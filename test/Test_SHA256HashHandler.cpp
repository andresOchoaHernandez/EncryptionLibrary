#include "SHAHashHandler.hpp"

#include "Utils.hpp"

bool test_helloWorld()
{
    SHA256HashHandler test;
    const std::string message = "Hello world!";
    return "wFNeS+K3n/2TKRMFQ2v4iTFOSj+uwF7P/Lt98xrZ5Ro=" == test.hash(message);
}

int main (int argc, char* argv[])
{
    if(!test_helloWorld())
        return -1;

    return 0;
}