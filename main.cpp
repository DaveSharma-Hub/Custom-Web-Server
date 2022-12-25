#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ServerUtils/ToObject.cpp"
#include "ServerUtils/WebserverConnection.cpp"


using namespace std;
std::string returnAllNames(std::string req);


int main(){

    // Webserver::WebserverConnection connection(AF_INET,SOCK_STREAM,0,8000);
    // connection.webserverListening();

    Server::ServerConnection newServer(AF_INET, SOCK_STREAM, 0,8000); // web server to host html files
    newServer.startListening();

    
    // Server::ServerConnection newAPIServer(AF_INET,SOCK_STREAM,0,8001); // api endpoint server
    // std::vector<Endpoints::endpoint> apis;
    // Endpoints::endpoint a1("/getAllNames","GET",&returnAllNames);
    // apis.push_back(a1);
    // // Endpoints::endpoint a2("/getSpecificName","GET",&otherFunction);
    // // apis.push_back(a2);
    // newAPIServer.listenRest(apis);
    
    return 1;
}

std::string returnAllNames(std::string req){
    Conversion::ToObject objectArray;
    for(int i=0;i<10;i++){
        int index = objectArray.newObject();
        objectArray.addToObject(index,"id",to_string(i));
        objectArray.addToObject(index,"name","john"+to_string(i));
        objectArray.addToObject(index,"location","NYC"+to_string(i));
    }
    return objectArray.convertToJson();
}