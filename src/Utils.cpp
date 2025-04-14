/**
 * @file Utils.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for Utils.hpp
 */

#include <random>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <openssl/evp.h>

#include "Utils.hpp"

std::string trimString(const std::string &str) 
{
    std::string strCopy = str;
    strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\n'), strCopy.cend());
    strCopy.erase(std::remove(strCopy.begin(), strCopy.end(), '\0'), strCopy.cend());
    return strCopy;
}

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

std::string encodeInBase64(const std::string& payload)
{
    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    EVP_EncodeInit(ctx);
    if(ctx == nullptr)
    {
        throw std::runtime_error("Failed to create EVP_ENCODE_CTX_new object");
    }

    int numberOfBlocks = 1 + ((payload.size()-1)/48);
    int bytesInTheLastBlock = payload.size() - ((numberOfBlocks-1)*48);
    std::vector<unsigned char> payloadEncoded(65 * numberOfBlocks + 1);

    int encodedBytes;
    for(uint i = 0 ; i < numberOfBlocks; i++)
    {        
        int encodeUpdateResult = EVP_EncodeUpdate(
            ctx,
            payloadEncoded.data() + 65*i,
            &encodedBytes,
            reinterpret_cast<unsigned char*>(const_cast<char*>(payload.c_str())) + 48*i,
            i == numberOfBlocks - 1 ? bytesInTheLastBlock : 48
        );

        if(encodeUpdateResult <= 0)
        {
            EVP_ENCODE_CTX_free(ctx);
            throw std::runtime_error("Error while encoding the payload");
        }

        if(encodedBytes == 0)
        {
            EVP_EncodeFinal(
                ctx,
                payloadEncoded.data() + 65*(numberOfBlocks-1),
                &encodedBytes
            );
        }
    }

    EVP_ENCODE_CTX_free(ctx);

    return trimString(std::string(payloadEncoded.begin(), payloadEncoded.end()));
}

std::string decodeFromBase64(const std::string& payload)
{
    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    EVP_DecodeInit(ctx);
    if(ctx == nullptr)
    {
        throw std::runtime_error("Failed to create EVP_ENCODE_CTX_new object");
    }

    int numberOfBlocks = 1 + ((payload.size()-1)/80);
    int bytesInTheLastBlock = payload.size() - ((numberOfBlocks-1)*80);
    std::vector<unsigned char> payloadDecoded(3*payload.size()/4);

    //std::cout << "Number of blocks : " << numberOfBlocks << std::endl;
    //std::cout << "Payload size : " << payload.size() << std::endl;

    int decodedBytes;
    for(uint i = 0 ; i < (numberOfBlocks-1); i++)
    {        
        int decodeUpdate = EVP_DecodeUpdate(
            ctx,
            payloadDecoded.data()+ 60*i,
            &decodedBytes,
            reinterpret_cast<unsigned char*>(const_cast<char*>(payload.c_str()))+ 80*i,
            80
        );
    
        if(decodeUpdate == -1)
        {
            EVP_ENCODE_CTX_free(ctx);
            throw std::runtime_error("Error while decoding the payload");
        }


        //std::cout << "Block : " << i << " Decoded Bytes : " << decodedBytes << " Remaining bytes in the ctx : " << EVP_ENCODE_CTX_num(ctx) << std::endl;
    }

    int decodeUpdate = EVP_DecodeUpdate(
        ctx,
        payloadDecoded.data()+ 60*(numberOfBlocks-1),
        &decodedBytes,
        reinterpret_cast<unsigned char*>(const_cast<char*>(payload.c_str()))+ 80*(numberOfBlocks-1),
        bytesInTheLastBlock
    );

    if(decodeUpdate == -1)
    {
        EVP_ENCODE_CTX_free(ctx);
        throw std::runtime_error("Error while decoding the payload");
    }

    EVP_ENCODE_CTX_free(ctx);

    return trimString(std::string(payloadDecoded.begin(), payloadDecoded.end()));
}