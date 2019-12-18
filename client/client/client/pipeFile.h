#pragma once
#include <windows.h>
#include <iostream>
#include "pipeMsg.h"

class pipeFile
{
public:
    pipeFile();
    ~pipeFile();

    bool IsEnabled();

    void* getHandle();

   // bool SendMsg(PipeMsg& _msg);
   // bool SendReceiveMsg(PipeMsg& _inMsg);

private:

    std::shared_ptr<void> _fileHandle;
};

