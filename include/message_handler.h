#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "protocol.h"
#include "connection.h"
#include "exceptions.h"

#include <memory>
#include <string>


class MessageHandler {
    public:
        MessageHandler(const std::shared_ptr<Connection>& conn): connection(conn){}
        MessageHandler(): connection{std::make_shared<Connection>()} {}
        void set_connection(const std::shared_ptr<Connection>& conn);
        void send_code(Protocol code);
        void send_int(int value);
        void send_int_parameter(int param);
        void send_string_parameter(const std::string& param);
        Protocol recv_code(); // throws ConnectionClosedException
        int recv_int(); // throws ConnectionClosedException
        int recv_int_parameter(); // throws ConnectionClosedException
        std::string recv_string_parameter(); // throws ConnectionClosedException
    private:
        std::shared_ptr<Connection> connection;
        void send_byte(int code); //throws ConnectionClosedException
        int recv_byte(); // throws ConnectionClosedException
};

#endif