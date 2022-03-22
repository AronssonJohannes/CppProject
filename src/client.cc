#include "client.h"
#include "protcol.h"
#include "string"

using std::cout;
using std::cin;
using std::endl;
using std::string

struct P  {
    using enum Protocol;
};

Client::Client(Connection& con){
    mh(con);
}

Client::start(){
    cout << "Welcome to the News Application!" << endl;
    loop();
}

Client::loop(){
    bool cont = true;
    while(cont){
        cout << "news $";
        string inp;
        cin >> inp;
        switch (inp) {
            case "list ng"  :
                //TODO
                break;

            case "add ng"   :
                try {
                    mh.send_code(P.COM_CREATE_NG);
                    cout << "Choose a Newsgroup Name:"
                    string para;
                    mh.send_string_parameter(cin >> para);
                    mh.send_code(P.COM_END);
                    cout << "Successful: Added Newsgroup."
                } catch (const std::exception& e) {
                    cout << "Failed: Could not add Newsgroup."
                }
                break;

            case "del ng"   :
                //TODO
                break;

            case "list art" :
                //TODO
                break;

            case "read art" :
                //TODO
                break;

            case "del art"  :
                //TODO
                break;

            case "stop"     :
                stop();
                //TODO
                break;


            default :
                cout << "Invalid Input. Please specify object (newsgroup (ng) or article (art)).\n";
                cout << "Example: add ng\n";
        }
        << endl;
    }
}

Client::send_recv(){
//TODO
}

Client::stop(){
//TODO
}

int main(int argc, char **argv) { //skickar host o port
    //TODO
    char* host = "bob"
    int port = 1234

    Connection c(host, port)
    Client client(c);
    client.start()
}