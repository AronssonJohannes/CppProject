#include "client.h"
#include "protocol.h"
#include <string>
#include <iostream>

#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void Client::begin(){
    cout << "Welcome to the News Application!" << endl;
    cout << "Commands: list <obj>, add/create <obj>, rm/del <obj>, get/read art" << endl;
    cout << "Objects: ng, art" << endl;
    news_loop();
}

void Client::make_cmds(){
    cmds.push_back("list ng");
    cmds.push_back("create ng");
    cmds.push_back("add ng");
    cmds.push_back("rm ng");
    cmds.push_back("del ng");
    cmds.push_back("list art");
    cmds.push_back("get art");
    cmds.push_back("read art");
    cmds.push_back("create art");
    cmds.push_back("add art");
    cmds.push_back("rm art");
    cmds.push_back("del art");
    cmds.push_back("quit");
    cmds.push_back("stop");
    cmds.push_back("end");

}

string Client:: write_article(){

    string res = "";
    string prev = "";
    string inp;
    while(getline(cin, inp)){
        //cout << "input:" << inp << endl;
        if(inp.compare("q") == 0){
            bool fin = false;
            string tmp;
            cout << "Are you sure you want to finish writing the Article?<Y/n>";
            while(getline(cin, tmp)){
                if(tolower(tmp[0]) == 'y'){
                    fin = true;
                    break;
                } else if(tolower(tmp[0]) == 'n'){
                    break;
                } else {
                     cout << "Are you sure you want to finish writing the Article?<Y/n>";
                }
            }
            if(fin){
                break;
            }
        }
        res = res + inp + "\n";
    }

    cout << "content: " << res << endl;

    return res;
}

void Client::news_loop(){
    bool cont = true;
    while(cont){
        cout << "news$ ";
        string inp;
        //cin >> inp;
        getline(cin, inp);
        int inp_int{0};

        //get index 
        for (string s : cmds){
            if(s.compare(inp) == 0)
                break;
            inp_int++;
        }
        //cout << "input_int: " << inp_int << endl;
        switch (inp_int) {
            case 0  :   //list ng
                try {
                    mh.send_code(Protocol::COM_LIST_NG);
                    mh.send_code(Protocol::COM_END); //ANS_LIST_NG num_p [num_p string_p]* ANS_END
                    check_ans_error();
                    int size = mh.recv_int_parameter();
                    for (int i = 0; i < size; i++){

                        cout << mh.recv_int_parameter() << " - " << mh.recv_string_parameter() << endl;
                    }
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Newsgroups.\n";
                }
                break;

            case 1   :   //create or add ng
            case 2   :
                try {
                    cout << "Choose a Newsgroup Name: ";
                    string para;
                    getline(cin, para);
                    mh.send_code(Protocol::COM_CREATE_NG);
                    mh.send_string_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not add Newsgroup.\n";
                }
                break;

            case 3    :   //rm or del ng
            case 4    :
                try { 
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    string str_para;
                    getline(cin, str_para);
                    para = stoi(str_para);
                    mh.send_code(Protocol::COM_DELETE_NG);
                    mh.send_int_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not delete Newsgroup.\n";
                }
                break;

            case 5      :   //list art
                try {    
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    string str_para;
                    getline(cin, str_para);
                    para = stoi(str_para);
                    mh.send_code(Protocol::COM_LIST_ART);
                    mh.send_int_parameter(para);
                    mh.send_code(Protocol::COM_END);
                    if(check_ans_error()){
                        int size = mh.recv_int_parameter();
                        for (int i = 0; i < size; i++){
                            cout << mh.recv_int_parameter() << "- " << mh.recv_string_parameter() << endl;
                        }
                        check_ans_error();
                    }
                    
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Articles.\n";
                }
                break;

            case 6  :   //get or read art
            case 7  :
                try {
                    cout << "Choose a Newsgroup Number: ";
                    int para;
                    string str_para;
                    getline(cin, str_para);
                    para = stoi(str_para);
                    cout << "Choose a Article Number: ";
                    int para2;
                    string str_para2;
                    getline(cin, str_para2);
                    para2 = stoi(str_para2);
                    mh.send_code(Protocol::COM_GET_ART);
                    mh.send_int_parameter(para);
                    mh.send_int_parameter(para2);
                    mh.send_code(Protocol::COM_END);
                    if(check_ans_error()) {
                        cout << "Title: " << mh.recv_string_parameter() << endl;
                        cout << "Author: " << mh.recv_string_parameter() << endl;
                        cout << "Content: \n" << mh.recv_string_parameter() << endl;
                        check_ans_error();
                    }
                } catch (const std::exception& e) {
                    cout << "Failed: Could not List Articles.\n";
                }
                break;

            case 8      :    //create or add art
            case 9      :
                try {
                    cout << "Choose a Newsgroup Number: ";
                    int para;
                    string str_para;
                    getline(cin, str_para);
                    para = stoi(str_para);
                    cout << "Title: ";
                    string para2;
                    getline(cin, para2);
                    mh.send_code(Protocol::COM_CREATE_ART);
                    mh.send_int_parameter(para);
                    mh.send_string_parameter(para2);
                    cout << "Author: ";
                    string para3;
                    getline(cin, para3);
                    mh.send_string_parameter(para3);
                    cout << "Content (When done, write q and press enter): \n";
                    string para4 = write_article();
                    mh.send_string_parameter(para4);
                    mh.send_code(Protocol::COM_END);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not add Article.\n";
                }
                break;

            case 10    :   //rm or del art
            case 11    :
                try {
                    cout << "Choose a Newsgroup Number:";
                    int para;
                    string str_para;
                    getline(cin, str_para);
                    para = stoi(str_para);
                    cout << "Choose a Article Number:";
                    int para2;
                    string str_para2;
                    getline(cin, str_para2);
                    para2 = stoi(str_para2);
                    mh.send_code(Protocol::COM_DELETE_ART);
                    mh.send_int_parameter(para);
                    mh.send_int_parameter(para2);
                    mh.send_code(Protocol::COM_END);
                    check_ans_error();
                } catch (const std::exception& e) {
                    cout << "Failed: Could not delete Article.\n";
                }
                break;

            case 12     :   //quit or stop
            case 13     :
                cont = false;
                break;


            default :
                cout << "Invalid Input. Please specify object (newsgroup (ng) or article (art)).\n";
        }
    }
}

