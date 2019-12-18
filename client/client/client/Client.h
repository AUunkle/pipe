#pragma once
#include "pipeFile.h"
#include <string>
#include <fstream>
#include "head.h"


class Client
{
public:
    Client();
    ~Client();

    void Run();
    
    


private:
    pipeFile _pipeFile;
    
    std::ifstream openTaskFile();

    PipeMsg _answer;
    //PipeMsg _outMsg;

    bool _send(PipeMsg& msg);
    bool sendAsyncRequest(PipeMsg& msg);
    bool sendSyncRequest(PipeMsg& msg);
    //bool _send(const std::string& input, SYNC& syncType);


};


