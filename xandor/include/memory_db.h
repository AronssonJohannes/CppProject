#ifndef MEMORY_DB
#define MEMORY_DB

#include "database.h"
#include <map>
#include <vector>
#include <string>
#include <utility>


using std::string;
using std::tuple;
using std::swap;

class InMemoryDB : public Database {
    private:
        struct article{
            article(int i, string a, string ti, string te): id{i}, author{a}, title{ti}, text{te}{}
            int id;
            string author;
            string title;
            string text;
        };
        struct newsgroup{
            newsgroup(){}
            newsgroup(int i, string n): id(i), name(n) {}
            int id;
            string name;
            int next_art_id{0};
            std::vector<article> articles;
        };
    public:
        InMemoryDB(){}
        std::vector<tuple<int, string>> list_newsgroups();
        void create_newsgroup(string name);
        void delete_newsgroup(int newsgroup_id);
        std::vector<tuple<int, string>> list_articles(int newsgroup_id);
        void create_article(string title, string author, string text, int newsgroup_id);
        void delete_article(int article_id, int newsgroup_id);
        tuple<string, string, string> get_article(int article_id, int newsgroup_id);
    private:
        std::map<int, newsgroup> db;
        int next_id{0};
};


#endif