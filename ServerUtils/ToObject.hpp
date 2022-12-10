#ifndef ToObject_hpp
#define ToObject_hpp

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cstring>
#include <vector>

namespace Conversion{
    class Object{
        private:
            std::vector<std::vector<std::string>> objectNotation;
        public:
            Object();
            void addItem(std::string key, std::string value);
            std::vector<std::vector<std::string>> getObject();
    };
    class ToObject{
        private:
            std::vector<Object> objectArray;

        public:
            ToObject();
            int newObject();
            void addToObject(int index,std::string key,std::string value);
            std::string convertToJson();
    };
}

#endif