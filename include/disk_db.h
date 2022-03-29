#ifndef MEMORY_DB
#define MEMORY_DB

#include "database.h"
#include <vector>
#include <string>
#include <utility>


using std::string;
using std::tuple;

class DiskDB : public Database {
    public:
        DiskDB();

        std::vector<tuple<int, string>> list_newsgroups();
        void create_newsgroup(string name);
        void delete_newsgroup(int newsgroup_id);
        std::vector<tuple<int, string>> list_articles(int newsgroup_id);
        void create_article(string title, string author, string text, int newsgroup_id);
        void delete_article(int article_id, int newsgroup_id);
        tuple<string, string, string> get_article(int article_id, int newsgroup_id);
    private:
        string filepath = "./database";
        bool PathExist(const string &path);
        tuple<int, string> CreateNGTuple(const string& ng_path);
        tuple<int, string> CreateATuple(const string& a_path);
        std::vector<string> FilesInPath(const string &path);
        void CreateDBInfo();
        //tuple<int, string> CreateNGTuple(const string& ng_path);
};

/* file structure:

database
    db_info - "next_ng_id"
    ng_0
        ng_info - "name, next_a_id"
        a_0 - "id, title, author, text"
        a_2 - "id, title, author, text"
    ng_3 - "name, next_id"
        ng_info - "name, next_a_id"
        a_1 - "id, title, author, text"
        a_2 - "id, title, author, text"
        a_5 - "id, title, author, text"
        a_7 - "id, title, author, text"

*/
#endif
