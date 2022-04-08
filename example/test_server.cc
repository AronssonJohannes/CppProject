
#include <iostream>
#include "connection.h"
#include "message_handler.h"
#include "protocol.h"

#include <memory>

using namespace std;

void test_protocol(MessageHandler& mh){
    mh.send_code(Protocol::COM_LIST_NG);
    mh.send_string_parameter("HELLO");
    mh.send_code(Protocol::COM_LIST_NG);
}

int main(int argc, char **argv) { 
    if(argc != 3){
        cout << "Not enough arguments" << endl;
    } else {
        char* host = argv[1];
        int port = stoi(argv[2]);
        MessageHandler mh(std::shared_ptr<Connection>(new Connection(host, port)));
        test_protocol(mh);
    }
}