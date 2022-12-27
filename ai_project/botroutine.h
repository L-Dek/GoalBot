#ifndef BOTROUTINE_H
#define BOTROUTINE_H

#include "public_define.h"

class InfoRetriever;
struct MemoryContainer;

class BotRoutine
{
public:
    explicit BotRoutine(InfoRetriever& retriever, MemoryContainer& memory);
    ActionType generateAction();
private:
    InfoRetriever& m_retriever;
    MemoryContainer& m_memory;
};

#endif // BOTROUTINE_H
