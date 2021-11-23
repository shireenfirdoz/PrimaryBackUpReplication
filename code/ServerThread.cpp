#include <iostream>
#include <memory>
#include <map>

#include "ServerThread.h"
#include "ServerStub.h"


LaptopInfo LaptopFactory::
CreateRegularLaptop(LaptopOrder order, int engineer_id) {
	LaptopInfo laptop;
	laptop.CopyOrder(order);
	laptop.SetEngineerId(engineer_id);
	laptop.SetAdminId(-1);
	return laptop;
}
/*
LaptopInfo LaptopFactory::
CreateCustomLaptop(LaptopOrder order, int engineer_id) {
	LaptopInfo laptop;
	laptop.CopyOrder(order);
	laptop.SetEngineerId(engineer_id);

	std::promise<LaptopInfo> prom;
	std::future<LaptopInfo> fut = prom.get_future();

	std::unique_ptr<ExpertRequest> req = 
		std::unique_ptr<ExpertRequest>(new ExpertRequest);
	req->laptop = laptop;
	req->prom = std::move(prom);

	erq_lock.lock();
	erq.push(std::move(req));
	erq_cv.notify_one();
	erq_lock.unlock();

	laptop = fut.get();
	return laptop;
} */



LaptopInfo LaptopFactory::CreateLaptopAdminRequest(CustRequest cust_rq, int engineer_id) {
	LaptopInfo laptop;
	int admin_id = -1;
	CustRecord customer_rec;

	laptop.SetInfo(cust_rq.GetCustomerId(),cust_rq.GetOrderNumber(),cust_rq.GetRequestType(),engineer_id,-1);
	laptop.SetEngineerId(engineer_id);
	laptop.SetAdminId(-1);
	  // std::cout << "customer_id" << laptop.GetCustomerId() << std::endl;

	customer_rec.SetRecord(laptop.GetCustomerId(), laptop.GetOrderNumber());

	std::promise<int> admin_prom;
	std::future<int> fut = admin_prom.get_future();

	std::unique_ptr<FactoryAdminReq> request = std::unique_ptr<FactoryAdminReq>(new FactoryAdminReq);
	request->cust_record = customer_rec;
	request->admin_promise = std::move(admin_prom);

	admin_queue_lock.lock();
	admin_queue.push(std::move(request));
	admin_queue_cv.notify_one();
	admin_queue_lock.unlock();

	admin_id = fut.get();
    //std::cout << "admin_id" << admin_id << std::endl;
	laptop.SetAdminId(admin_id);
	return laptop;
}

void LaptopFactory::
EngineerThread(std::unique_ptr<ServerSocket> socket, int id) {
	int engineer_id = id;
	//int laptop_type;
	int request_type;
	LaptopOrder order;
	LaptopInfo laptop;
	int cust_id;
	CustRequest cust_rq;
	CustRecord cust_rd;

	ServerStub stub;

	stub.Init(std::move(socket));

	while (true) {

		 IFAMessage	ifa_message = stub.ReceiveIFAMessage();
		int identity_ifa_client_flag = ifa_message.GetIsIFA();

		//std::cout << " identity_ifa_client_flag " << identity_ifa_client_flag << std::endl;
		if(identity_ifa_client_flag == 0){
			cust_rq = stub.ReceiveRequest();
					if (!cust_rq.IsValid()) {
						break;
					}
					//get the request type
					request_type = cust_rq.GetRequestType();
					switch (request_type) {
						case 1:
						{
							//std::cout << " create laptop customer_id"  << cust_rq.GetCustomerId() << "order no" << cust_rq.GetOrderNumber() << std::endl;
							laptop = CreateLaptopAdminRequest(cust_rq, engineer_id);
							//std::cout << "receive a laptop customer id" << laptop.GetCustomerId() << " order no  " << laptop.GetOrderNumber() << " engineer id" << laptop.GetEngineerId() << " admin id" << laptop.GetAdminId() << std::endl;
							stub.SendLaptop(laptop);
							break;
						}
						case 2:
						{
							cust_id = cust_rq.GetCustomerId();
						    //std::cout << " read request from client" << cust_id << std::endl;

							cust_rd.SetCustomerId(cust_id);
							cust_rd.SetLastOrder(-1);
							cust_rd_lock.lock();
							if (cust_rec_map.find(cust_id) != cust_rec_map.end()) {
								cust_rd.SetLastOrder(cust_rec_map[cust_id]);
							}
							cust_rd_lock.unlock();
							//std::cout << "record found: " << cust_id << " : " << cust_rd.GetLastOrder() << std::endl;

							stub.ReturnRecord(cust_rd);
							break;
						}
						default:
							std::cout << "not define request type: "
								<< request_type << std::endl;
					}

	        }else if (identity_ifa_client_flag == 1){

				RepRequest replica_request = stub.RecRepRequest();
					if (!replica_request.IsValid()) {
						break;
					}
					int primary_fac_id = replica_request.GetFactoryId();
					if (admin_dtls.primary_id != primary_fac_id) {
						admin_dtls.primary_id = primary_fac_id;
					}
					
					int rep_last_index = replica_request.GetLastIndex();
					MapOp rep_mop = replica_request.GetMapOp();

					log_lock.lock();
					// std::cout << "last_index" << rep_last_index << std::endl;
					if ((rep_last_index - admin_dtls.last_index) > 1) {
						int last_index1 = admin_dtls.last_index;
						for (int i = last_index1; i < rep_last_index; i++) {
							MapOp mapop1 = MapOp();
							smr_log.insert((smr_log.begin() + i), mapop1);
						   //  std::cout << "i" << i << std::endl;
							admin_dtls.last_index += 1;
						}
					  // std::cout << "last_index " << admin_dtls.last_index << std::endl;
					}
					smr_log.insert((smr_log.begin() + rep_last_index), rep_mop);
					//std::cout << "rep order number " << smr_log[rep_last_index].GetArg2() << std::endl;
					//std::cout << " set smr_log" << std::endl;
					log_lock.unlock();
					admin_dtls.last_index = rep_last_index;
				
				    // log updation
					int rep_commited_index = replica_request.GetCommittedIndex();
					 // std::cout << "commited index " << rep_commited_index << std::endl;
					if (rep_commited_index != -1) {
						log_lock.lock();
						MapOp op_commited = smr_log[rep_commited_index];
						log_lock.unlock();
						int commited_op_cust_id = op_commited.GetArg1();
						int commited_op_order_no = op_commited.GetArg2();
						  // std::cout << "commited order no " <<  commited_op_order_no << std::endl;
						cust_rd_lock.lock();
						if (cust_rec_map.find(commited_op_cust_id) == cust_rec_map.end()) {
							cust_rec_map.insert({commited_op_cust_id, commited_op_order_no});
						} else {
							cust_rec_map[commited_op_cust_id] = commited_op_order_no;
						}
						cust_rd_lock.unlock();
						admin_dtls.committed_index = rep_commited_index;
					}
					stub.SendRepResponse(admin_dtls.last_index);


			}else{
				//std::cout<< "not a valid identity " << std::endl;
				break;
			}
	   }
}


