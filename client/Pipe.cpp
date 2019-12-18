#include "pch.h"
#include "Pipe.h"


Pipe::Pipe()
{


}

Pipe::Pipe(const std::string& pipe_name) {

}

Pipe::~Pipe()
{
}

void* Pipe::pipePTR() {
    return _sharedHandle.get();
}

bool Pipe::Connect() {
    return ConnectNamedPipe(_sharedHandle.get(), NULL);
}

bool Pipe::Disconnect()
{
    return DisconnectNamedPipe(_sharedHandle.get());
}

bool Pipe::IsConnected()
{
    return ERROR_PIPE_NOT_CONNECTED != GetLastError();
}

bool Pipe::IsEnabled()
{
    return ERROR_BROKEN_PIPE != GetLastError();
}
