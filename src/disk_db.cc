#include "disk_db.h"
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>

using std::string;
using std::tuple;

DiskDB::DiskDB(){}

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
            std::cout << diread->d_name << std::endl;
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

tuple<int, string> CreateNGTuple(const string& ng_path){
  int ng_id = stoi(ng_path.substr(3)); // remove "ng_"
  string ng_name = "name"; // TODO
  std::cout << ng_id << ng_name << std::endl;
  return std::make_tuple(ng_id, ng_name);
}

std::vector<tuple<int, string>> DiskDB::list_newsgroups(){
    std::cout << "Path Exist: " << PathExist(filepath) << std::endl;
    std::cout << "FilesInPath: "<< std::endl;
    std::vector<string> all_files = FilesInPath(filepath.c_str());
    std::vector<string> ng_folders;
    std::copy_if (all_files.begin(), all_files.end(), std::back_inserter(ng_folders),
                  [](const string& str){return str.find("ng")==0;} );
    for(auto i = ng_folders.begin(); i != ng_folders.end(); ++i){
        std::cout << (*i) << std::endl;
    }
    std::vector<tuple<int, string>> res;
    std::transform(ng_folders.begin(), ng_folders.end(), res.begin(),
                  [](const string& str){  std::cout << "str "<< str << std::endl; return CreateNGTuple(str);});
    std::cout << "post_t" << std::endl; // not reached, segnentation fault, why?
    return res;
}

void DiskDB::create_newsgroup(string name){

}

void DiskDB::delete_newsgroup(int newsgroup_id){

}

std::vector<tuple<int, string>> DiskDB::list_articles(int newsgroup_id){
    std::vector<tuple<int, string>> res;

    return res;
}

void DiskDB::create_article(string title, string author, string text, int newsgroup_id){

}

void DiskDB::delete_article(int article_id, int newsgroup_id){

}

tuple<string, string, string> DiskDB::get_article(int article_id, int newsgroup_id){
    tuple<string, string, string> res = std::make_tuple("title", "author", "text");

    return res;
}
