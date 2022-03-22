#ifndef DISK_DB
#define DISK_DB

#include "database.h"

class Disk_database: public Database {
    Disk_database();
    void read();
    void write();
    void del();
}

#endif