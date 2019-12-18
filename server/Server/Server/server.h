#pragma once

#include "windows.h"
#include "Pipe.h"
#include <iostream>
#include <sstream>
#include "srvMsg.h"
#include "Head.h"

class Server
{
public:
    Server();
    ~Server();

    bool getRequest();

    bool sendAnswer();

    void Run();
    
private:
    //bool isMSGValid(void *data, Head& header);

    Pipe _pipe;

    srvMsg _inMsg;
    srvMsg _outMsg;

    

};

