/**
 * @file RSAEncryptorHandler.hpp
 * @author Andres Ochoa Hernandez
 * @brief This file contains the class RSAEncryptorHandler
 */

#include "CryptoHandler.hpp"

/**
 * @struct RsaKeyPair
 * @brief Contains the public and private key
 */
struct RsaKeyPair
{
    /**
     * @brief Public key
     */
    std::string publicKey;
    
    /**
     * @brief Private key
     */
    std::string privateKey;
};

/**
 * @implements CryptoHandler
 * @class RSAEncryptorHandler
 * @brief Implements CryptoHandler interface
 * 
 * This class handles the generation of a random key pair, the encryption and decryption of strings using RSA asymmetric encryption
 */
class RSAEncryptorHandler : public CryptoHandler
{
    public :

        /**
         * @brief Generates a key pair
         * @param bits Number of bits of the key pair to be generated
         * @returns Keypair
         */
        RsaKeyPair generateKeyPair(int bits);

        /**
         * @brief Encrypts a message using RSA
         * @param plaintext Message to be encrypted
         * @param key Key to be used for RSA asymmetric encryption
         * @returns Encrypted string
         */
        std::string encrypt(const std::string& plaintext,const std::string& key) override;

        /**
         * @brief Decrypts a message using RSA
         * @param cyphertext The payload to be decrypted
         * @param key Key to be used for RSA asymmetric decryption
         * @returns Decrypted string
         */
        std::string decrypt(const std::string& cyphertext,const std::string& key) override;
};