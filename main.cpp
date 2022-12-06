#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ServerUtils/ServerConnection.cpp"
#include <fstream>

using namespace std;
int main(){
    Server::ServerConnection newServer(AF_INET, SOCK_STREAM, 0,8000); // web server to host html files
    newServer.startListening();

    Server::ServerConnection newAPIServer(AF_INET,SOCK_STREAM,0,8080); // api endpoint server
    newServer.listenRest();
    return 1;
}