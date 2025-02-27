#include "CryptoHandler.hpp"

struct RsaKeyPair
{
    std::string publicKey;
    std::string privateKey;
};

class RSAEncryptorHandler : public CryptoHandler
{
    public : 
        RsaKeyPair generateKeyPair(int bits);

        std::string encrypt(const std::string& message,const std::string& key) override;
        std::string decrypt(const std::string& message,const std::string& key) override;
};