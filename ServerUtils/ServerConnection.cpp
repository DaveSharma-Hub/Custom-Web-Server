#include "ServerConnection.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

Server::ServerConnection::ServerConnection(int domain,int type, int protocol,int port){
    domain=domain;
    type=type;
    protocol=protocol;
    port=port;
    addrlen = sizeof(address);

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
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\n<h1>Hello</h1>";
    char arr[200]="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";

    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        memset(buffer,0,sizeof(buffer));
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        string fileName = parseHeaderRequest(buffer);
        string fileType = getFileType(fileName.c_str());
        string arr = findFile(fileName.c_str(),fileType.c_str());
        //if(fileType!="jpg" && fileType!="jpeg" && fileType!="png"){
            char message[arr.length()+100]={0};
            memset(message,0,sizeof(buffer));
            for(int i=0;i<arr.length();i++){
                message[i] = arr[i];
            }
            // printf("%d\n",sizeof(message));
            // write(new_socket , hello , strlen(hello));
            int send_value = send(new_socket,message,sizeof(message),0);
            // int send_res=send(new_socket,message,sizeof(message),0);

        //}
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}

string Server::ServerConnection::findFile(const char* fileName,const char* fileType){
    if(fileType=="jpg" || fileType=="jpeg" || fileType=="png"){
            string fileLocation = string(fileName);
            string tmp="";
            ifstream image;
            string file = "C:/Users/Daves/git/Custom-Web-Server/FileDirectory/"+fileLocation;
            FILE* file_stream = fopen(file.c_str(), "r");
            // FILE *in = fopen(file.c_str(),"r");

            if(file_stream != nullptr)
            {
                char Buffer[100000] ={};
                int len;
                fread(Buffer,sizeof(Buffer),1, file_stream);
                while ((len = fread(Buffer,sizeof(Buffer),1, file_stream)) > 0)
                {      
                    std::string header = "HTTP/1.1 200 OK\nContent-Type: text/jpeg\nContent-Length: "+to_string(len)+"\n\n";
                    header += string(Buffer);      
                    send(new_socket,header.c_str(),header.length(),0);            
                    cout<<header;
                }
                // header+=string(Buffer);
                // return header;
                std::string header = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 0\n\n";
            }
            else{
                // cout<<"Unable to open the file."<<endl;
                // string failed =  "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 22\n\n<h1>404 Not Found</h1>";
                // return failed;
            }
        }
    else{
        string fileLocation = string(fileName);
        ifstream file;
        string tmp="";
        cout<<fileName;
        file.open("C:/Users/Daves/git/Custom-Web-Server/FileDirectory/"+fileLocation);
        if(!file.is_open())
        {
            cout<<"Unable to open the file."<<endl;
            string failed =  "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 22\n\n<h1>404 Not Found</h1>";
            return failed;
        }
        
        string line;
        while(getline(file, line))
        {
            tmp+=line;
            // cout<<line<<endl;
        }
        
        file.close();
        string header = initMessage(tmp.length(),fileType);
        header+=tmp;
        return header;
    }
}

string Server::ServerConnection::initMessage(int length,const char* typeOfFile){
    string fileType = string(typeOfFile);
    string tmp;
    if(fileType=="html"){
         tmp = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "+std::to_string(length)+"\n\n";
    }
    else if(fileType=="jpg" || fileType=="JPG" ){
         tmp = "HTTP/1.1 200 OK\nContent-Type: image/jpg\nContent-Length: "+std::to_string(length)+"\n\n";
    }
    else if(fileType=="js"){
         tmp = "HTTP/1.1 200 OK\nContent-Type: text/js\nContent-Length: "+std::to_string(length)+"\n\n";
    }
    else if(fileType=="css"){
         tmp = "HTTP/1.1 200 OK\nContent-Type: text/css\nContent-Length: "+std::to_string(length)+"\n\n";
    }
    else{
         tmp = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "+std::to_string(length)+"\n\n";
    }
    // cout<<message<<endl;
    return tmp;
}

string Server::ServerConnection::parseHeaderRequest(char* header){
    string buffer = string(header);
    string tmp="";
    for(int i=5;i<buffer.length()-5;i++){
        if(buffer[i]==' '&&buffer[i+1]=='H'&&buffer[i+2]=='T'&&buffer[i+3]=='T'&&buffer[i+4]=='P'){
            break;
        }
        else{
            tmp+=buffer[i];
        }
    }
    return tmp;
}

std::string Server::ServerConnection::getFileType(const char* file){
    string fileName = string(file);
    string tmp="";
    int i=0;
    for(;i<fileName.length();i++){
        if(fileName[i]=='.'){
            i++;
            break;
        }
    }
    for(;i<fileName.length();i++){
        tmp+=fileName[i];
    }
    return tmp;
}

void Server::ServerConnection::listenRest(){
    while(1)
    {
        printf("\n+++++++ Waiting for new connection++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        char message[1000]="HTTP/1.1 200 OK\nContent-Type: text/json\nContent-Length: 20\n\n{id:'1',name:'John'}";
        //const char* message= tmp.c_str();
        int send_value = send(new_socket,message,sizeof(message),0);        

        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}

void Server::ServerConnection::listenRest(std::vector<Endpoints::endpoint>& input){
    while(1)
    {

        printf("\n+++++++ Waiting for new connection++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
            char buffer[30000] = {0};
            valread = read( new_socket , buffer, 30000);
            printf("%s\n",buffer );
            // char message[1000]="HTTP/1.1 200 OK\nContent-Type: text/json\nContent-Length: 85\n\n[{id:'0',name:'John'},{id:'1',name:'Bob'},{id:'2',name:'Katy'},{id:'3',name:'Tina'},]";
            string tmp = checkEndpoints(buffer,input);
            string totalMessage = "HTTP/1.1 200 OK\nContent-Type: text/json\nContent-Length: "+to_string(tmp.length())+"\n\n"+tmp;
            // char message[totalMessage.length()]={};
            for(int i=0;i<totalMessage.length();i++){
                message[i] = totalMessage[i];
            }
            const char* message= totalMessage.c_str();
            // cout<<message<<endl;
            int send_value = send(new_socket,message,sizeof(message),0);        

            printf("------------------Hello message sent-------------------\n");
            close(new_socket);
    }
}

std::string Server::ServerConnection::checkEndpoints(char* input,std::vector<Endpoints::endpoint>& endpoints){
    
    string type = getRestType(input);
    string endpointName = getEndpointName(input);

    for(Endpoints::endpoint eachEndpoint:endpoints){
        if(eachEndpoint.getEndpointApi()==endpointName){
            return eachEndpoint.evaluateFunction();
        }
    }
    return "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 22\n\n<h1>404 Not Found</h1>";
}  

std::string Server::ServerConnection::getRestType(char* input){
    string tmp = string(input);
    string type ="";
    int i=0;

    while(tmp[i]!=' '){
        type+=tmp[i];
        i++;
    }
    return type;
}
std::string Server::ServerConnection::getEndpointName(char* input){
    string tmp = string(input);
    string name ="";
    int i=0;

    while(tmp[i]!='/'){
        i++;
    }
    while(tmp[i]!=' '){
        name+=tmp[i];
        i++;
    }
    return name;
}

