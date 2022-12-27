#ifndef INFORETRIEVER_H
#define INFORETRIEVER_H

#include "public_define.h"
#include <string>
#include <map>

struct GameStateContainer;
struct MemoryContainer;

class InfoRetriever
{
public:
    InfoRetriever(std::string name, const GameStateContainer& container, MemoryContainer& memory);

    MemoryContainer& m_memory;
    Location getMyLoc() const;
    Location getEnemyLoc() const;
    int getEnemyDist() const;
    int getWidth() const;
    int getHeight() const;
    int getDistToCenter(Location loc) const;
    std::vector<Location> getNearWalkableTiles(Location loc, int xRange, int yRange) const;
    std::vector<EntityStruct> getBombs() const;
    std::vector<EntityStruct> getSolidifiers() const;
    std::vector<Location> getCrates() const;
    std::vector<Location> getSolids() const;
    int getDegreesOfFreedom(Location loc) const;

    bool inRange(Location loc) const;
    bool isCrate(Location loc) const;
    bool isSolid(Location loc) const;

private:
    std::string m_myName;
    const GameStateContainer& m_container;
    std::string m_enemyName;
    Location m_myLoc;
    Location m_enemyLoc;
    std::vector< std::vector<TileStruct> > m_orderedTiles;

    void orderTiles();
};



#endif // INFORETRIEVER_H
