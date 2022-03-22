#ifndef MEMORY_DB
#define MEMORY_DB

#include "database.h"
#include <map>
#include <vector>
#include <string>
#include <utility>


using std::string;
using std::pair;
using std::tuple;

class InMemoryDB : public Database {
    public:
        InMemoryDB();
        //virtual Database();
        std::vector<pair<int, string>> list_newsgroups();
        void create_newsgroup(string name);
        void delete_newsgroup(int newsgroup_id);
        std::vector<tuple<string, string>> list_articles(int newsgroup_id);
        void create_article(string title, string author, string text, int newsgroup_id);
        void delete_article(int article_id, int newsgroup_id);
        tuple<string, string, string> get_article(int article_id, int newsgroup_id);
    private:
        std::map<int, vector<article>> db;
        std::map<int, string> ng_names()
        int next_id{0};
}

#endif