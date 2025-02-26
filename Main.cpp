#include <iostream>

#include "AES256EncryptorHandler.hpp"
#include "RSAEncryptorHandler.hpp"

int main(int argc, char* argv[])
{
    AES256EncryptorHandler testSymmetricEncryption;
    RSAEncryptorHandler testAsymmetricEncryption;

    std::cout << "Hello world" << std::endl;

    return 0;
}