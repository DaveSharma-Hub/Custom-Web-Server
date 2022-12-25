#include <stdio.h>
#include <iostream>
#include <unistd.h>
// #include "ServerUtils/ServerConnection.cpp"
#include "ServerUtils/ToObject.cpp"
#include "ServerUtils/WebserverConnection.cpp"
// #include <fstream>
// #include "ServerUtils/Endpoint.cpp"

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
    // std::vector<std::string> names ={"John","Bob","Katy","Tina","Benny","Sammy"};
    // string tmp="[";
    // for(int i=0;i<names.size();i++){
    //     string holder = "{id:'"+ std::to_string(i) + "',name:'"+names[i]+"'},";
    //     tmp += holder;
    // }
    // tmp+="]";
    // string tmp = "[\{\"id\":\"1\",\"name\":\"Bob\"},{\"id\":\"2\",\"name\":\"John\"}\]";

    Conversion::ToObject objectArray;
    for(int i=0;i<10;i++){
        int id = objectArray.newObject();
        objectArray.addToObject(id,"id",to_string(i));
        objectArray.addToObject(id,"name","john"+to_string(i));
        objectArray.addToObject(id,"location","NYC"+to_string(i));
    }
    return objectArray.convertToJson();
}