#ifndef AGENT_H
#define AGENT_H

#include "AIBaseClass.h"
#include <MemoryContainer.h> // kan geen forward declaration doen want is geen ref/pointer

class Agent : public AIBaseClass
{
public:
    Agent();

    ~Agent();

    const std::string& GetName();

    const std::string& GetIcon();

    ActionType GetAction(const GameStateContainer& container);

    MemoryContainer m_memory;

private:
    // DO NOT CHANGE //
    static const std::string m_name;

    static const std::string m_icon;
};

#endif // AGENT_H
