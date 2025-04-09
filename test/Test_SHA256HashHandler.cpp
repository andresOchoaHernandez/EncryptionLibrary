#include "SHAHashHandler.hpp"

#include "Utils.hpp"

#include <iostream>

bool test_helloWorld()
{
    SHA256HashHandler test;
    const std::string message = "Hello world!";

    std::cout << "Original message : " << message << std::endl;
    std::cout << "Hashed message in base64 : " << test.hash(message) << std::endl;
    std::cout << "Hashed message in string : " << decodeFromBase64(test.hash(message)) << std::endl;

    return true;
}

int main (int argc, char* argv[])
{
    if(!test_helloWorld())
        return -1;

    return 0;
}