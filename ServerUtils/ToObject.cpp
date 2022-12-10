#include "ToObject.hpp"

Conversion::Object::Object(){
    objectNotation={};
}

void::Conversion::Object::addItem(std::string key, std::string value){
    std::vector<std::string> tmp = {};
    tmp.push_back(key);
    tmp.push_back(value);
    objectNotation.push_back(tmp);
}

std::vector<std::vector<std::string>> Conversion::Object::getObject(){
    return objectNotation;
}

Conversion::ToObject::ToObject(){
    objectArray = {};
}

int Conversion::ToObject::newObject(){
    Object o1;
    objectArray.push_back(o1);
    return objectArray.size()-1;
}
void Conversion::ToObject::addToObject(int index,std::string key,std::string value){
    if(index<objectArray.size() && index>=0){
        objectArray[index].addItem(key,value);
    }
}

std::string Conversion::ToObject::convertToJson(){
    std::string holder = "[\ ";
    for(Object obj:objectArray){
        holder+="{\ ";
        for(std::vector<std::string> keyValue : obj.getObject()){
            holder+=keyValue[0]+":\""+keyValue[1]+"\",";
        }
        holder+="\},";
    }
    holder+="\]";
    return holder;
}
