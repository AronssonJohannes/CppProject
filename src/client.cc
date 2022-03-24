#include "client.h"
#include "protcol.h"
#include "string"

using std::cout;
using std::cin;
using std::endl;
using std::string

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
                try {
                    mh.send_code(Protocol::COM_LIST_NG);
                    mh.send_code(Protocol::COM_END); //ANS_LIST_NG num_p [num_p string_p]* ANS_END
                    check_ans_error();
                    int size = mh.recv_code();
                    for (int i = 0; i < size; i++){
                        cout << i << "- " << mh.recv_string_parameter() << endl;
                    }
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Newsgroups.\n";
                }
                break;

            case "create ng":
            case "add ng"   :
                try {
                    mh.send_code(Protocol::COM_CREATE_NG);
                    cout << "Choose a Newsgroup Name: ";
                    string para;
                    cin >> para;
                    mh.send_string_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not add Newsgroup.";
                }
                break;

            case "rm ng"    :
            case "del ng"   :
                try {
                    mh.send_code(Protocol::COM_DELETE_NG);
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not delete Newsgroup.";
                }
                break;

            case "list art" :
                try {
                    mh.send_code(Protocol::COM_LIST_ART);
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    check_ans_error();
                    int size = mh.recv_code();
                    for (int i = 0; i < size; i++){
                        cout << i << "- " << mh.recv_string_parameter() << endl;
                    }
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Articles.\n";
                }
                break;

            case "get art"  :
            case "read art" :
                try {
                    mh.send_code(Protocol::COM_GET_ART);
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    endl(cout);
                    cout << "Choose a Article Number:";
                    int para2;
                    cin >> para2;
                    mh.send_int_parameter(para2);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    mh.recv_code(); // Protocol::ANS_GET_ART
                    cout << "List of Articles: ";
                    if(mh.recv_code() == Protocol::ANS_ACK) {
                        cout << "Successful.\n";
                        cout << "Title: " << mh.recv_string_parameter << endl;
                        cout << "Author: " << mh.recv_string_parameter << endl;
                        cout << "Content: \n" << mh.recv_string_parameter << endl;
                    } else {
                        cout << "Failed.\n";
                        check_ans_error();
                    }
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Articles.\n";
                }
                break;

            case "create art"   :
            case "add art"  :
                try {
                    mh.send_code(Protocol::COM_CREATE_NG);
                    cout << "Choose a Newsgroup Number: ";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    endl(cout);
                    cout << "Title: ";
                    string para2;
                    cin >> para2;
                    mh.send_string_parameter(para2);
                    endl(cout);
                    cout << "Author: ";
                    string para3;
                    cin >> para3;
                    mh.send_string_parameter(para3);
                    endl(cout);
                    cout << "Content: \n";
                    string para4;
                    cin >> para4;
                    mh.send_string_parameter(para4);
                    endl(cout);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not add Newsgroup.";
                }
                break;

            case "rm art"   :
            case "del art"  :
                try {
                    mh.send_code(Protocol::COM_DELETE_ART);
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    endl(cout);
                    cout << "Choose a Article Number:";
                    int para;
                    cin >> para;
                    mh.send_int_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    endl(cout);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not delete Article.";
                }
                break;

            case "quit"     :
            case "stop"     :
                stop();
                cont = false;
                break;


            default :
                cout << "Invalid Input. Please specify object (newsgroup (ng) or article (art)).\n";
                cout << "Example: add ng\n";
        }
        << endl;
    }
}

Client::stop(){
//TODO
}

Client::check_ans_error(){
    int ans = mh.recv_code();
        while(ans != Protocol::ANS_END){
            switch (ans) {
                case Protocol::ANS_LIST_NG:
                    cout << "Listing Newsgroups:\n";
                    ans = Protocol::ANS_END;
                    break;
                case Protocol::ANS_CREATE_NG:
                    cout << "Add Newsgroup: ";
                    break;
                case Protocol::ANS_DELETE_NG:
                    cout << "Deleting Newsgroup: ";
                    break;
                case Protocol::ANS_LIST_ART:
                    cout << "Listing Articles:\n";
                    ans = Protocol::ANS_END;
                    break;
                case Protocol::ANS_CREATE_ART:
                    cout << "Add Article: ";
                    break;
                case Protocol::ANS_DELETE_ART:
                    cout << "Deleting Article: ";
                    break;
                case: Protocol::ANS_GET_ART:
                    cout << "Retreiving Article: ":
                    break;
                case Protocol::ANS_ACK:
                    cout << "Successful.\n";
                    break;
                case Protocol::ANS_NACK:
                    cout << "Failed.\n";
                    break;
                case Protocol::ERR_ART_DOES_NOT_EXIST:
                    cout << "Error: Article does not exist.\n";
                    break;
                case Protocol::ERR_NG_ALREADY_EXISTS:
                    cout << "Error: Newsgroup already exists.\n";
                    break;
                case Protocol::ERR_NG_DOES_NOT_EXIST:
                    cout << "Error: Newsgroup does not exist.\n";
                    break;
            }
            ans = mh.recv_code();
        }
}

int main(int argc, char **argv) { //skickar host o port
    //TODO
    char* host = "bob";
    int port = 8888;

    Connection c(host, port);
    Client client(c);
    client.start();
}