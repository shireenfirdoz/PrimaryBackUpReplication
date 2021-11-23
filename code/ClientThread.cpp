#include "ClientThread.h"
#include "Messages.h"

#include <iostream>

ClientThreadClass::ClientThreadClass() {}

/*
void ClientThreadClass::
ThreadBody(std::string ip, int port, int id, int orders, int type) {
	customer_id = id;
	num_orders = orders;
	req_type = type;
	if (!stub.Init(ip, port)) {
		std::cout << "Thread " << customer_id << " failed to connect" << std::endl;
		return;
	}
	//changes for all three types of request_type

		IFAMessage ifa_message;
	ifa_message.SetIsIFA(0); //client is 0
	stub.SendIFAMessage(ifa_message);

CustRequest customer_req;
		LaptopInfo laptop;
	if (type == 1)
	{
		for (int i = 0; i < num_orders; i++) {
		//LaptopOrder order;
		//order.SetOrder(customer_id, i, laptop_type);
		
		customer_req.SetRequest(customer_id, i, req_type);
		timer.Start();
			std::cout << "customer_id " << customer_id << "i" << i << std::endl;
		laptop = stub.OrderLaptop(customer_req);
		timer.EndAndMerge();
        
		std::cout << "receive a laptop customer id" << laptop.GetCustomerId() << " order no  " << laptop.GetOrderNumber() << " engineer id" << laptop.GetEngineerId() << " admin id" << laptop.GetAdminId() << std::endl;
		//std::cout<< "laptop custid" << laptop.GetCustomerId() << " " << std::endl;
		if (!laptop.IsValid()) {
			std::cout << "Invalid laptop " << customer_id << std::endl;
			break;	
		} 
	}
	} else if(type == 2){
		for (int i = 1; i <= num_orders; i++) {
			CustRequest customer_req;
			CustRecord rec;
			customer_req.SetRequest(customer_id, i, req_type);

			timer.Start();
			rec = stub.ReadRecord(customer_req);
			timer.EndAndMerge();

			if (!rec.IsValid()) {
				std::cout << "Invalid record " << customer_id << std::endl;
				break;
				 } else {
				 std::cout << " Record found: c_id " << rec.GetCustomerId() << ", last order :" << rec.GetLastOrder() << std::endl;
				  }
			//}
		}
	}
	else if(type == 3){//num_orders is number of client
		for (int i = 1; i <= num_orders; i++) {
			CustRequest customer_req;
			CustRecord rec;
			customer_req.SetRequest(i, -1, 2);

			timer.Start();
			rec = stub.ReadRecord(customer_req);
			timer.EndAndMerge();
			if (rec.IsValid()) {
				std::cout << rec.GetCustomerId() << "\t";
				std::cout << rec.GetLastOrder() << std::endl;
			}
		}
	}
		


} */



void ClientThreadClass::
ThreadBody(std::string ip, int port, int id, int orders, int type) {
	customer_id = id;
	num_orders = orders;
	req_type = type;
	if (!stub.Init(ip, port)) {
		std::cout << "Thread " << customer_id << " failed to connect" << std::endl;
		return;
	}

if(req_type == 1){
	for (int i = 0; i < num_orders; i++) {

		//LaptopOrder order;
		//order.SetOrder(customer_id, i, laptop_type);

		IFAMessage ifa_message;
	  ifa_message.SetIsIFA(0); //client is 0
	  stub.SendIFAMessage(ifa_message);

		CustRequest customer_req;
		LaptopInfo laptop;
		customer_req.SetRequest(customer_id, i, req_type);


		timer.Start();
		laptop = stub.OrderLaptop(customer_req);
		timer.EndAndMerge();

		if (!laptop.IsValid()) {
			std::cout << "Invalid laptop " << customer_id << std::endl;
			break;	
		} 
	}

 }else if(req_type == 2){

	 for (int i = 0; i < num_orders; i++) {

		 	IFAMessage ifa_message;
	  ifa_message.SetIsIFA(0); //client is 0
	  stub.SendIFAMessage(ifa_message);


			CustRequest customer_req;
			CustRecord rec;
			customer_req.SetRequest(customer_id, i, req_type);

			timer.Start();
			rec = stub.ReadRecord(customer_req);
			timer.EndAndMerge();

          // std::cout << " record " << rec.GetCustomerId() << "last_order" << rec.GetLastOrder() << std::endl;

			if (!rec.IsValid()) {
				std::cout << "Invalid record " << customer_id << std::endl;
				  break;
				 } else {
				// std::cout << " Record found: c_id " << rec.GetCustomerId() << ", last order :" << rec.GetLastOrder() << std::endl;
				  }
			//}
		}

 }else if(req_type == 3){
	 //num_orders is number of client

		for (int i = 0; i < num_orders; i++) {

         IFAMessage ifa_message;
	      ifa_message.SetIsIFA(0); //client is 0
	    stub.SendIFAMessage(ifa_message);

			CustRequest customer_req;
			CustRecord rec;
			customer_req.SetRequest(i, -1, 2);

			timer.Start();
			rec = stub.ReadRecord(customer_req);
			timer.EndAndMerge();
			if (rec.IsValid()) {
				std::cout << rec.GetCustomerId() << "\t";
				std::cout << rec.GetLastOrder() << std::endl;
			}
		}

 }else{
	 std::cout << "Invalid req_type " << customer_id << std::endl;
 }
}

ClientTimer ClientThreadClass::GetTimer() {
	return timer;	
}