void LaptopFactory::updateCustomerRecord() {
	cust_rd_lock.lock();
	MapOp last_op_rec = smr_log[admin_dtls.last_index];

	int last_op_rec_order_num = last_op_rec.GetArg2();
	int last_op_rec_cid = last_op_rec.GetArg1();
	
	if (cust_rec_map.find(last_op_rec_cid) == cust_rec_map.end()) {
		cust_rec_map.insert({last_op_rec_cid, last_op_rec_order_num});
	} else {
		cust_rec_map[last_op_rec_cid] = last_op_rec_order_num;
	}
	//std::cout << "customer written record"<< last_op_rec_cid << " : " << cust_rec_map[last_op_rec_cid] << std::endl;
	admin_dtls.committed_index = admin_dtls.last_index;
	cust_rd_lock.unlock();
}

void LaptopFactory::FactoryAdminThread(int id) {

std::unique_lock<std::mutex> ul(admin_queue_lock, std::defer_lock);
	while (true) {
		ul.lock();

		if (admin_queue.empty()) {
			admin_queue_cv.wait(ul, [this]{ return !admin_queue.empty(); });
		}
		
		admin_lock.lock();
		if (admin_dtls.primary_id != admin_dtls.id) {
			admin_dtls.primary_id = admin_dtls.id;
		}
		admin_lock.unlock();

	 if (!replica_connection_status) {

		for (std::map<int,Replica>::iterator it=admin_dtls.replicaMap.begin(); it!=admin_dtls.replicaMap.end(); it++){
			 // std::cout << it->first << " => " << it->second << '\n';
			  Replica replica = it->second;
			  if(replica.GetStatus()){
                  std::unique_ptr<ServerReplicaClientStub> replica_factory_stub = std::unique_ptr<ServerReplicaClientStub>(new ServerReplicaClientStub);
			      if (!replica_factory_stub->Init(replica.GetIp(), replica.GetPort())) {
						replica.SetStatus(false);
					} else {
						replicaStubMap[replica.GetId()] = std::move(replica_factory_stub);
					}
			
			  }
		  }
       replica_connection_status = true;
	 }

		auto admin_request = std::move(admin_queue.front());
		admin_queue.pop();

		ul.unlock();

		std::this_thread::sleep_for(std::chrono::microseconds(100));
		CustRecord cust_record = admin_request->cust_record;
		int cust_id = cust_record.GetCustomerId();
		int order_num = cust_record.GetLastOrder();
		MapOp op1;
		op1.SetMapOp(1, cust_id, order_num);
		log_lock.lock();
		int log_diff = smr_log.size() - admin_dtls.last_index;
		if (log_diff > 1) {
			smr_log[admin_dtls.last_index] = op1;
		} else {
			smr_log.push_back(op1);
			admin_dtls.last_index = admin_dtls.last_index + 1;
		}
		log_lock.unlock();

		RepRequest replica_request;
		replica_request.SetRepRequest(admin_dtls.factory_id, admin_dtls.committed_index
			                   , admin_dtls.last_index, op1);
	
		
	    
       for (std::map<int, std::unique_ptr<ServerReplicaClientStub>>::iterator itr = replicaStubMap.begin(); itr != replicaStubMap.end(); itr++ ) {
			if (!itr->second->GetStubFailedStatus()) {
				if (!itr->second->GetIdentitySendStatus()) {
					IFAMessage ifa_message;
					ifa_message.SetIsIFA(1);// server 1
					itr->second->SendIFAMessage(ifa_message);
					itr->second->SetIdentitySendStatus(true);
				}
				
				int response = itr->second->SendRepRequest(replica_request);
				
				if (response != admin_dtls.last_index) {
				
				  itr->second->StopStub();
				  //for live threads 
					
				}
			}
		}

		updateCustomerRecord();

		admin_request->admin_promise.set_value(id);

	}
 
}

void LaptopFactory::SetAdminDtls(FactoryAdminDtls p_admin_dtls) {
        admin_dtls = p_admin_dtls;
}


