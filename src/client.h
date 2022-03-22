#include "message_handler.h"
#include "connection.h"

class Client {
    public:
        Client(Connection& con);
        
        void start();
        void loop()
        void stop();
        void send_recv();
    private:
        MessageHandler mh;
}