#include "message_handler.h"

using std::string;


void MessageHandler::set_connection(const std::shared_ptr<Connection>& conn) {
    connection = conn;
}

//MessageHandler(std::shared_ptr<Connection> connection): connection(connection){}
void MessageHandler::send_byte(int code){
    connection->write(code);
} //throws ConnectionClosedException

void MessageHandler::send_code(Protocol code){
    send_byte(static_cast<int>(code));
}

void MessageHandler::send_int(int value){
    send_byte((value >> 24) & 0xFF);
    send_byte((value >> 16) & 0xFF);
    send_byte((value >> 8) & 0xFF);
    send_byte(value & 0xFF);
}

void MessageHandler::send_int_parameter(int param){
    send_code(Protocol::PAR_NUM);
    send_int(param);
}

void MessageHandler::send_string_parameter(const string& param){
    send_code(Protocol::PAR_STRING);
    send_int(param.length());
    for(size_t i{0}; i < param.length(); ++i){
        send_byte(param.at(i));
    }
}

int MessageHandler::recv_byte(){
    return connection->read();
} // throws ConnectionClosedException

Protocol MessageHandler::recv_code(){
    Protocol code = static_cast<Protocol>(recv_byte());
    return code;
} // throws ConnectionClosedException

int MessageHandler::recv_int(){
    int b1 = recv_byte();
    int b2 = recv_byte();
    int b3 = recv_byte();
    int b4 = recv_byte();
    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
} // throws ConnectionClosedException

int MessageHandler::recv_int_parameter(){
    Protocol code = static_cast<Protocol>(recv_code());
    if (code != Protocol::PAR_NUM) throw ProtocolViolationException();
    return recv_int();
} // throws ConnectionClosedException

string MessageHandler::recv_string_parameter() {
    Protocol code = static_cast<Protocol>(recv_code());
    if(code != Protocol::PAR_STRING){
        //throw ProtocolViolationException("Receive string parameter, wrong code");
        throw ProtocolViolationException();
    }
    int n = recv_int();
    if (n < 0) {
        //throw ProtocolViolationException("Receive string parameter, num characters < 0");
        throw ProtocolViolationException();
    }
    string res = "";
    for(int i = 1; i <= n; ++i){
        char ch = connection->read(); // c cast? or static cast? char ch = (char) conn.read();
        res += ch;
    }
    return res;
    
} // throws ConnectionClosedException