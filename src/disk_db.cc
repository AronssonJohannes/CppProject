#include "disk_db.h"
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <filesystem>

namespace fs = std::filesystem;
using std::string;
using std::tuple;
using std::vector;

//DiskDB::


// TODO multi word titles, names, etc

// TODO db_info always contains "1" after a run?



// Checks if db_info exists and creates it if it doesn't
void DiskDB::initDB(){
    fs::create_directory(filepath);
    string p = filepath + "/db_info";
    if (!fs::exists(p)) {
        std::ofstream ofstr(p);
        ofstr << "0";
        ofstr.close();
    }
}

// TODO allow no newsgroups to exist? removed throw error in filesinpath
vector<tuple<int, string>> DiskDB::list_newsgroups(){
    vector<tuple<int, string>> newsgroups;
    for (const auto& dir_entry : fs::recursive_directory_iterator(filepath)) {
        fs::path file = dir_entry.path();
        if (file.filename() == "ng_info") {
            std::ifstream istr(file.relative_path());
            string ng_id;
            string ng_name;
            std::getline(istr, ng_id);
            std::getline(istr, ng_name);
            newsgroups.emplace_back(stoi(ng_id), ng_name);
        }
    }
    return newsgroups;
}

void DiskDB::create_newsgroup(string name){
    vector<tuple<int, string>> newsgroups = list_newsgroups();
    auto it = std::find_if(newsgroups.begin(), newsgroups.end(),
            [&name](const auto& tup){ return std::get<string>(tup) == name; });
    if (it != newsgroups.end()) {
        throw NewsgroupException();
    }

    int id;
    std::ifstream ifstr(filepath + "/db_info");
    ifstr >> id;
    ifstr.close();

    string dirname = filepath + "/ng_" + std::to_string(id);

    if (fs::create_directory(dirname)) {
        std::ofstream ofstr(filepath + "/db_info");
        ofstr << (id + 1); //next id
        ofstr.close();

        string info_path = dirname + "/ng_info";
        std::ofstream fstr(info_path.c_str());
        fstr << id << "\n";
        fstr << name << "\n";
        fstr << 0;
        fstr.close();
    } else {
        throw NewsgroupException();
    }
}

void DiskDB::delete_newsgroup(int newsgroup_id){
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    if (fs::remove_all(dir) == 0) { throw NewsgroupException(); } //remove_all() returns how many were removed, zero if directory never existed
}

vector<tuple<int, string>> DiskDB::list_articles(int newsgroup_id){
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    if(!fs::exists(dir)){
        throw NewsgroupException();
    }

    vector<tuple<int, string>> articles;
    for (const auto& dir_entry : fs::directory_iterator(dir)) {
        fs::path file = dir_entry.path();
        if (file.filename() != "ng_info") {
            std::ifstream istr(file.relative_path());
            string a_id;
            string a_name;
            std::getline(istr, a_id);
            std::getline(istr, a_name);
            articles.emplace_back(stoi(a_id), a_name);
        }
    }
    return articles;
}


void DiskDB::create_article(string title, string author, string text, int newsgroup_id){
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);

    if (!fs::exists(dir)) {
        throw NewsgroupException();
    }

    int a_id;
    int ng_id;
    string ng_name;
    std::ifstream ifstr(dir + "/ng_info");
    ifstr >> ng_id;
    std::getline(ifstr, ng_name);
    ifstr >> a_id;
    ifstr.close();

    std::ofstream ofstr(dir + "/ng_info"); // Truncates by default
    ofstr << ng_id << "\n";
    ofstr << ng_name << "\n";
    ofstr << a_id + 1; //next a_id
    ofstr.close();

    std::ofstream ofstr2(dir + "/a_" + std::to_string(a_id));
    ofstr2 << a_id << "\n";
    ofstr2 << title << "\n";
    ofstr2 << author << "\n";
    ofstr2 << text;
    ofstr2.close();
}

void DiskDB::delete_article(int article_id, int newsgroup_id){
    string file = filepath + "/ng_" + std::to_string(newsgroup_id);
    if (!fs::exists(file)) { throw NewsgroupException(); } //if the news group dir doesn't exist
    file += "/a_" + std::to_string(article_id); 
    if (!fs::remove(file)) { throw ArticleException(); } //remove() returns true if deleted, else false.
}

tuple<string, string, string> DiskDB::get_article(int article_id, int newsgroup_id){
    string a_path = filepath +"/ng_" + std::to_string(newsgroup_id) + "/a_" + std::to_string(article_id);
    std::ifstream istr(a_path);
    if(!istr){
         throw ArticleException(); 
    }
    string title;
    string author;
    string text;

    std::getline(istr, title); // skip id
    std::getline(istr, title); // title
    std::getline(istr, author); // author
    
    std::stringstream buffer;
    buffer << istr.rdbuf();
    text = buffer.str();
    return std::make_tuple(title, author, text);
}
