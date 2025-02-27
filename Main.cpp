#include <iostream>

#include "AES256EncryptorHandler.hpp"
#include "RSAEncryptorHandler.hpp"

int main(int argc, char* argv[])
{
    AES256EncryptorHandler testSymmetricEncryption;
    RSAEncryptorHandler testAsymmetricEncryption;

    std::cout << testSymmetricEncryption.encrypt("Hello!","12345") << std::endl;

    return 0;
}