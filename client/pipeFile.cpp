#include "pch.h"
#include "pipeFile.h"

#include <iostream>

pipeFile::pipeFile()
{
    auto file = std::shared_ptr<void>(
        CreateFile(TEXT("\\\\.\\pipe\\myPipe"),
            GENERIC_READ | GENERIC_WRITE,
            0,
            nullptr,
            OPEN_EXISTING,
            0,
            nullptr
        ),
        [](HANDLE fileHandle) {CloseHandle(fileHandle);});

    _fileHandle = std::move(file);

    if (_fileHandle == nullptr || _fileHandle.get() == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Failed to create file");
    DWORD state = PIPE_READMODE_MESSAGE;
    SetNamedPipeHandleState(_fileHandle.get(), &state, nullptr, nullptr);

}


pipeFile::~pipeFile()
{
}

bool pipeFile::IsEnabled()
{
    return ERROR_PIPE_NOT_CONNECTED != GetLastError();
}

void * pipeFile::getHandle()
{
    return _fileHandle.get();
}

//bool pipeFile::SendMsg(PipeMsg& _msg) {
//    if (!_msg.getBuf())
//        return false;
//
//    DWORD writeAmount = 0;
//    if (!WriteFile(_fileHandle.get(), _msg.getBuf(), _msg.getSize(), &writeAmount, nullptr)
//        || writeAmount != _msg.getSize()) {
//        return false;
//    }
//
//    return true;
//}


//bool pipeFile::SendReceiveMsg(PipeMsg& _msg){
//    if (!_msg.getBuf() || !_msg.getAnswerBuf())
//        return false;
//
//    DWORD bytes_read_;
//    if (!TransactNamedPipe(_fileHandle.get(),
//        _msg.getBuf(), _msg.getSize(),
//        _msg.getAnswerBuf(), _msg.getAnswerSize(),
//        &bytes_read_, nullptr)
//        || bytes_read_ >= _msg.getAnswerSize()) {
//        std::cout << "somth wron" << std::endl;
//        return false;
//    }
//        
//
//    _msg.setAnswerSize(bytes_read_);
//    return true;
//}

//
//bool File::ReceiveBuffer(buffer::Ptr& buffer) {
//    if (!buffer)
//        return false;
//
//    // Read the file
//    DWORD bytes_read_;
//    if (!ReadFile(handle_.get(), buffer->GetData(), buffer->GetAllocatedSize(), &bytes_read_, nullptr)
//        || bytes_read_ >= buffer->GetAllocatedSize())
//        return false;
//
//    // Set the buffer size
//    buffer->SetSize(bytes_read_);
//    return true;
//}
