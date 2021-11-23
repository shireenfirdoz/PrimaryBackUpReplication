#include <cstring>
#include <arpa/inet.h>

#include "ServerReplicaClientStub.h"

bool stub_failed_status;
	bool identity_send_status;

ServerReplicaClientStub::ServerReplicaClientStub(){
    stub_failed_status = true;
}
bool ServerReplicaClientStub::GetStubFailedStatus(){
      return stub_failed_status;
}
void ServerReplicaClientStub::StopStub(){
	     stub_failed_status = true;
	     socket.Close();
    }

	int ServerReplicaClientStub::Init(std::string ip, int port){
	    int fd = socket.Init(ip, port);
	    stub_failed_status = false;
	    return fd;
    }
	
	int ServerReplicaClientStub::SendRepRequest(RepRequest rep_req){
        	int res1;
	int buff_size = sizeof(int) * 6;
	char buffer[buff_size];
	rep_req.Marshal(buffer);
	int size = rep_req.Size();
	if (socket.Send(buffer, size, 0)) {
		size = sizeof(res1);
		if (socket.Recv(buffer, size, 0)) {
			memcpy(&res1, buffer, sizeof(res1));
		}
	}
	return ntohl(res1);

    }

	void ServerReplicaClientStub::SetIdentitySendStatus(bool identity_send_status){
             identity_send_status = identity_send_status;
    }

	bool ServerReplicaClientStub::GetIdentitySendStatus(){
               return identity_send_status;
    }

    void ServerReplicaClientStub::SendIFAMessage(IFAMessage ifaMessage){
     int buff_size = sizeof(int);
	char buffer[buff_size];
	ifaMessage.Marshal(buffer);
	int size = ifaMessage.Size();
	socket.Send(buffer, size, 0);
    }


