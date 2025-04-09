/**
 * @file Utils.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for Utils.hpp
 */

#include <random>
#include <fstream>
#include <filesystem>
#include <openssl/evp.h>

#include "Utils.hpp"

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

std::string generateRandomString(size_t length) 
{
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    for (size_t i = 0; i < length; ++i) 
    {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

void writeFile(const std::string& path,const std::string& content)
{
    std::ofstream file;
    file.open (path);

    if(file.fail())
    {
        file.close();
        throw std::runtime_error("Error while opening the specified file");
    }

    file << content;
    file.close();
}

std::string readFile(const std::string& path)
{
    std::ifstream file(path);

    if(file.fail())
    {
        file.close();
        throw std::runtime_error("Error while opening the specified file");
    }

    std::string content;
    std::string line; 

    while (std::getline(file, line))
    {
        content += line;
    }

    file.close();

    return content;
}

void deleteFile(const std::string& path)
{
    if(!std::filesystem::remove(path))
        throw std::runtime_error("Tried to delete a non existent file");
}

std::string encodeToBase64(std::string payload)
{
    // TODO :
    return "";
}

std::string decodeFromBase64(std::string base64payload)
{
    // TODO :
    return "";
}