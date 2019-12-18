// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Client.h"

int main()
{
    try {

        std::cout << "Start session" << std::endl;
        Client client;

        client.Run();

        std::cout << "End session." << std::endl;
        return 0;
    }
    catch (...) {
        std::cout << "Error" << std::endl;
        return 1;
    }
}

