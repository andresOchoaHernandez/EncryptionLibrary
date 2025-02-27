#pragma once

#include <exception>

#include <string>

class CryptoHandler
{
    public:
        virtual std::string encrypt(const std::string& message,const std::string& key) = 0;
        virtual std::string decrypt(const std::string& message,const std::string& key) = 0;       
};

class CryptoHandlerException : public std::exception
{

    private : 
        
        std::string message;

    public :
    
        CryptoHandlerException(const char* msg):message(msg){}

        const char* what() const throw()
        {
            return message.c_str();
        }
};