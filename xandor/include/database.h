#ifndef DATABASE
#define DATABASE

#include <string>
#include <utility>
#include <tuple>
#include <vector>
#include "exceptions.h"

using std::string;
using std::tuple;

class Database {
    public:
        Database() {}
        // returns a list of tuples with newsgroup id and group title
        virtual std::vector<tuple<int, string>> list_newsgroups()= 0;
        // title as parameter
        virtual void create_newsgroup(string name)=0;
        virtual void delete_newsgroup(int newsgroup_id)=0;
        // returns a list of tuples containing article id and article title
        virtual std::vector<tuple<int, string>> list_articles(int newsgroup_id)=0;
        virtual void create_article(string title, string author, string text, int newsgroup_id)=0;
        virtual void delete_article(int article_id, int newsgroup_id)=0;
        virtual tuple<string, string, string> get_article(int article_id, int newsgroup_id)=0;
};

#endif