void Client::news_stop(){
    //TODO
}

bool Client::check_ans_error(){
    Protocol ans = mh.recv_code();
    bool ret = true;
    Protocol topic = ans;
    //cout << "answer: " << static_cast<int>(ans) << endl;
    while(ans != Protocol::ANS_END){
        switch (ans) {
            case Protocol::ANS_LIST_NG:
                cout << "Listing Newsgroups: Successful\n";
                return true;
                break;
            case Protocol::ANS_CREATE_NG:
                cout << "Add Newsgroup: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_DELETE_NG:
                cout << "Deleting Newsgroup: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_LIST_ART:
                cout << "Listing Articles: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_CREATE_ART:
                cout << "Add Article: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_DELETE_ART:
                cout << "Deleting Article: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_GET_ART:
                cout << "Retreiving Article: ";
                ans = mh.recv_code();
                break;
            case Protocol::ANS_ACK:
                cout << "Successful.\n";
                if(topic == Protocol::ANS_CREATE_NG || 
                    topic == Protocol::ANS_DELETE_NG ||
                    topic == Protocol::ANS_CREATE_ART ||
                    topic == Protocol::ANS_DELETE_ART){
                    ans = mh.recv_code();
                } else {
                    ans = Protocol::ANS_END;
                }
                break;
            case Protocol::ANS_NAK:
                cout << "Failed.\n";
                ans = mh.recv_code();
                ret = false;
                break;
            case Protocol::ERR_ART_DOES_NOT_EXIST:
                cout << "Error: Article does not exist.\n";
                ans = mh.recv_code();
                break;
            case Protocol::ERR_NG_ALREADY_EXISTS:
                cout << "Error: Newsgroup already exists.\n";
                ans = mh.recv_code();
                break;
            case Protocol::ERR_NG_DOES_NOT_EXIST:
                cout << "Error: Newsgroup does not exist.\n";
                ans = mh.recv_code();
                break;
        }
            //ans = mh.recv_code();
    }
    return ret;
}

