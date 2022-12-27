#ifndef __AIBASECLASS_H__
#define __AIBASECLASS_H__

#include "public_define.h"
/*
 * This is the base class that the new Alten joiners will extend to implement their AI.
 * For now it is a stub.
 */

class AIBaseClass
{
public:

    AIBaseClass();

    virtual ~AIBaseClass() = 0;

    virtual const std::string& GetName() = 0;

    virtual const std::string& GetIcon() = 0;

    /*
     * Main function to be implemented
     */
    virtual ActionType GetAction(const GameStateContainer& )  = 0;

    void SetPlayerName(const std::string& name);

protected:
    /**
     * @brief m_playerName the name of the player that is in the gameroom
     * this name can be linked to a playername that resides in the GameStatecontainer
     */
    std::string m_playerName;

};


#endif // __AIBASECLASS_H__
