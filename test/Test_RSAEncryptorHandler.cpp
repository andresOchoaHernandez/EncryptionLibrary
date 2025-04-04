#include "RSAEncryptorHandler.hpp"

#include <iostream>

int main (int argc, char* argv[])
{
    RSAEncryptorHandler test;
        
    RsaKeyPair res =  test.generateKeyPair(2048);

    std::cout << res.publicKey << std::endl;
    std::cout << res.privateKey << std::endl;

    return 0;
}