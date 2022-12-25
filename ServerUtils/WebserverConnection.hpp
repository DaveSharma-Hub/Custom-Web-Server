#ifndef WebserverConnection_hpp
#define WebserverConnection_hpp

#include "ServerConnection.cpp"

namespace Webserver{
    class WebserverConnection:private Server::ServerConnection{
        public:
            WebserverConnection(int domain,int type, int protocol,int port);
            void webserverListening();
            void webserverDevListening(std::string entry);
    };  
}


#endif