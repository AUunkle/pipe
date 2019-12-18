#include "pch.h"
#include "PipeMsg.h"


PipeMsg::PipeMsg()
{
    init();
}

PipeMsg::PipeMsg(const std::string& data) {
    init();
    if (!parse(data))
        _bufer = nullptr;
}


PipeMsg::~PipeMsg()
{
}

void PipeMsg::init()
{
    _bufer = std::shared_ptr <uint8_t[]>(new uint8_t[MAX_BUF_SIZE], std::default_delete<uint8_t[]>());
    _size = MAX_BUF_SIZE;
}

void * PipeMsg::getData()
{
    return static_cast<uint8_t*>(getBuf()) + sizeof(Head);
}

bool PipeMsg::parse(const std::string & data)
{
    std::string atr;
    std::istringstream ist(data);
    std::vector<std::string> v;

    while (ist >> atr) {
        v.push_back(atr);
    }
    if (v.size() < 2)
        return false;

    _header.sync = parseSync(v[0]);
    _header.mesageType = parseType(v[1]);
    _header.mesageSize = 0;
    _size = sizeof(struct Head);
    

    _dataPTR = _bufer.get() + _size;

    if (_header.mesageType == MSGType::GetLastReq ||
        _header.mesageType == MSGType::GetListObj ||
        _header.mesageType == MSGType::ObjStore) {
        std::memcpy(_bufer.get(), &_header, sizeof(struct Head));
        return true;
    }

    for (uint32_t i = 2; i < v.size();i++) {
        if (_header.mesageType == MSGType::Char) {
            parseBaseType<char>(v[i], &_header);
            continue;
        }
        if (_header.mesageType == MSGType::Double) {
            parseBaseType<double>(v[i], &_header);
            continue;
        }
        if (_header.mesageType == MSGType::Int32) {
            parseBaseType<int32_t>(v[i], &_header);
            continue;
        }
    }
    std::memcpy(_bufer.get(), &_header, sizeof(struct Head));
    return true;
}

void PipeMsg::updateCapacity(DWORD size)
{
    _size = size;
}

void PipeMsg::toString()
{
    Head * _head = static_cast<Head *>(getBuf());
    _header.mesageSize = _head->mesageSize;
    _header.mesageType = _head->mesageType;
    _header.sync = _head->sync;
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

SYNC PipeMsg::parseSync(std::string str)
{
    return str == "sync" ? SYNC::Sync : SYNC::Async;
}

MSGType PipeMsg::parseType(std::string str)
{
    if (str == "Char")
        return MSGType::Char;

    if (str == "Int32")
        return MSGType::Int32;

    if (str == "Double")
        return MSGType::Double;

    if (str == "GetLastReq")
        return MSGType::GetLastReq;

    if (str == "ObjStore")
        return MSGType::ObjStore;

    if (str == "GetListObj")
        return MSGType::GetListObj;

    if (str == "GetObjAttr")
        return MSGType::GetObjAttr;

    if (str == "ChAttrDig")
        return MSGType::ChAttrDig;

    if (str == "RemObj")
        return MSGType::RemObj;

    return MSGType::Undefined;
}
