#include "ServerConnection.hpp"

using namespace std;
namespace fs = std::experimental::filesystem;

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
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
        string arr = findFile();
        // string arr="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 5\n\n<h1>hello world</h1>";
        char message[arr.length()+100]={0};
        for(int i=0;i<arr.length();i++){
            message[i] = arr[i];
        }
        printf("%s\n",message);
        // write(new_socket , hello , strlen(hello));
        int send_res=send(new_socket,message,sizeof(message),0);

        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
    }
}

string Server::ServerConnection::findFile(){
    ifstream file;
    string tmp="";
    file.open("C:/Users/Daves/git/Custom-Web-Server/FileDirectory/exampleWebsite.html");
    if(!file.is_open())
    {
        cout<<"Unable to open the file."<<endl;
        string failed =  "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 22\n\n<h1>404 Not Found</h1>";
        return failed;
    }
    
    string line;
    while(getline(file, line))
    {
        // cout<<line<<endl;
        tmp+=line;
    }
    
    file.close();
    // cout<<tmp.length();
    string header = initMessage(tmp.length());
    header+=tmp;
    return header;
    
    // message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    // message = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 97\n\n<div><h1>Cool Website</h1><p>Definitely Check Out the socials</p><button>Click Me</button></div>";
    // for(int i=0;i<length+tmp.length();i++){
    //     cout<<message[i];
    // }
    //  std::string path = "../FileDirectory";
    // for (const auto & entry : fs::directory_iterator(path))
    //     std::cout << entry.path() << std::endl;
}

string Server::ServerConnection::initMessage(int length){
    string tmp = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "+std::to_string(length)+"\n\n";
    // cout<<message<<endl;
    return tmp;
}



// void Server::ServerConnection::setMessage(char* msg){
//     char* tmp = msg;
//     while(tmp!="\n"){
//         while(){

//         }
//     }
// }