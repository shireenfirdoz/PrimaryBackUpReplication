#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include "Messages.h"

LaptopOrder::LaptopOrder() {
	customer_id = -1;
	order_number = -1;
	laptop_type = -1;
}

void LaptopOrder::SetOrder(int id, int number, int type) {
	customer_id = id;
	order_number = number;
	laptop_type = type;
}

int LaptopOrder::GetCustomerId() { return customer_id; }
int LaptopOrder::GetOrderNumber() { return order_number; }
int LaptopOrder::GetLaptopType() { return laptop_type; }

int LaptopOrder::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(laptop_type);
}

void LaptopOrder::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(order_number);
	int net_laptop_type = htonl(laptop_type);
	int offset = 0;
	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(buffer + offset, &net_laptop_type, sizeof(net_laptop_type));
}

void LaptopOrder::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int net_laptop_type;
	int offset = 0;
	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(&net_laptop_type, buffer + offset, sizeof(net_laptop_type));

	customer_id = ntohl(net_customer_id);
	order_number = ntohl(net_order_number);
	laptop_type = ntohl(net_laptop_type);
}

bool LaptopOrder::IsValid() {
	return (customer_id != -1);
}

void LaptopOrder::Print() {
	std::cout << "id " << customer_id << " ";
	std::cout << "num " << order_number << " ";
	std::cout << "type " << laptop_type << std::endl;
}

LaptopInfo::LaptopInfo() {
	customer_id = -1;
	order_number = -1;
	laptop_type = -1;
	engineer_id = -1;
	admin_id = -1;
}

void LaptopInfo::SetInfo(int id, int number, int type, int engid, int adminid) {
	customer_id = id;
	order_number = number;
	laptop_type = type;
	engineer_id = engid;
	admin_id = adminid;
}

void LaptopInfo::CopyOrder(LaptopOrder order) {
	customer_id = order.GetCustomerId();
	order_number = order.GetOrderNumber();
	laptop_type = order.GetLaptopType();
}
void LaptopInfo::SetEngineerId(int p_id) { engineer_id = p_id; }
//void LaptopInfo::SetExpertId(int id) { expert_id = id; }
void LaptopInfo::SetAdminId(int p_id) { admin_id = p_id; }

int LaptopInfo::GetCustomerId() { return customer_id; }
int LaptopInfo::GetOrderNumber() { return order_number; }
int LaptopInfo::GetLaptopType() { return laptop_type; }
int LaptopInfo::GetEngineerId() { return engineer_id; }
//int LaptopInfo::GetExpertId() { return expert_id; }
int LaptopInfo::GetAdminId() { return admin_id; }

int LaptopInfo::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(laptop_type)
		+ sizeof(engineer_id) + sizeof(admin_id);
}

