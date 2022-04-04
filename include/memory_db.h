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
            article& operator=(const article&)=default;
            // article& operator=(article a){  //article operator=(const article&)=default
            //     swap(id, a.id);
            //     swap(author, a.author);
            //     swap(title, a.title);
            //     swap(text, a.text);
            //     return *this;
            // }
            int id;
            string author;
            string title;
            string text;
        };
        // struct newsgroup{
        //     newsgroup(string n) : name(n) {}
        //     int id;
        //     string name;
        //     next_art_id{0};
        //     set<article> articles;
        // };
    public:
        InMemoryDB(){}
        
        //virtual Database();
        std::vector<tuple<int, string>> list_newsgroups();
        void create_newsgroup(string name);
        void delete_newsgroup(int newsgroup_id);
        std::vector<tuple<int, string>> list_articles(int newsgroup_id);
        void create_article(string title, string author, string text, int newsgroup_id);
        void delete_article(int article_id, int newsgroup_id);
        tuple<string, string, string> get_article(int article_id, int newsgroup_id);
    private:
        std::map<int, std::vector<article>> db;
        std::map<int, string> ng_names;
        // std::map<int, newsgroup> db;
        std::map<int, int> next_a_ids;
        int next_id{0};
        // int next_art_id{0}; //
        // TODO: ovan var inte felet, artikeln försvinner för delete article 0 och article 0 är kvar
};


#endif