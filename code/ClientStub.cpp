#include "ClientStub.h"
#include <ostream>
#include <iostream>

ClientStub::ClientStub() {}

int ClientStub::Init(std::string ip, int port) {
	return socket.Init(ip, port);	
}

LaptopInfo ClientStub::OrderLaptop(CustRequest cust_req) {
	LaptopInfo info;
	char buffer[32];
	int size;
	cust_req.Marshal(buffer);
	size = cust_req.Size();
	if (socket.Send(buffer, size, 0)) {
		size = info.Size();
		if (socket.Recv(buffer, size, 0)) {
			info.Unmarshal(buffer);
			
		} 
	}
	//std::cout << "info custid" << info.GetCustomerId() << std::endl;
	return info;
}

CustRecord ClientStub::ReadRecord(CustRequest cust_req){
	CustRecord customer_rec;
	char buffer[32];
	cust_req.Marshal(buffer);
	int size = cust_req.Size();
	if (socket.Send(buffer, size, 0)) {
		size = customer_rec.Size();
		if (socket.Recv(buffer, size, 0)) {
			customer_rec.Unmarshal(buffer);
		}
	}
	return customer_rec;
}

void ClientStub::SendIFAMessage(IFAMessage ifaMessage){
	int buff_size = sizeof(int);
	char buffer[buff_size];
	ifaMessage.Marshal(buffer);
	int size = ifaMessage.Size();
	socket.Send(buffer, size, 0);
}

