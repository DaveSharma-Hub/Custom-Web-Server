#include "WebserverConnection.hpp"

Webserver::WebserverConnection::WebserverConnection(int domain,int type, int protocol,int port):Server::ServerConnection(domain,type,protocol,port){};

void Webserver::WebserverConnection::webserverListening(){
    Server::ServerConnection::startListening();
}

void Webserver::WebserverConnection::webserverDevListening(std::string entry){
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 14\n\n<h1>Hello</h1>";
    char array[200]="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";

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
        string fileName = parseHeaderRequest(buffer);
        string fileType = getFileType(fileName.c_str());
        string arr = findFile(fileName.c_str(),fileType.c_str());
        //if(fileType!="jpg" && fileType!="jpeg" && fileType!="png"){
            // char message[arr.length()+100]={0};
            // for(int i=0;i<arr.length();i++){
            //     message[i] = arr[i];
            // }
            // printf("%d\n",sizeof(message));
            // write(new_socket , hello , strlen(hello));
            int send_value = send(new_socket,arr.c_str(),sizeof(message),0);
            // int send_res=send(new_socket,message,sizeof(message),0);

        //}
        printf("------------------Hello message sent-------------------\n");
        sleep(10);
        send_value = send(new_socket,array,sizeof(array),0);

        close(new_socket);
    }
}
