#include "ServerConnection.hpp"

using namespace std;

Server::ServerConnection::ServerConnection(int domain,int type, int protocol,int port){
    domain=domain;
    type=type;
    protocol=protocol;
    port=port;

     if ((server_fd = socket(domain, type, protocol)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    address.sin_family = domain;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( port );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    setup_func();
}

void Server::ServerConnection::createBindConnection(){
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
}
void Server::ServerConnection::createListenConnection(){
    if(listen(server_fd,10)<0){
        perror("In listen");
        exit(EXIT_FAILURE);
    }
}
void Server::ServerConnection::setup_func(){
    createBindConnection();
    createListenConnection();
}
void Server::ServerConnection::startListening(){
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 1000\n\n<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Document</title></head><body><div><h1>Cool Website</h1><p>Definitely Check Out the socials</p><button>Click Me</button></div></body></html>";

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        write(new_socket , hello , strlen(hello));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}