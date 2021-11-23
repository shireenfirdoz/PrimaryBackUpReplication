#ifndef __REPLICA_H__
#define __REPLICA_H__

#include <string>
class Replica {
private:
	int id;
	std::string ip;
	int port;
	bool status;
public:
    Replica();
    Replica(int p_id, std::string p_ip, int p_port);
    void SetId(int p_id);
    void SetIp(std::string p_ip);
    void SetPort(int p_port);
	void SetStatus(bool state);
	bool GetStatus();
    int GetId();
    std::string GetIp();
    int GetPort();
};


#endif // #ifndef __MESSAGES_H__
