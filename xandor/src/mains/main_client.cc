#include <iostream>
#include "connection.h"
#include "client.h"

#include <memory>

int main(int argc, char **argv) { //skickar host o port
    //TODO
    if(argc != 3){
        cout << "Missing ip or port-number" << endl;
    } else {
        char* host = argv[1];
        int port = stoi(argv[2]);

        //Connection c(host, port);
        Client client = Client(std::shared_ptr<Connection>(new Connection(host, port)));
        client.begin();
    }
}