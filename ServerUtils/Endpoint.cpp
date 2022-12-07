#include "Endpoint.hpp"

Endpoints::endpoint::endpoint(std::string apis, std::string type,std::string (*function)(std::string)){
    endpointApi = apis;
    endpointType = type;
    func = function;
}

std::string Endpoints::endpoint::getEndpointApi(){
    return endpointApi;
}

std::string Endpoints::endpoint::evaluateFunction(){
    return func("");
}
