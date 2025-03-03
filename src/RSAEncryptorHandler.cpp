/**
 * @file RSAEncryptorHandler.cpp
 * @author Andres Ochoa Hernandez
 * @brief Implementation file for RSAEncryptorHandler.hpp
 */

#include <openssl/evp.h>

#include "RSAEncryptorHandler.hpp"

EVP_PKEY* keypairToEVP_PKEY(RsaKeyPair keyPair)
{
    return nullptr;
}

RsaKeyPair EVP_PKEYToKeypair(EVP_PKEY* keyPair)
{
    return {"pub","priv"};
}

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