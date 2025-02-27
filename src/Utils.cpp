#include "Utils.hpp"

#include <random>

std::string padString(const std::string& str, size_t numberOfBytes,char paddingChar)
{
    std::string result = str;

    if(result.size() >= numberOfBytes)
    {
        result = str.substr(0,numberOfBytes);
    }
    else 
    {
        result.append(numberOfBytes - str.size(), paddingChar);
    }

    return result;
}

std::string generateRandomString(size_t length) {
    
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}