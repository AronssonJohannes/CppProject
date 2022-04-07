#include "ourserver.h"
#include "memory_db.h"

int main(int argc, char* argv[])
{
    InMemoryDB db;
    OurServer s(db, argc, argv);
    s.run();
}