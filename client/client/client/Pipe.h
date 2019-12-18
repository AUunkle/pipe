#pragma once

#include "windows.h"
#include <iostream>

class Pipe
{
public:
    Pipe();
    Pipe(const std::string& pipe_name);

    ~Pipe();


    bool Connect();
    bool Disconnect();
    bool IsConnected();
    bool IsEnabled();
    void* pipePTR();
private:

    std::shared_ptr<void> _sharedHandle;


};

