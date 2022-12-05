#ifndef ServerConnection_hpp
#define ServerConnection_hpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <filesystem>
#include <experimental/filesystem>
#include <fstream>

namespace Server{
    class ServerConnection{
        private:
            int server_fd;
            int new_socket;
            struct sockaddr_in address;
            int addrlen;
            int domain;
            int type;
            int protocol;
            int port;
            long valread;
            // char *message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 11\n\n<h1>Hi</h1>";
            // vector<char[1024]> message;
            char* message;

        public:
            ServerConnection(int domain,int type, int protocol,int port);
            void createBindConnection();
            void createListenConnection();
            void setup_func();
            void startListening();
            void setMessage(char* msg);
            std::string findFile();
            std::string initMessage(int length);
    };
}


#endif