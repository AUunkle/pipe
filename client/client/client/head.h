#pragma once
#include <iostream>
#include "windows.h"

//constexpr DWORD MAX_BUF_SIZE = 100 * 1024;

constexpr uint16_t MAGIC_ID  = 0x1234;

enum class MSGType : uint8_t
{   Undefined = 0,
    Char,
    Int32,
    Double,
    GetLastReq,
    ObjStore,
    GetListObj,
    GetObjAttr,
    ChAttrDig,
    RemObj,
    MaxNumOfRequest
};

enum class SYNC : uint8_t
{
    Sync = 0,
    Async
};


#pragma pack (push, 1)
struct Head
{
    const uint16_t head = MAGIC_ID;
    uint32_t mesageSize = 0;
    MSGType mesageType = MSGType::GetLastReq;
    SYNC sync = SYNC::Sync;

    Head() {};
};

#pragma pack (pop)
