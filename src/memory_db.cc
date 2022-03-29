#include "memory_db.h"
#include <algorithm>
using std::pair;
using std::vector;
using std::string;
using std::tuple;


vector<tuple<int, string>> InMemoryDB::list_newsgroups(){
    vector<tuple<int, string>> res;
    for(auto i = ng_names.begin(); i != ng_names.end(); ++i){
        res.emplace_back(i->first, i->second);
    }
    return res;
}

void InMemoryDB::create_newsgroup(string name){
    // check if name already exists
    auto it = std::find_if(ng_names.begin(), ng_names.end(), 
    [&name](const std::pair<int, string>& pair){return pair.second == name;});
    if(it != ng_names.end()){
        throw NewsgroupException();
    }
    vector<article> v;
    db[next_id] = v;
    ng_names[next_id++] = name;
}

void InMemoryDB::delete_newsgroup(int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    db.erase(newsgroup_id);
    ng_names.erase(newsgroup_id);
}
 
vector<tuple<int, string>> InMemoryDB::list_articles(int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    vector<article> articles = db.at(newsgroup_id);
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
    article a(next_art_id++, author, title, text);
    db[newsgroup_id].push_back(a);
}

// 0 allt funkar, >0 newsgroup finns ej, <0 article finns ej
void InMemoryDB::delete_article(int article_id, int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id);
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){ return art.id == article_id;} );

    if(it == vec.end()){
        throw ArticleException();
    }
    db.at(newsgroup_id).erase(it);
}

// error: no matching function for call to ‘find_if(std::vector<InMemoryDB::article>::iterator, std::vector<InMemoryDB::article>::iterator, InMemoryDB::delete_article(int, int)::<lambda(const InMemoryDB::article&)>, std::vector<InMemoryDB::article>::iterator)’
//    64 |             [article_id](const article& article){return article.id == article_id;}, vec.end());

tuple<string, string, string> InMemoryDB::get_article(int article_id, int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id);
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){return art.id == article_id;});
    if(it == vec.end()){
        throw ArticleException();
    }
    return std::make_tuple(it->title, it->author, it->text);
}
