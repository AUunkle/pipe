#pragma once
#include <iostream>
#include "windows.h"
#include "head.h"

constexpr auto MAX_BUF_SIZE = 100 * 1024;

class srvMsg
{
public:
    srvMsg();
    ~srvMsg();

    void init();

    void* getBuf();
    Head* getHead();
    void* getData();
    DWORD getMAXSize();
    DWORD getSize();
    void updateCapacity(DWORD size);

    bool validation(DWORD amount);
    void parse();
    bool isSync();
    void prepareAnswer(srvMsg * request);

private:

    DWORD _byteAmount = 0;
    std::shared_ptr <std::array<uint8_t, MAX_BUF_SIZE>> _bufer;
    Head* _head = nullptr;

    template <typename T>
    void LogBaseTypeData(void* _msg) {
        std::cout << "Value is ";
        T* value = static_cast<T*>(_msg);
        for (int i = 0;
            i < (_head->mesageSize / sizeof(T));
            i++) {
            std::cout << *value << "  ";
            value++;
        };

        std::cout << std::endl;
    };
};

