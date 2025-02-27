#include <iostream>

#include "AES256EncryptorHandler.hpp"
#include "RSAEncryptorHandler.hpp"

int main(int argc, char* argv[])
{
    AES256EncryptorHandler testSymmetricEncryption;

    std::string message = "Hello! This communication is encrypted!";
    std::string key = testSymmetricEncryption.generateKey();
    std::cout << "Generated key : " << key << std::endl;

    std::string encryptedPayload = testSymmetricEncryption.encrypt(message,key);
    std::string decryptedPayload = testSymmetricEncryption.decrypt(encryptedPayload,key);

    std::cout << "Message : " << message << std::endl;
    std::cout << "Encrypted message : " << encryptedPayload << std::endl;
    std::cout << "Decrypted message : " << decryptedPayload << std::endl;

    return 0;
}