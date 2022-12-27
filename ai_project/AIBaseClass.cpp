#include "AIBaseClass.h"


AIBaseClass::AIBaseClass()
    : m_playerName("")
{}

AIBaseClass::~AIBaseClass()
{}

void AIBaseClass::SetPlayerName(const std::string& name)
{
    m_playerName = name;
}
