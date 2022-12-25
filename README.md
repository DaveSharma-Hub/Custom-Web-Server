# Custom-Web-Server
*In Progress*
## Description
Creating a custom webserver from scratch similar to a Node.js server that can either host custom websites or create RESTful api endpoints using sockets

## Usage
Clone repository
```c++
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ServerUtils/ToObject.cpp"
#include "ServerUtils/WebserverConnection.cpp"

int main(){
  Server::ServerConnection newServer(AF_INET, SOCK_STREAM, 0,8000); // web server to host html files
  newServer.startListening();
}
```
Will start listening on port 8000

## Documentation

## Class Diagram
