 #include "Replica.h"
 
 Replica::Replica() {
    id = -1;
    ip = "";
    port = -1;
    status = true;
 }

Replica::Replica(int p_id, std::string p_ip, int p_port) {
    id = p_id;
    ip = p_id;
    port = p_port;
}

void Replica::SetId(int p_id) {
    id = p_id;
}
void Replica::SetIp(std::string p_ip) {
    ip = p_ip;
}
void Replica::SetPort(int p_port) {
    port = p_port;
}

void Replica::SetStatus(bool state) {
  status = state;
}

bool Replica::GetStatus() {
  return status;
}

int Replica::GetId() {
    return id;
}
std::string Replica::GetIp() {
    return ip;
}
int Replica::GetPort() {
    return port;
}
