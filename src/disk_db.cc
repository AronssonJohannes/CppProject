#include "disk_db.h"
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <dirent.h>
#include <filesystem>


namespace fs = std::filesystem;
using std::string;
using std::tuple;

//DiskDB::


// TODO multi word titles, names, etc

// TODO db_info always contains "1" after a run?



// Checks if db_info exists and creates it if it doesn't
void DiskDB::initDB(){
    fs::path p = filepath;
    fs::create_directory(p);
    p += "/db_info.txt";
    if (fs::exists(p)) {
        std::ofstream ofstr(p.c_str());
        ofstr << "0";
        ofstr.close();
    }
}

bool DiskDB::PathExist(const string &path) //Could replace with fs::exists()
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

std::vector<string> DiskDB::FilesInPath(const string &path){ //fs::directory_iterator(path) https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    DIR *dir;
    struct dirent *diread;
    std::vector<string> files;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(string(diread->d_name));
        }
        closedir (dir);
    } else {
       
        // TODO error handling? 
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
    string line;
    std::getline(istr, line); // ng_name
    std::istringstream iss(line);
    ng_name = iss.str();

return std::make_tuple(ng_id, ng_name);
}

tuple<int, string> DiskDB::CreateATuple(const string& a_path){
    int a_id = stoi(a_path.substr(2)); // remove "a_"
    string a_name = "No name";
    std::ifstream istr(a_path);
    string line;
    std::getline(istr, line); // ng_name
    std::istringstream iss(line);
    a_name = iss.str();

    return std::make_tuple(a_id, a_name);
}

// TODO allow no newsgroups to exist? removed throw error in filesinpath
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
    int id;
    std::ifstream ifstr(filepath + "/db_info.txt");
    ifstr >> id;
    ifstr.close();
    int next_id = id + 1;
    std::ofstream ofstr(filepath + "/db_info.txt");
    ofstr << next_id;
    ofstr.close();

    string dirname = filepath + "/ng_";
    dirname += std::to_string(id);

    mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); //fs::create_directory
    // create ng_info file in the folder
    string info_path = dirname + "/ng_info.txt";
    std::ofstream fstr(info_path.c_str());
    fstr << name << "\n";
    fstr << 0;
    fstr.close();

}

void DiskDB::delete_newsgroup(int newsgroup_id){
    fs::path dir = filepath + "/ng_" + std::to_string(newsgroup_id);
    if (fs::remove_all(dir) == 0) { throw NewsgroupException(); } //remove_all() returns how many were removed, zero if directory never existed
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
    int a_id;
    string ng_name;
    std::ifstream ifstr(filepath + "/ng_info.txt");
    string line;
    std::getline(ifstr, line); // ng_name
    std::istringstream iss(line);
    ng_name = iss.str();

    ifstr >> a_id;
    ifstr.close();
    int next_a_id = a_id + 1;
    std::ofstream ofstr(filepath + "/ng_info.txt"); // Truncates by default
    ofstr << ng_name << "\n";
    ofstr << next_a_id;
    ofstr.close();
    if (!PathExist(dir)) {
        throw NewsgroupException();
    }
    std::ofstream ofstr2(dir + "/a_" + std::to_string(a_id));
    ofstr2 << a_id << "\n";
    ofstr2 << title << "\n";
    ofstr2 << author << "\n";
    ofstr2 << text;
    ofstr2.close();
}

void DiskDB::delete_article(int article_id, int newsgroup_id){
    fs::path file = filepath + "/ng_" + std::to_string(newsgroup_id)
            + "/a_" + std::to_string(article_id); 
    if (!fs::remove(file)) { throw ArticleException(); } //remove() returns true if deleted, else false.
}

tuple<string, string, string> DiskDB::get_article(int article_id, int newsgroup_id){
    tuple<string, string, string> res = std::make_tuple("title", "author", "text");
    string a_path = filepath +"/ng_" + std::to_string(newsgroup_id) + "/a_" + std::to_string(article_id);
    std::ifstream istr(a_path);
    if(!istr){
         throw ArticleException(); 
    }
    string line;
    std::getline(istr, line); // id
    std::getline(istr, line); // title
    std::istringstream iss(line);
    string title = iss.str();
    std::getline(istr, line); // author
    std::istringstream iss2(line);
    string author = iss2.str();
    
    string text;
    std::stringstream buffer;
    buffer << istr.rdbuf();
    text = buffer.str();
    return std::make_tuple(title, author, text);
}
