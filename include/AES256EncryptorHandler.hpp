#include "CryptoHandler.hpp"

class AES256EncryptorHandler : public CryptoHandler
{
    std::string encrypt(const std::string& message,const std::string& key) override;
    std::string decrypt(const std::string& message,const std::string& key) override;
};