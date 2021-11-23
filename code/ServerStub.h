#ifndef __SERVER_STUB_H__
#define __SERVER_STUB_H__

#include <memory>

#include "ServerSocket.h"
#include "Messages.h"

class ServerStub {
private:
	std::unique_ptr<ServerSocket> socket;
public:
	ServerStub();
	void Init(std::unique_ptr<ServerSocket> socket);
	CustRequest ReceiveRequest();
	int ReturnRecord(CustRecord customer_rec);
	int SendLaptop(LaptopInfo info);
	
	IFAMessage ReceiveIFAMessage();
	RepRequest RecRepRequest();
	int SendRepResponse(int p_last_index);

};

#endif // end of #ifndef __SERVER_STUB_H__
