#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>

#include "ClientSocket.h"
#include "Messages.h"

class ClientStub {
private:
	ClientSocket socket;
public:
	ClientStub();
	int Init(std::string ip, int port);
	LaptopInfo OrderLaptop(CustRequest cust_req);
    CustRecord ReadRecord(CustRequest cust_req);
	void SendIFAMessage(IFAMessage ifaMessage);
};


#endif // end of #ifndef __CLIENT_STUB_H__
