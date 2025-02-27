#include "CryptoHandler.hpp"

class AES256EncryptorHandler : public CryptoHandler
{
    public:
        
        std::string generateKey();
        std::string encrypt(const std::string& plaintext,const std::string& key) override;
        std::string decrypt(const std::string& cyphertext,const std::string& key) override;
};