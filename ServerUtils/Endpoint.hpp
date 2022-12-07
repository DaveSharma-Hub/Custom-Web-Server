#ifndef Endpoint_hpp
#define Endpoint_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <cstring>
#include <functional>

namespace Endpoints{
    class endpoint{
        private:
            std::string endpointApi; //eg./getMyBooks
            std::string endpointType;//GET or POST
            std::string (*func)(std::string);//this is the "resolver" function
                                                //for particular api endpoint, pass in request
                                                //returns json in string format
        public:
            endpoint(std::string api, std::string type,std::string (*function)(std::string));
            std::string getEndpointApi();
            std::string evaluateFunction();
    };
}

#endif