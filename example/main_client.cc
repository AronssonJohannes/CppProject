#include <iostream>
#include "connection.h"
#include "client.cc"

#include <memory>

int main(int argc, char **argv) { //skickar host o port
    //TODO
    if(argc != 3){
        cout << "Not enough arguments" << endl;
    }
    char* host = argv[1];
    int port = stoi(argv[2]);

    //Connection c(host, port);
    Client client = Client(std::shared_ptr<Connection>(new Connection(host, port)));
    client.begin();
}