#include "ServerStub.h"
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

ServerStub::ServerStub() {}

void ServerStub::Init(std::unique_ptr<ServerSocket> socket) {
	this->socket = std::move(socket);
}

CustRequest ServerStub::ReceiveRequest() {
	char buffer[32];
	CustRequest customer_req;
	if (socket->Recv(buffer, customer_req.Size(), 0)) {
		customer_req.Unmarshal(buffer);
	}
	return customer_req;	
}

int ServerStub::SendLaptop(LaptopInfo info) {
	char buffer[32];
	info.Marshal(buffer);
	//std::cout<< "here in sendLaptop" << std::endl;
	return socket->Send(buffer, info.Size(), 0);
}

int ServerStub::ReturnRecord(CustRecord customer_rec) {
	char buffer[16];
	customer_rec.Marshal(buffer);
	return socket->Send(buffer, customer_rec.Size(), 0);
}

IFAMessage ServerStub::ReceiveIFAMessage() {
   char buffer[sizeof(int)];
	IFAMessage ifa_messgae;
	if (socket->Recv(buffer, ifa_messgae.Size(), 0)) {
		ifa_messgae.Unmarshal(buffer);
	}
	return ifa_messgae;
}

RepRequest ServerStub::RecRepRequest() {
    int buff_size = sizeof(int) * 6;
	char buffer[buff_size];
	RepRequest rep_request;
	if (socket->Recv(buffer, rep_request.Size(), 0)) {
		rep_request.Unmarshal(buffer);
	}
	return rep_request;
	}

int ServerStub::SendRepResponse(int p_last_index) {
     char buffer[sizeof(int)];
	int last_index = htonl(p_last_index);
	memcpy(buffer, &last_index, sizeof(last_index));
	return socket->Send(buffer, sizeof(int), 0);
	}

	