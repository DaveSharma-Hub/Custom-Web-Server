# Custom-Web-Server
*In Progress*
## Description
Creating a custom webserver from scratch similar to a Node.js or Flask server that can either host custom websites or create RESTful api endpoints using c++ web-sockets.

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
Will start listening on port 8000. Store custom html, js, and css files (website) in the File Directory folder to be retrieved.

## Documentation


## Class Diagram
