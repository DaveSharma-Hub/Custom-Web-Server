#ifndef ServerConnection_hpp
#define ServerConnection_hpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


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

        public:
            ServerConnection(int domain,int type, int protocol,int port);
            void createBindConnection();
            void createListenConnection();
            void setup_func();
            void startListening();
    };
}


#endif