#ifndef __SERVER_REPLICA_CLIENT_STUB_H__
#define __SERVER_REPLICA_CLIENT_STUB_H__

#include <string>

#include "ServerReplicaClientSocket.h"
#include "Messages.h"

class ServerReplicaClientStub {
private:
	ServerReplicaClientSocket socket;
	bool stub_failed_status;
	bool identity_send_status;
public:
	ServerReplicaClientStub();
	bool GetStubFailedStatus();
	void StopStub();
	int Init(std::string ip, int port);
	
	int SendRepRequest(RepRequest rep_req);
	void SetIdentitySendStatus(bool identity_send_status);
	bool GetIdentitySendStatus();

    void SendIFAMessage(IFAMessage ifaMessage);
};

#endif // end of #ifndef __SERVER_REPLICA_CLIENT_STUB_H__
