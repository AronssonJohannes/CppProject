#ifndef OUR_SERVER_H
#define OUR_SERVER_H

#include "server.h"

class OurServer{
    public:
        OurServer(Database database, int argc, char* argv[]): db(database), s(init(argc, argv)){}
        Server init(int argc, char* argv[]);
        void run();
        void com_end();
    private:
        MessageHandler mh;
        Database db;
        Server s;
    
}
#endif