#include <string>

#ifndef PROTOCOL_VIOLATION_EXCEPTION_H
#define PROTOCOL_VIOLATION_EXCEPTION_H

struct ProtocolViolationException{
    ProtocolViolationException (msg) : message(msg){}
    std::string message;
}

#endif