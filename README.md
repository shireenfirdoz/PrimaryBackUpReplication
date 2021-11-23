# PrimaryBackUpReplication

Software Design Summary: I have implemented the customer records using a map with attributes key
which is the customer id, and the value is the last order number of the customer. A state machine log to
keep track of our operations of the customer records so I have MapOp and it has been constructed using
struct which contains the opcode, customer id (arg1), and parameter for the operation(arg2). The state
machine replication log is a vector of MapOp.I have created another stub to communicate with
the replicas and copy the log from primary to replicas

How To Run : running client machine along with 1 primary and 2 backup server :

./server 12345 0 2 1 10.200.125.60 12345 2 10.200.125.59 12345

./server 12345 1 2 0 10.200.125.61 12345 2 10.200.125.59 12345

./server 12345 2 2 0 10.200.125.61 12345 1 10.200.125.60 12345

./client 10.200.125.61 12345 2 5 1
