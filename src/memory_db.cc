#include "memory_db.h"

using std::pair;
using std::vector;


InMemoryDB::InMemoryDB(){

}

vector<pair<int, string>> InMemoryDB::list_newsgroups(){
    vector<pair<int, string>> v;
    for(auto i = db.begin(); i != db.end(); ++i){
        v.push_back(make_pair<int, string>(*i, db.at(*i)));
    }
    return v;
}

void InMemoryDB::create_newsgroup(string name){
    vector<article> v;
    db.insert(make_pair<int, string>(next_id++, name), v)
}

void InMemoryDB::delete_newsgroup(int newsgroup_id){
    db.erase()
}

std::vector<tuple<string, string>> InMemoryDB::list_articles(int newsgroup_id){
    
}

void InMemoryDB::create_article(string title, string author, string text, int newsgroup_id){
    
}

void InMemoryDB::delete_article(int article_id, int newsgroup_id){
    
}

tuple<string, string, string> InMemoryDB::get_article(int article_id, int newsgroup_id){
    
}
