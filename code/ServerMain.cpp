#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "ServerSocket.h"
#include "ServerThread.h"
#include "Replica.h"


int main(int argc, char *argv[]) {
	int port;
	int engineer_cnt = 0;
	//int num_experts;
	//int num_replica;
	int id;
	ServerSocket socket;
	LaptopFactory factory;
	std::unique_ptr<ServerSocket> new_socket;
	std::vector<std::thread> thread_vector;

	std::map<int, Replica> replicaMap;
	
/*	if (argc < 3) {
		std::cout << "not enough arguments" << std::endl;
		std::cout << argv[0] << "[port #] [# experts]" << std::endl;
		return 0;
	} */

	if (argc < 4) {
		std::cout << "arguments are not enough" << std::endl;
		std::cout << argv[0] << "[port #] [# unique ID] [# replicas]" << std::endl;
		return 0;
	}

int count = atoi(argv[3]);
	if (argc < 4 + 3 * count) {
		std::cout << "arguments are not enough" << std::endl;
		std::cout << argv[0] << "[port #] [# unique ID] [# replicas] ";
		std::cout << "(repeat [ID] [IP] [port #]" << std::endl;
		return 0;
	}

	port = atoi(argv[1]);
    id = atoi(argv[2]);
	for (int i = 0; i < count; i++) {
		Replica replica;
		replica.SetId(atoi(argv[4 + i*3]));
		replica.SetIp(argv[4 + i*3 + 1]);
		replica.SetPort(atoi(argv[4 + i*3 + 2]));
		replicaMap.insert({replica.GetId(), replica});
	}


	//num_experts = atoi(argv[2]);

	/*for (int i = 0; i < num_experts; i++) {
		std::thread expert_thread(&LaptopFactory::ExpertThread, 
				&factory, engineer_cnt++);
		thread_vector.push_back(std::move(expert_thread));
	}*/

	FactoryAdminDtls admin_dtls;
	admin_dtls.id = id;
	admin_dtls.last_index = -1;
	admin_dtls.committed_index = -1;
	admin_dtls.primary_id = -1;
	admin_dtls.replicaMap = replicaMap;

	factory.SetAdminDtls(admin_dtls);
	std::thread factory_admin_thread(&LaptopFactory::FactoryAdminThread, &factory, engineer_cnt++);
	thread_vector.push_back(std::move(factory_admin_thread));

	if (!socket.Init(port)) {
		std::cout << "Socket initialization failed" << std::endl;
		return 0;
	}

	while ((new_socket = socket.Accept())) {
		std::thread engineer_thread(&LaptopFactory::EngineerThread, 
				&factory, std::move(new_socket), 
				engineer_cnt++);
		thread_vector.push_back(std::move(engineer_thread));
	}
	return 0;
}
