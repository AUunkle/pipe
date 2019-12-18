#include "pch.h"
#include "Client.h"
#include "windows.h"
#include <iostream>
#include "PipeMsg.h"



using namespace std;

Client::Client()
{
}


Client::~Client()
{
}

ifstream Client::openTaskFile() {

    ifstream In("taskList.dat");
    if (!In.is_open())
        throw("haven't task file");
    return In;

}

bool Client::sendAsyncRequest(PipeMsg& msg)
{
    DWORD writeAmount = 0;
    if (!WriteFile(_pipeFile.getHandle(), msg.getBuf(), msg.getSize(), &writeAmount, nullptr))
        return false;


    return true;
}

bool Client::sendSyncRequest(PipeMsg& msg)
{
    _answer.init();
    DWORD _byteReadAmount = 0;
    if (!TransactNamedPipe(_pipeFile.getHandle(),
        msg.getBuf(), msg.getSize(),
        _answer.getBuf(), _answer.getSize(),
        &_byteReadAmount, nullptr)) {
        std::cout << "Error" << std::endl;
        return false;
    }
    _answer.updateCapacity(_byteReadAmount);

    _answer.toString();
    return true;
}

bool Client::_send(PipeMsg& msg) {
    if (!msg.getBuf())
        return false;


    if (msg.isSync())
        return sendSyncRequest(msg);

    return sendAsyncRequest(msg);
}

void Client::Run()
{
    auto taskFileStream = openTaskFile();

    while (_pipeFile.IsEnabled() && !taskFileStream.eof()) {
        string msgTXT;
        getline(taskFileStream, msgTXT);

        PipeMsg msg(msgTXT);


        if (!_send(msg)) {
            cout << "Request " << msgTXT << "  is not supported" << endl;
            continue;
        }
    }
    //    if (syncType == SYNC::Sync)
    //        cout << msgTXT << endl;

    //}



}

/*
async Char         a
sync  getLastReq
async int32        123456
sync  getLastReq
sync  double       0.01234536
sync  objStore
sycn  objStore
sync  getListObj
sync  getObj       1
sycn  objStore
sync  getObjAttr   2
sync  chAttrDig    2  55
sync  getObjAttr   2
sync  remObj       2
sync  getListObj


*/