void LaptopInfo::Marshal(char *buffer) {
	int net_customer_id = htonl(customer_id);
	int net_order_number = htonl(order_number);
	int net_laptop_type = htonl(laptop_type);
	int net_engineer_id = htonl(engineer_id);
	int net_admin_id = htonl(admin_id);
	int offset = 0;

	memcpy(buffer + offset, &net_customer_id, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(buffer + offset, &net_order_number, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(buffer + offset, &net_laptop_type, sizeof(net_laptop_type));
	offset += sizeof(net_laptop_type);
	memcpy(buffer + offset, &net_engineer_id, sizeof(net_engineer_id));
	offset += sizeof(net_engineer_id);
	memcpy(buffer + offset, &net_admin_id, sizeof(net_admin_id));

}

void LaptopInfo::Unmarshal(char *buffer) {
	int net_customer_id;
	int net_order_number;
	int net_laptop_type;
	int net_engineer_id;
	int net_admin_id;
	int offset = 0;

	memcpy(&net_customer_id, buffer + offset, sizeof(net_customer_id));
	offset += sizeof(net_customer_id);
	memcpy(&net_order_number, buffer + offset, sizeof(net_order_number));
	offset += sizeof(net_order_number);
	memcpy(&net_laptop_type, buffer + offset, sizeof(net_laptop_type));
	offset += sizeof(net_laptop_type);
	memcpy(&net_engineer_id, buffer + offset, sizeof(net_engineer_id));
	offset += sizeof(net_engineer_id);
	memcpy(&net_admin_id, buffer + offset, sizeof(net_admin_id));
 //std::cout<< "here in sendLaptop in message" << std::endl;
	customer_id = ntohl(net_customer_id);
	order_number = ntohl(net_order_number);
	laptop_type = ntohl(net_laptop_type);
	engineer_id = ntohl(net_engineer_id);
	admin_id = ntohl(net_admin_id);
	//std::cout<< "here in sendLaptop in message 2" << customer_id << std::endl;
}

bool LaptopInfo::IsValid() {
	return (customer_id != -1);
}

void LaptopInfo::Print() {
	std::cout << "id " << customer_id << " ";
	std::cout << "num " << order_number << " ";
	std::cout << "type " << laptop_type << " ";
	std::cout << "engid " << engineer_id << " ";
	std::cout << "admin_id " << admin_id << std::endl;
}

CustRequest::CustRequest() {
	customer_id = -1;
	order_number = -1;
	request_type = -1;
}

void CustRequest::SetRequest(int p_customer_id, int p_order_number, int p_request_type) {
	customer_id = p_customer_id;
	order_number = p_order_number;
	request_type = p_request_type;
}

int CustRequest::GetCustomerId() { return customer_id; }
int CustRequest::GetOrderNumber() { return order_number; }
int CustRequest::GetRequestType() { return request_type; }

int CustRequest::Size() {
	return sizeof(customer_id) + sizeof(order_number) + sizeof(request_type);
}

void CustRequest::Marshal(char *buffer) {
	int customer_id1 = htonl(customer_id);
	int order_number1 = htonl(order_number);
	int request_type1 = htonl(request_type);
	int offset = 0;
	memcpy(buffer + offset, &customer_id1, sizeof(customer_id1));
	offset += sizeof(customer_id1);
	memcpy(buffer + offset, &order_number1, sizeof(order_number1));
	offset += sizeof(order_number1);
	memcpy(buffer + offset, &request_type1, sizeof(request_type1));
}

void CustRequest::Unmarshal(char *buffer) {
	int customer_id1;
	int order_number1;
	int request_type1;
	int offset = 0;
	memcpy(&customer_id1, buffer + offset, sizeof(customer_id1));
	offset += sizeof(customer_id1);
	memcpy(&order_number1, buffer + offset, sizeof(order_number1));
	offset += sizeof(order_number1);
	memcpy(&request_type1, buffer + offset, sizeof(request_type1));

	customer_id = ntohl(customer_id1);
	order_number = ntohl(order_number1);
	request_type = ntohl(request_type1);
}

bool CustRequest::IsValid() {
	return (customer_id != -1);
}

void CustRequest::Print() {
	std::cout << "customer_id " << customer_id << " ";
	std::cout << "order_number " << order_number << " ";
	std::cout << "request_type " << request_type << std::endl;
}


CustRecord::CustRecord() {
	customer_id = -1;
	last_order = -1;
}

void CustRecord::SetRecord(int p_customer_id, int p_last_order) {
	customer_id = p_customer_id;
	last_order = p_last_order;
}

void CustRecord::SetCustomerId(int p_customer_id) { customer_id = p_customer_id; }
void CustRecord::SetLastOrder(int p_last_order) { last_order = p_last_order; }

int CustRecord::GetCustomerId() { return customer_id; }

int CustRecord::GetLastOrder() { return last_order; }

int CustRecord::Size() {
	return sizeof(customer_id) + sizeof(last_order);
}

void CustRecord::Marshal(char *buffer) {
	int customer_id1 = htonl(customer_id);
	int last_order1 = htonl(last_order);
	int offset = 0;

	memcpy(buffer + offset, &customer_id1, sizeof(customer_id1));
	offset += sizeof(customer_id1);
	memcpy(buffer + offset, &last_order1, sizeof(last_order1));
}

void CustRecord::Unmarshal(char *buffer) {
	int customer_id1;
	int last_order1;
	int offset = 0;

	memcpy(&customer_id1, buffer + offset, sizeof(customer_id1));
	offset += sizeof(customer_id1);
	memcpy(&last_order1, buffer + offset, sizeof(last_order1));

	customer_id = ntohl(customer_id1);
	last_order = ntohl(last_order1);
}

bool CustRecord::IsValid() {
	return (customer_id != -1);
}

void CustRecord::Print() {
	std::cout << "customer_id " << customer_id << " ";
	std::cout << "last order " << last_order << " ";
}

RepRequest::RepRequest() {
	factory_id = -1;
	committed_index = -1;
	last_index = -1;
	map_op = MapOp();
}

void RepRequest::SetRepRequest(int p_factory_id, int p_committed_index, int p_last_index, MapOp p_map_op) {
	factory_id = p_factory_id;
	committed_index = p_committed_index;
	last_index = p_last_index;
	map_op = p_map_op;
}

void RepRequest::SetFactoryId(int p_factory_id) {
	factory_id = p_factory_id;
}
void RepRequest::SetCommittedIndex(int p_committed_index) {
	committed_index = p_committed_index;
}

void RepRequest::SetLastIndex(int p_last_index) {
	last_index = p_last_index;
}

void RepRequest::SetMapOp(MapOp p_map_op) {
	map_op = p_map_op;
}

int RepRequest::GetFactoryId() {
	return factory_id;
}
int RepRequest::GetCommittedIndex() {
	return committed_index;
}
int RepRequest::GetLastIndex() {
	return last_index;
}

MapOp RepRequest::GetMapOp() {
	return map_op;
}

int RepRequest::Size() {
	return sizeof(factory_id) + sizeof(committed_index) +
	       sizeof(last_index) + map_op.Size();
}

void RepRequest::Marshal(char *buffer) {
	int factory_id1 = htonl(factory_id);
	int committed_index1 = htonl(committed_index);
	int last_index1 = htonl(last_index);

	int offset = 0;

	memcpy(buffer + offset, &factory_id1, sizeof(factory_id1));
	offset += sizeof(factory_id1);
	memcpy(buffer + offset, &committed_index1, sizeof(committed_index1));
	offset += sizeof(committed_index1);
	memcpy(buffer + offset, &last_index1, sizeof(last_index1));
	offset += sizeof(last_index1);

	char map_buffer[map_op.Size()];
	map_op.Marshal(map_buffer);

	memcpy(buffer + offset, &map_buffer, map_op.Size());
}

void RepRequest::Unmarshal(char *buffer) {
	int factory_id1;
	int committed_index1;
	int last_index1;

	int offset = 0;

	memcpy(&factory_id1, buffer + offset, sizeof(factory_id1));
	offset += sizeof(factory_id1);
	memcpy(&committed_index1, buffer + offset, sizeof(committed_index1));
	offset += sizeof(committed_index1);
	memcpy(&last_index1, buffer + offset, sizeof(last_index1));
	offset += sizeof(last_index1);

	factory_id = ntohl(factory_id1);
	committed_index = ntohl(committed_index1);
	last_index = ntohl(last_index1);

	char map_buffer[map_op.Size()];
	memcpy(&map_buffer, buffer + offset, map_op.Size());
	map_op.Unmarshal(map_buffer);
}

bool RepRequest::IsValid() {
	return (factory_id != -1);
}

void RepRequest::Print() {
	std::cout << "factory_id " << factory_id << " ";
	std::cout << "committed_index " << committed_index << " ";
	std::cout << "last_index " << last_index << " ";
	map_op.Print();
}

MapOp::MapOp() {
	opcode = -1;
	arg1 = -1;
	arg2 = -2;
}

void MapOp::SetMapOp(int p_opcode, int p_arg1, int p_arg2) {
	opcode = p_opcode;
	arg1 = p_arg1;
	arg2 = p_arg2;
}

void MapOp::SetOpcode(int p_opcode) {
	opcode = p_opcode;
}

void MapOp::SetArg1(int p_arg1) {
	arg1 = p_arg1;
}

void MapOp::SetArg2(int p_arg2) {
	arg2 = p_arg2;
}

int MapOp::GetOpcode() {
	return opcode;
}

int MapOp::GetArg1() {
	return arg1;
}

int MapOp::GetArg2() {
	return arg2;
}

int MapOp::Size() {
	return sizeof(opcode) + sizeof(arg1) + sizeof(arg2);
}

void MapOp::Marshal(char * buffer) {
	int opcode1 = htonl(opcode);
	int arg1_1 = htonl(arg1);
	int arg2_1 = htonl(arg2);

	int offset = 0;

	memcpy(buffer + offset, &opcode1, sizeof(opcode1));
	offset += sizeof(opcode1);
	memcpy(buffer + offset, &arg1_1, sizeof(arg1_1));
	offset += sizeof(arg1_1);
	memcpy(buffer + offset, &arg2_1, sizeof(arg2_1));
}

void MapOp::Unmarshal(char * buffer) {
	int opcode1;
	int arg1_1;
	int arg2_1;

	int offset = 0;

	memcpy(&opcode1, buffer + offset, sizeof(opcode1));
	offset += sizeof(opcode1);
	memcpy(&arg1_1, buffer + offset, sizeof(arg1_1));
	offset += sizeof(arg1_1);
	memcpy(&arg2_1, buffer + offset, sizeof(arg2_1));

	opcode = ntohl(opcode1);
	arg1 = ntohl(arg1_1);
	arg2 = ntohl(arg2_1);
}

bool MapOp::IsValid() {
	return (opcode != -1);
}

void MapOp::Print() {
	std::cout << "opcode " << opcode << " ";
	std::cout << "arg1 " << arg1 << " ";
	std::cout << "arg2 " << arg2 << " ";
}

IFAMessage::IFAMessage(){
		is_ifa=-1;
	}
int IFAMessage::Size(){
   return sizeof(is_ifa);
	}

void IFAMessage::SetIsIFA(int p_isIFA){
	is_ifa = p_isIFA;
}

int IFAMessage::GetIsIFA(){
		return is_ifa;
}

bool IFAMessage::IsValid(){
	return (is_ifa != -1);
}

void IFAMessage::Marshal(char *buffer){
 int is_ifa1 = htonl(is_ifa);
	memcpy(buffer, &is_ifa1, sizeof(is_ifa1));
}

void IFAMessage::Unmarshal(char *buffer){
    int is_ifa1;
	memcpy(&is_ifa1, buffer, sizeof(is_ifa1));
	is_ifa = ntohl(is_ifa1);
}
