#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"
#include "connection.h"

#include <memory>
#include <string>


class MessageHandler {
    public:
        MessageHandler(const std::shared_ptr<Connection>& connection): connection(connection){}
        void send_code(int code);
        void send_int(int value);
        void send_int_parameter(int param);
        void send_string_parameter(const std::string& param);
        int recv_code(); // throws ConnectionClosedException
        int recv_int(); // throws ConnectionClosedException
        int recv_int_parameter(); // throws ConnectionClosedException
        std::string recv_string_parameter(); // throws ConnectionClosedException
    private:
        std::shared_ptr<Connection> connection;
        void send_byte(int code); //throws ConnectionClosedException
        int recv_byte(); // throws ConnectionClosedException
}

#endif