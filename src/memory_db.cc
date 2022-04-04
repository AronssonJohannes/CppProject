#include "memory_db.h"
#include <algorithm>
#include <iostream>
using std::pair;
using std::vector;
using std::string;
using std::tuple;
using std::cout;
using std::endl;


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
    // db.insert(std::make_pair<int, vector<article>>(next_id, v));
    ng_names[next_id] = name;
    // ng_names.insert(std::make_pair<int, string>(next_id, name));
    next_a_ids[next_id++] = 0;
    // next_a_ids.insert(std::make_pair<int, int>(next_id++, 0));
}

void InMemoryDB::delete_newsgroup(int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    db.erase(newsgroup_id);
    ng_names.erase(newsgroup_id);
    next_a_ids.erase(newsgroup_id);
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
    article a(next_a_ids.at(newsgroup_id)++, author, title, text);
    db[newsgroup_id].push_back(a);
}

void InMemoryDB::delete_article(int article_id, int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id);
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){return art.id == article_id;} );

    cout << article_id << endl;
    if(it == vec.end()){
        throw ArticleException();
    }
    cout << "it = " << it->title << endl;
    vec.erase(it);
    db.at(newsgroup_id) = vec;
    // db.at(newsgroup_id).erase(it);
}

tuple<string, string, string> InMemoryDB::get_article(int article_id, int newsgroup_id){
    if(ng_names.find(newsgroup_id) == ng_names.end()){
        throw NewsgroupException();
    }
    auto vec = db.at(newsgroup_id);
    auto it = std::find_if(vec.begin(), vec.end(), 
            [article_id](const article& art){return art.id == article_id;});
    
    cout << article_id << endl;
    if(it == vec.end()){
        throw ArticleException();
    }
    return std::make_tuple(it->title, it->author, it->text);
}
