#include "message_handler.h"

using std::string;
using enum Protocol;

//MessageHandler(std::shared_ptr<Connection> connection): connection(connection){}
void MessageHandler::send_byte(int code){
    *connection.write(code);
} //throws ConnectionClosedException

void MessageHandler::send_code(int code){
    send_byte(code);
}

void MessageHandler::send_int(int value){
    send_byte((value >> 24) & 0xFF);
    send_byte((value >> 16) & 0xFF);
    send_byte((value >> 8) & 0xFF);
    send_byte(value & 0xFF);
}

void MessageHandler::send_int_parameter(int param){
    send_code(PAR_NUM);
    send_int(param);
}

void MessageHandler::send_string_parameter(String param){
    send_code(PAR_STRING);
    send_int(param.length());
    for(int i{0}; i < param.length(); ++i){
        send_byte(param.at(i));
    }
}

int MessageHandler::recv_byte(){
    return *connection.read();
} // throws ConnectionClosedException

int MessageHandler::recv_code(){
    return recv_byte();
} // throws ConnectionClosedException

int MessageHandler::recv_int(){
    int b1 = recv_byte();
    int b2 = recv_byte();
    int b3 = recv_byte();
    int b4 = recv_byte();
    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
} // throws ConnectionClosedException

int MessageHandler::recv_int_parameter(){
    int code() = recvCode();
    if (code != PAR_NUM) throw ProtocolViolationException("Receive int parameter, wrong code");
    return recv_int();
} // throws ConnectionClosedException

string MessageHandler::recv_string_parameter(){
    int code = recv_code();
    if(code != PAR_STRING){
        throw ProtocolViolationException("Receive string parameter, wrong code");
    }
    int n = recv_int();
    if (n < 0) {
        throw ProtocolViolationException("Receive string parameter, num characters < 0");
    }
    string res = "";
    for(int i = 1; i <= n; ++i){
        char ch = connection.read(); // c cast? or static cast? char ch = (char) conn.read();
        res += ch;
    }
    return res;
    
} // throws ConnectionClosedException