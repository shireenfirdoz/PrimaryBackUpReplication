#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

class LaptopOrder {
private:
	int customer_id;
	int order_number;
	int laptop_type;

public:
	LaptopOrder();
	void operator = (const LaptopOrder &order) {
		customer_id = order.customer_id;
		order_number = order.order_number;
		laptop_type = order.laptop_type;
	}
	void SetOrder(int cid, int order_num, int type);
	int GetCustomerId();
	int GetOrderNumber();
	int GetLaptopType();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};

class LaptopInfo {
private:
	int customer_id;
	int order_number;
	int laptop_type;
	int engineer_id;
	int admin_id;

public:
	LaptopInfo();
	void operator = (const LaptopInfo &info) {
		customer_id = info.customer_id;
		order_number = info.order_number;
		laptop_type = info.laptop_type;
		engineer_id = info.engineer_id;
		admin_id = info.admin_id;
	}
	void SetInfo(int cid, int order_num, int type, int engid, int adminid);
	void CopyOrder(LaptopOrder order);
	void SetEngineerId(int id);
	//void SetExpertId(int id);
	void SetAdminId(int id);

	int GetCustomerId();
	int GetOrderNumber();
	int GetLaptopType();
	int GetEngineerId();
	//int GetExpertId();
	int GetAdminId();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};


class CustRequest {
private:
	int customer_id;
	int order_number;
	int request_type;

public:
	CustRequest();
	void operator = (const CustRequest &req) {
		customer_id = req.customer_id;
		order_number = req.order_number;
		request_type = req.request_type;
	}
	void SetRequest(int cid, int order_num, int req_type);
	int GetCustomerId();
	int GetOrderNumber();
	int GetRequestType();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};


class CustRecord {
private:
	int customer_id;
	int last_order;
public:
	CustRecord();
	void operator = (const CustRecord &cust_rec) {
		customer_id = cust_rec.customer_id;
		last_order = cust_rec.last_order;
	}
	void SetRecord(int cust_id, int last_or);
	void SetCustomerId(int cust_id);
	void SetLastOrder(int last_or);

	int GetCustomerId();
	int GetLastOrder();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};


class MapOp {
private:
	int opcode; 
	int arg1;
	int arg2; 
public:
	MapOp();
	void operator = (const MapOp &map_op) {
		opcode = map_op.opcode;
		arg1 = map_op.arg1;
		arg2 = map_op.arg2;
	}
	void SetMapOp(int opcd, int ar1, int ar2);
	void SetOpcode(int opcd);
	void SetArg1(int ar1);
	void SetArg2(int ar2);

	int GetOpcode();
	int GetArg1();
	int GetArg2();

	int Size();

	void Marshal(char * buffer);
	void Unmarshal(char * buffer);

	bool IsValid();

	void Print();
};


class RepRequest {
private:
	int factory_id;
	int committed_index;
	int last_index;
	MapOp map_op;
public:
	RepRequest();
	void operator = (const RepRequest &rep_request) {
		factory_id = rep_request.factory_id;
		committed_index = rep_request.committed_index;
		last_index = rep_request.last_index;
		map_op = rep_request.map_op;
	}
	void SetRepRequest(int factory_id, int commit_index, int last_index, MapOp map_op);
	void SetFactoryId(int factory_id);
	void SetCommittedIndex(int commit_index);
	void SetLastIndex(int last_index);
	void SetMapOp(MapOp map_op);

	int GetFactoryId();
	int GetCommittedIndex();
	int GetLastIndex();
	MapOp GetMapOp();

	int Size();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);

	bool IsValid();

	void Print();
};


class IFAMessage {
private:
	int is_ifa;
public:
	IFAMessage();
	int Size();
	void SetIsIFA(int p_is_ifa);
	int GetIsIFA();

	bool IsValid();

	void Marshal(char *buffer);
	void Unmarshal(char *buffer);
};

#endif // #ifndef __MESSAGES_H__
