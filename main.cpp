#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ServerUtils/ServerConnection.cpp"

using namespace std;
int main(){
    Server::ServerConnection newServer(AF_INET, SOCK_STREAM, 0,8000);
    newServer.startListening();
    return 1;
}