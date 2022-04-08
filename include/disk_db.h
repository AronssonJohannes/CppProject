#ifndef DISK_DB
#define DISK_DB

#include "database.h"
#include <vector>
#include <string>
#include <utility>


using std::string;
using std::tuple;

class DiskDB : public Database {
    public:
        DiskDB(){initDB();}

        std::vector<tuple<int, string>> list_newsgroups();
        void create_newsgroup(string name);
        void delete_newsgroup(int newsgroup_id);
        std::vector<tuple<int, string>> list_articles(int newsgroup_id);
        void create_article(string title, string author, string text, int newsgroup_id);
        void delete_article(int article_id, int newsgroup_id);
        tuple<string, string, string> get_article(int article_id, int newsgroup_id);
    private:
        string filepath = "./database";
        void initDB();
};
#endif
