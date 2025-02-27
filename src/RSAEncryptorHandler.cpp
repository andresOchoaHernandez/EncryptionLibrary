/**
 * @file RSAEncryptorHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for RSAEncryptorHandler.hpp
 */

#include "RSAEncryptorHandler.hpp"

RsaKeyPair RSAEncryptorHandler::generateKeyPair(int bits)
{
    return {"pub","priv"};
}

std::string RSAEncryptorHandler::encrypt(const std::string& plaintext,const std::string& key)
{
    return "";
}

std::string RSAEncryptorHandler::decrypt(const std::string& cyphertext,const std::string& key)
{
    return "";
}