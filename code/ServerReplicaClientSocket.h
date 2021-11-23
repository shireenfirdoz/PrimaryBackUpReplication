#ifndef __SERVER_REPLICA_CLIENT_SOCKET_H__
#define __SERVER_REPLICA_CLIENT_SOCKET_H__

#include <string>

#include "Socket.h"


class ServerReplicaClientSocket: public Socket {
public:
	ServerReplicaClientSocket() {}
	~ServerReplicaClientSocket() {}

	int Init(std::string ip, int port);
};


#endif // end of #ifndef __SERVER_REPLICA_CLIENT_SOCKET_H__
