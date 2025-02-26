#include "RSAEncryptorHandler.hpp"

RsaKeyPair RSAEncryptorHandler::generateKeyPair(int bits)
{
    return {"pub","priv"};
}

std::string RSAEncryptorHandler::encrypt(const std::string& message,const std::string& key)
{
    return "";
}

std::string RSAEncryptorHandler::decrypt(const std::string& message,const std::string& key)
{
    return "";
}