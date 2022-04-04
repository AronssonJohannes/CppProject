#include "message_handler.h"
#include "connection.h"
#include "string"

#include <vector>

using namespace std;

class Client {
    public:
        Client(const std::shared_ptr<Connection> &con) : mh(con) {make_cmds();}
        void begin();
        
    private:
        MessageHandler mh;
        vector<string> cmds;

        void make_cmds();
        void news_loop();
        void news_stop();
        bool check_ans_error();
        string write_article();
};