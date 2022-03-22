#ifndef DATABASE
#define DATABASE

#include <string>
#include <utility>
#include <tuple>

using std::string;
using std::pair;
using std::tuple;

class Database {
    public:
        Database();
        virtual std::vector<pair<int, string>> list_newsgroups();
        virtual void create_newsgroup(string name);
        virtual void delete_newsgroup(int newsgroup_id);
        virtual std::vector<tuple<string, string>> list_articles(int newsgroup_id);
        virtual void create_article(string title, string author, string text, int newsgroup_id);
        virtual void delete_article(int article_id, int newsgroup_id);
        virtual tuple<string, string, string> get_article(int article_id, int newsgroup_id);
}

#endif