/**
 * @file AES256EncryptorHandler.hpp
 * @author Andres Ochoa Hernandez
 * @brief This file contains the class AES256EncryptorHandler
 */

#include "CryptoHandler.hpp"

/**
 * @implements CryptoHandler
 * @class AES256EncryptorHandler
 * @brief Implements CryptoHandler interface
 * 
 * This class handles the generation of a random 256 bit symmetric key, the encryption and decryption of strings using AES 256 GCM
 */
class AES256EncryptorHandler : public CryptoHandler
{
    public:
        
        /**
         * @brief Generates a 256 bit random string
         * @returns 256 bit string
         */
        std::string generateKey();

        /**
         * @brief Encrypts a message using AES 256 GCM
         * @param plaintext Message to be encrypted
         * @param key Symmetric key to be used for the encryption. If the key size is less than 256 bits, padding will be added to reach 256. If it ecceeds 256 bits it will be truncated to 256.
         * @returns Encrypted base 64 encoded string structured in the following way : The first 128 bits are the initialization vector (that is generated randomly), the rest are the encrypted payload
         */
        std::string encrypt(const std::string& plaintext,const std::string& key) override;
        
        /**
         * @brief Decrypts a message using AES 256 GCM
         * @param base64EncodedCyphertext Base 64 encoded payload to be decrypted. It's assumed that the first 128 bits are the initialization vector
         * @param key Symmetric key to be used for the encryption. If the key size is less than 256 bits, padding will be added to reach 256. If it ecceeds 256 bits it will be truncated to 256.
         * @returns Decrypted string
         */
        std::string decrypt(const std::string& base64EncodedCyphertext,const std::string& key) override;
};