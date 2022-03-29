#include "ourserver.h"
#include "memory_db.h"

int main(int argc, char* argv[])
{
    //  using namespace Server; //Maybe??

    InMemoryDB db;
    OurServer s(db, argc, argv);
    s.run();
}