#include "pch.h"
#include "srvMsg.h"
#include <array>

srvMsg::srvMsg()
{
}


srvMsg::~srvMsg()
{
}

void srvMsg::init()
{
    _bufer =  std::make_shared<std::array<uint8_t, MAX_BUF_SIZE>>();
    _byteAmount = MAX_BUF_SIZE;
}

void * srvMsg::getBuf()
{
    return  _bufer.get();
}

Head * srvMsg::getHead()
{
    return static_cast<Head*>(getBuf());
}

void * srvMsg::getData()
{
    return static_cast<uint8_t*>(getBuf()) + sizeof(Head);
}

DWORD srvMsg::getMAXSize()
{
    _byteAmount = MAX_BUF_SIZE;
    return _byteAmount;
}

DWORD srvMsg::getSize()
{
    return _byteAmount;
}

void srvMsg::updateCapacity(DWORD size)
{
    _byteAmount = size;
}

bool srvMsg::validation(DWORD amount)
{
    _head = static_cast<Head*>(getBuf());
    if (_head->head != MAGIC_ID)
        return false;
    if (_head->mesageType >= MSGType::MaxNumOfRequest)
        return false;
    if (_head->sync > SYNC::Async)
        return false;

    _head->mesageSize = amount - sizeof(Head);
    return true;
}

void srvMsg::parse()
{
    if (_head->mesageType == MSGType::Char) {
        LogBaseTypeData<char>(getData());
    }
    else if (_head->mesageType == MSGType::Double) {
        LogBaseTypeData<double>(getData());
    }
    else if (_head->mesageType == MSGType::Int32) {
        LogBaseTypeData<int32_t>(getData());
    }
}

bool srvMsg::isSync()
{
    return _head->sync == SYNC::Sync;
}

void srvMsg::prepareAnswer(srvMsg * request)
{
    init();
    if (request->getHead()->mesageType == MSGType::Char ||
        request->getHead()->mesageType == MSGType::Double ||
        request->getHead()->mesageType == MSGType::Int32) {
        std::memcpy(getBuf(), request->getBuf(), request->getSize());
        updateCapacity(request->getSize());
    };
}
