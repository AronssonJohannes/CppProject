#ifndef OUR_SERVER_H
#define OUR_SERVER_H

#include "server.h"
#include "message_handler.h"
#include "exceptions.h"
#include "connectionclosedexception.h"


class OurServer{
    public:
        OurServer(Database& database, int argc, char* argv[]): db(database), s(init(argc, argv)){}
        void run();
    private:
        MessageHandler mh;
        Database& db;
        Server s;
        Server init(int argc, char* argv[]);
        void com_end();
};

#endif