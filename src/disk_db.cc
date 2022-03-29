#include "disk_db.h"
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <filesystem>

using std::string;
using std::tuple;

DiskDB::DiskDB(){
    CreateDBInfo();
}

// Checks if db_info exists and creates it if it doesn't
void DiskDB::CreateDBInfo(){
    string info_path = filepath + "/db_info.txt";
    if(!PathExist(info_path)){
        std::ofstream ofstr(info_path.c_str());
        ofstr << "0";
        ofstr.close();
    }
}

bool DiskDB::PathExist(const string &path)
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

std::vector<string> DiskDB::FilesInPath(const string &path){
    DIR *dir;
    struct dirent *diread;
    std::vector<string> files;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(string(diread->d_name));
        }
        closedir (dir);
    } else {
        perror ("opendir");
        std::cout << "error path, FilesInPath" << std::endl;
        // TODO error handling
    }
    return files;
}

tuple<int, string> DiskDB::CreateNGTuple(const string& ng_path){
    int ng_id = stoi(ng_path.substr(3)); // remove "ng_"
    string ng_name = "No name";
    string info_path = ng_path;

    std::ifstream istr(info_path);
    // int next_id; // discard
    // istr >> next_id;
    istr >> ng_name;

return std::make_tuple(ng_id, ng_name);
}

tuple<int, string> DiskDB::CreateATuple(const string& a_path){
    int a_id = stoi(a_path.substr(2)); // remove "a_"
    string a_name = "No name";
    std::ifstream istr(a_path);
    istr >> a_name;

    return std::make_tuple(a_id, a_name);
}

std::vector<tuple<int, string>> DiskDB::list_newsgroups(){
    std::vector<string> all_files = FilesInPath(filepath.c_str());
    std::vector<string> ng_folders;
    std::copy_if (all_files.begin(), all_files.end(), std::back_inserter(ng_folders),
                  [](const string& str){return str.find("ng")==0;} );
 
    std::vector<tuple<int, string>> res;
    std::for_each(ng_folders.begin(), ng_folders.end(), 
        [&](const string& str){res.push_back(CreateNGTuple(str));});
    return res;
}

void DiskDB::create_newsgroup(string name){
    // TODO get next ng_id from db_info
    int id;
    std::ifstream ifstr(filepath + "/db_info.txt");
    ifstr >> id;
    ifstr.close();
    ++id;
    std::ofstream ofstr(filepath + "/db_info.txt");
    ofstr << id;
    ofstr.close();

    string dirname = filepath + "/ng_";
    dirname += std::to_string(id);

    int status = mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    // create ng_info file in the folder
    string info_path = dirname + "/ng_info.txt";
    std::ofstream fstr(info_path.c_str());
    fstr << name;
    fstr.close();

}

void DiskDB::delete_newsgroup(int newsgroup_id){
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    int res = std::remove_all(dir); //Remove all returns nbr deleted items (0 if dir does not exist)
    if (res == 0) { throw NewsgroupException(); }
}

std::vector<tuple<int, string>> DiskDB::list_articles(int newsgroup_id){
    std::vector<tuple<int, string>> res;
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    if(!PathExist(dir)){
        throw NewsgroupException();
    }
    std::vector<string> all_files = FilesInPath(filepath.c_str());
    std::vector<string> articles;
    std::copy_if (all_files.begin(), all_files.end(), std::back_inserter(articles),
                  [](const string& str){return str.find("a_")==0;} );

    std::for_each(articles.begin(), articles.end(), 
        [&](const string& str){res.push_back(CreateATuple(str));});
    
    return res;
}

void DiskDB::create_article(string title, string author, string text, int newsgroup_id){
    string dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    int a_id = 2;
    if (!PathExist(dir)) {
        throw NewsgroupException();
    }
    std::ofstream ofstr(dir + "/a_" + std::to_string(a_id));
    ofstr << a_id << "\n";
    ofstr << title << "\n";
    ofstr << author << "\n";
    ofstr << text;
    ofstr.close();
}

void DiskDB::delete_article(int article_id, int newsgroup_id){
    string file = filepath + "/ng_" + std::to_string(newsgroup_id);
    //if (std::exists())
     + "/a_" + std::to_string(article_id);
    bool res = remove(file)  //returns true if deleted, else false.
    if
}

tuple<string, string, string> DiskDB::get_article(int article_id, int newsgroup_id){
    tuple<string, string, string> res = std::make_tuple("title", "author", "text");

    return res;
}
