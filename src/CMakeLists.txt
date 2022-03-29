cmake_minimum_required(VERSION 3.14)
target_sources(clientserver
    PRIVATE
        connection.cc
        server.cc
        memory_db.cc
        message_handler.cc
        ourserver.cc
        client.cc
)
