#include "memory_db.h"
#include <algorithm>
#include <iostream>
using std::pair;
using std::vector;
using std::string;
using std::tuple;
using std::endl;


vector<tuple<int, string>> InMemoryDB::list_newsgroups(){
    vector<tuple<int, string>> res;
    for(auto i = db.begin(); i != db.end(); ++i){
        res.emplace_back(i->second.id, i->second.name);
    }
    return res;
}

void InMemoryDB::create_newsgroup(string name){
    auto it = std::find_if(db.begin(), db.end(), 
    [&name](const std::pair<int, newsgroup>& pair){return pair.second.name == name;});
    if(it != db.end()){
        throw NewsgroupException();
    }

    newsgroup ng(next_id, name);
    db[next_id++] = ng;
}

void InMemoryDB::delete_newsgroup(int newsgroup_id){
    if(db.find(newsgroup_id) == db.end()){
        throw NewsgroupException();
    }
    db.erase(newsgroup_id);
}
 
vector<tuple<int, string>> InMemoryDB::list_articles(int newsgroup_id){
    if(db.find(newsgroup_id) == db.end()){
        throw NewsgroupException();
    }
    vector<article> articles = db.at(newsgroup_id).articles;
    vector<tuple<int, string>> res;
    for(auto i = articles.begin(); i != articles.end(); ++i){
        res.emplace_back(i->id, i->title);
    }
    return res;
}

void InMemoryDB::create_article(string title, string author, string text, int newsgroup_id){
    if(db.find(newsgroup_id) == db.end()){
        throw NewsgroupException();
    }
    article a(db.at(newsgroup_id).next_art_id++, author, title, text);
    db[newsgroup_id].articles.push_back(a);
}

void InMemoryDB::delete_article(int article_id, int newsgroup_id){
    if(db.find(newsgroup_id) == db.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id).articles;
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){return art.id == article_id;} );

    if(it == vec.end()){
        throw ArticleException();
    }
    vec.erase(it);
    db.at(newsgroup_id).articles = vec;
}

tuple<string, string, string> InMemoryDB::get_article(int article_id, int newsgroup_id){
    if(db.find(newsgroup_id) == db.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id).articles;
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){return art.id == article_id;});
    
    if(it == vec.end()){
        throw ArticleException();
    }
    return std::make_tuple(it->title, it->author, it->text);
}
