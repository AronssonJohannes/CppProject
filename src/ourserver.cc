

Server OurServer::init(int argc, char* argv[])
{
        if (argc != 2) 
        {
                cerr << "Usage: ourserver port-number" << endl;
                exit(1);
        }

        int port = -1;
        try 
        {
                port = std::stoi(argv[1]);
        } catch (std::exception& e) {
                cerr << "Wrong format for port number. " << e.what() << endl;
                exit(2);
        }

        Server server(port);
        if (!server.isReady()) 
        {
                cerr << "Server initialization error." << endl;
                exit(3);
        }
        return server;
}

void OurServer::com_end()
{
    if (mh.recv_code() != Protocol::COM_END)
    {
        throw ProtocolViolationException();
    } // COM_END EXPECTED
}

void OurServer::run()
{
    // Catch protocolviolation
    for (;;)
    {
        std::shared_ptr<Connection> conn = waitForActivity();
        if (!conn)
        {
            conn = std::shared_ptr<Connection>(new Connection());
            //: error: no matching function for call to ‘std::shared_ptr<Connection>::shared_ptr(Connection)’
            registerConnection(conn);
        }
        else
        {
            mh = MessageHandler(conn); // Alter MessageHander so we don't have to overrite every time?

            // Make big try-catch and just throw from all the cases??
            try
            {

                vector<std::tuple<int, string>> news_groups;
                vector<std::tuple<int, string>> articles;
                std::tuple<string, string, string> article;
                int ng_id;
                int a_id;
                string ng_name;
                string a_title;
                string a_author;
                string a_text;
                switch (mh.recv_code()) // if (mh.recv_code() != COM_END) { break; }
                {
                // TODO: Fix this. It's a tuple now
                case Protocol::COM_LIST_NG:
                    com_end();
                    news_groups = db.list_newsgroups();
                    mh.send_code(Protocol::ANS_LIST_NG);
                    mh.send_int_parameter(news_groups.size());
                    if (news_groups.size())
                    {
                        for (const auto &ng : news_groups)
                        {
                            mh.send_int_parameter(get<0>(ng));
                            mh.send_string_parameter(get<1>(ng));
                        }
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_CREATE_NG:
                    ng_name = mh.recv_string_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_CREATE_NG);
                    try
                    {
                        db.create_newsgroup(ng_name);
                        mh.send_code(Protocol::ANS_ACK);
                    }
                    catch (NewsgroupException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_ALREADY_EXISTS);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_DELETE_NG:
                    ng_id = mh.recv_int_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_DELETE_NG);
                    try
                    {
                        db.delete_newsgroup(ng_id);
                        mh.send_code(Protocol::ANS_ACK);
                    }
                    catch (NewsgroupException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_LIST_ART:
                    ng_id = mh.recv_int_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_LIST_ART);
                    try
                    {
                        articles = db.list_articles(ng_id);
                        mh.send_code(Protocol::ANS_ACK);
                        mh.send_int_parameter(articles.size());
                        if (articles.size())
                        {
                            for (const auto &art : articles)
                            {
                                mh.send_int_parameter(get<0>(art));
                                mh.send_string_parameter(get<1>(art));
                            }
                        }
                    }
                    catch (NewsgroupException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_CREATE_ART:
                    ng_id = mh.recv_int_parameter();
                    a_title = mh.recv_string_parameter();
                    a_author = mh.recv_string_parameter();
                    a_text = mh.recv_string_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_CREATE_ART);
                    try
                    {
                        db.create_article(a_title, a_author, a_text, ng_id);
                        mh.send_code(Protocol::ANS_ACK);
                    }
                    catch (NewsgroupException)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_DELETE_ART:
                    ng_id = mh.recv_int_parameter();
                    a_id = mh.recv_int_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_DELETE_ART);
                    try
                    {
                        db.delete_article(ng_id, a_id);
                        mh.send_code(Protocol::ANS_ACK);
                    }
                    catch (NewsgroupException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
                    }
                    catch (ArticleException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                case Protocol::COM_GET_ART:
                    ng_id = mh.recv_int_parameter();
                    a_id = mh.recv_int_parameter();
                    com_end();
                    mh.send_code(Protocol::ANS_GET_ART);
                    try
                    {
                        article = db.get_article(ng_id, a_id);
                        mh.send_code(Protocol::ANS_ACK);
                        mh.send_string_parameter(get<0>(article));
                        mh.send_string_parameter(get<1>(article));
                        mh.send_string_parameter(get<2>(article));
                    }
                    catch (NewsgroupException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_NG_DOES_NOT_EXIST);
                    }
                    catch (ArticleException &)
                    {
                        mh.send_code(Protocol::ANS_NAK);
                        mh.send_code(Protocol::ERR_ART_DOES_NOT_EXIST);
                    }
                    mh.send_code(Protocol::ANS_END);
                    break;

                default:
                    throw ProtocolViolationException(); // Commandbyte not recognized
                }
            }
            catch (ProtocolViolationException &e)
            {
                deregisterConnection(conn);
                std::cout << "Client did not observe proper protocol. Connection terminated.\n";
            }
        }
    }
}

