#pragma once

#include <string>

class CryptoHandler
{
    public:
        virtual std::string encrypt(const std::string& message,const std::string& key) = 0;
        virtual std::string decrypt(const std::string& message,const std::string& key) = 0;       
};