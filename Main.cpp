#include <iostream>

#include "AES256EncryptorHandler.hpp"
#include "RSAEncryptorHandler.hpp"

int main(int argc, char* argv[])
{
    AES256EncryptorHandler testSymmetricEncryption;
    RSAEncryptorHandler testAsymmetricEncryption;

    std::string message = "Hello!";
    std::string key = "12345";

    std::string encryptedPayload = testSymmetricEncryption.encrypt(message,key);
    std::string decryptedPayload = testSymmetricEncryption.decrypt(encryptedPayload,key);

    std::cout << "Message : " << message << std::endl;
    std::cout << "Encrypted message : " << encryptedPayload << std::endl;
    std::cout << "Decrypted message : " << decryptedPayload << std::endl;

    return 0;
}