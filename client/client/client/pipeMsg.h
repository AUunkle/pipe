#pragma once
#include "head.h"
#include <sstream>
#include <iostream>
#include <vector>

constexpr auto MAX_BUF_SIZE = 100 * 1024;

struct mesage {
    struct Head header;

};

class PipeMsg
{
public:
    PipeMsg();
    explicit PipeMsg(const std::string& data);
    
    ~PipeMsg();

    void init();

    void * getData();


    bool parse(const std::string& data);

    DWORD getSize() { 
        return _size; 
    };
    void updateCapacity(DWORD size);

    void* getBuf() { return _bufer.get(); }

    void toString();
   /* uint8_t* getAnswerBuf() { 
        if (!_answer.get()) {
            _answer = std::shared_ptr <BYTE[]>(new BYTE[MAX_BUF_SIZE], std::default_delete<BYTE[]>());
            _answer_size = MAX_BUF_SIZE;
        }
        return _answer.get();
    }*/

    bool isSync() {
        return _header.sync == SYNC::Sync;
    }


    
private:
    struct Head _header;
    SYNC parseSync(std::string str);
    MSGType parseType(std::string str);

    std::shared_ptr < uint8_t[]> _bufer;
    DWORD _size;
    uint8_t* _dataPTR = nullptr;

    template <typename T>
    void parseBaseType(std::string src, struct Head * h) {
        std::stringstream _stream(src);
        T value;
        _stream >> value;
        uint8_t addition = sizeof(T);

        h->mesageSize += addition;
        _size += addition;
        
        
        std::memcpy(_dataPTR, &value, addition);
        _dataPTR += addition;
        return; 
    };

    template <typename T>
    void LogBaseTypeData(void* _msg) {
        std::cout << "Value is ";
        T* value = static_cast<T*>(_msg);
        for (int i = 0;
            i < (_header.mesageSize / sizeof(T));
            i++) {
            std::cout << *value << "  ";
            value++;
        };

        std::cout << std::endl;
    };
};

