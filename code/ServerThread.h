#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <map>

#include "Messages.h"
#include "ServerSocket.h"
#include "Replica.h"
#include "ServerReplicaClientStub.h"
#include "ServerStub.h"




struct ExpertRequest {
	LaptopInfo laptop;
	std::promise<LaptopInfo> prom;
};

struct FactoryAdminReq {
	CustRecord cust_record;
	std::promise<int> admin_promise;
};

struct FactoryAdminDtls {
	int committed_index;
	int id;
	int primary_id;
	int factory_id;
    int last_index;
	std::map<int, Replica> replicaMap;
};

class LaptopFactory {
private:
	//std::queue<std::unique_ptr<ExpertRequest>> erq;
	//std::mutex erq_lock;
	//std::condition_variable erq_cv;

	std::queue<std::unique_ptr<FactoryAdminReq>> admin_queue;
	std::mutex admin_queue_lock;
	std::condition_variable admin_queue_cv;

	//my variables
	std::map<int, std::unique_ptr<ServerReplicaClientStub>> replicaStubMap;
	bool replica_connection_status = false;

	FactoryAdminDtls admin_dtls;

	std::mutex cust_rd_lock;
	std::map<int, int> cust_rec_map;

	std::mutex log_lock;
	std::vector<MapOp> smr_log;

	std::mutex admin_lock;


	LaptopInfo CreateRegularLaptop(LaptopOrder order, int engineer_id);
	//LaptopInfo CreateCustomLaptop(LaptopOrder order, int engineer_id);
	LaptopInfo CreateLaptopAdminRequest(CustRequest cust_rq, int engineer_id);
	void updateCustomerRecord();
public:
	void EngineerThread(std::unique_ptr<ServerSocket> socket, int id);
	//void ExpertThread(int id);
	void SetAdminDtls(FactoryAdminDtls admin_dtls);
	void FactoryAdminThread(int id);

};


#endif // end of #ifndef __SERVERTHREAD_H__

