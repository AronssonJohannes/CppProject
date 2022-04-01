#include "ourserver.h"
#include "disk_db.h"

int main(int argc, char* argv[])
{
    //  using namespace Server; //Maybe??

    DiskDB db;
    OurServer s(db, argc, argv);
    s.run();
}