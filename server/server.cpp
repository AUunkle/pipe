#include "pch.h"
#include "server.h"
#include <array>
#include "Head.h"


using namespace std;



Server::Server()
{

    if (!ConnectNamedPipe(_pipe.pipePTR(), NULL))
        throw std::runtime_error("Error in connecting");

    std::cout << "Connected" << std::endl;
}

Server::~Server()
{
    _pipe.Disconnect();
}
bool Server::getRequest()
{
    DWORD _byteReadAmount = 0;

    _inMsg.init();
    bool res = ReadFile(_pipe.pipePTR(), _inMsg.getBuf(), _inMsg.getMAXSize(), &_byteReadAmount, nullptr);

    if (_byteReadAmount >= MAX_BUF_SIZE || _byteReadAmount < sizeof(Head))
        return false;

    if (!_inMsg.validation(_byteReadAmount))
        return false;

    _inMsg.updateCapacity(_byteReadAmount);
    return res;
}

bool Server::sendAnswer()
{
    DWORD writeAmount = 0;
    WriteFile(_pipe.pipePTR(), _outMsg.getBuf(), _outMsg.getSize(), &writeAmount, nullptr);

    return true;
}

void Server::Run() {
    _inMsg.init();
    while (_pipe.IsEnabled() && _pipe.IsConnected()) {
        std::cout << "Wait request" << std::endl;

        if (!getRequest())
        {
            std::cerr << "Failed to receive request, skipping..." << std::endl;
            continue;
        }

        std::cout << "Have Request" << std::endl;
        _inMsg.parse();

        _outMsg.prepareAnswer(&_inMsg);

        if (_inMsg.isSync()) {
            sendAnswer();
        }
        

    }
}

