#include "pch.h"
#include "Pipe.h"


Pipe::Pipe()
{
    auto pipe = std::shared_ptr<void>(CreateNamedPipe(TEXT("\\\\.\\pipe\\myPipe"),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE,
        PIPE_UNLIMITED_INSTANCES,
        0,
        0,
        NMPWAIT_USE_DEFAULT_WAIT, nullptr),
        [](auto pipeHandle) {CloseHandle(pipeHandle);});

    _pipeHandle = std::move(pipe);

    DWORD mode = PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(_pipeHandle.get(), &mode, nullptr, nullptr);

}

Pipe::~Pipe()
{
}

void* Pipe::pipePTR() {
    return _pipeHandle.get();
}



bool Pipe::Connect() {
    return ConnectNamedPipe(_pipeHandle.get(), NULL);
}

bool Pipe::Disconnect()
{
    return DisconnectNamedPipe(_pipeHandle.get());
}

bool Pipe::IsConnected()
{
    return ERROR_PIPE_NOT_CONNECTED != GetLastError();
}

bool Pipe::IsEnabled()
{
    return ERROR_BROKEN_PIPE != GetLastError();
}
