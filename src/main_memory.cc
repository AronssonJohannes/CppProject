#include "ourserver.h"

int main(int argc, char* argv[])
{
    //  using namespace Server; //Maybe??

    memory_db db;
    OurServer s(db, argc, argv);
    s.run();
}