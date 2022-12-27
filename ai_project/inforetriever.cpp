#include "inforetriever.h"
#include "public_define.h"
#include "utils.h"
#include <string>
#include <iostream>


InfoRetriever::InfoRetriever(std::string name, const GameStateContainer& container, MemoryContainer& memory) :
    m_memory(memory),
    m_myName(name),
    m_container(container)
{
    // Save player location, enemy location, and enemy name
    for (auto& player : container.players)
    {
        if (player.playerName == m_myName)
        {
            m_myLoc = player.loc;
        } else
        {
            m_enemyName = player.playerName;
            m_enemyLoc = player.loc;
        }
    }
    m_orderedTiles = std::vector< std::vector<TileStruct> >( m_container.width, std::vector<TileStruct>(m_container.height) );
    orderTiles();
}

Location InfoRetriever::getMyLoc() const
{
    return m_myLoc;
}

Location InfoRetriever::getEnemyLoc() const
{
    return m_enemyLoc;
}

// Manhattan distance between the two opponents
int InfoRetriever::getEnemyDist() const
{
    int xDist = abs(m_myLoc.x - m_enemyLoc.x);
    int yDist = abs(m_myLoc.y - m_enemyLoc.y);
    return xDist + yDist;
}

int InfoRetriever::getWidth() const
{
    return m_container.width;
}

int InfoRetriever::getHeight() const
{
    return m_container.height;
}

// Manhattan distance of Location loc to center of playing field
int InfoRetriever::getDistToCenter(Location loc) const
{
    int xDist = abs(loc.x - m_container.width/2);
    int yDist = abs(loc.y - m_container.height/2);
    return xDist + yDist;
}

std::vector<EntityStruct> InfoRetriever::getBombs() const
{
    std::vector<EntityStruct> bombs;

    for (auto& entity : m_container.entities)
    {
        if (entity.type == "Bomb")
        {
            bombs.emplace_back(entity);
        }
    }
    return bombs;
}

std::vector<EntityStruct> InfoRetriever::getSolidifiers() const
{
    std::vector<EntityStruct> solidifiers;

    for (auto& entity : m_container.entities)
    {
        if (entity.type == "Solidifier")
        {
            solidifiers.emplace_back(entity);
        }
    }
    return solidifiers;
}

std::vector<Location> InfoRetriever::getCrates() const
{
    std::vector<Location> crates;

    for (auto& tile : m_container.tiles)
    {
        if (tile.crate)
        {
            crates.emplace_back(Location(tile.loc.x, tile.loc.y));
        }
    }
    return crates;
}

std::vector<Location> InfoRetriever::getSolids() const
{
    std::vector<Location> solids;

    for (auto& tile : m_container.tiles)
    {
        if (tile.type == "Solid")
        {
            solids.emplace_back(Location(tile.loc.x, tile.loc.y));
        }
    }
    return solids;
}

std::vector<Location> InfoRetriever::getNearWalkableTiles(Location loc, int xRange, int yRange) const
{
    int x;
    int y;
    std::vector<Location> nearWalkableTiles;

    for (int deltaX = -xRange; deltaX < xRange+1; ++deltaX)
    {
        for (int deltaY = -yRange; deltaY < yRange+1; ++deltaY)
        {
            x = loc.x + deltaX;
            y = loc.y + deltaY;
            Location tempLoc = Location(x,y);

            if (inRange(tempLoc))
            {
                if (!isCrate(tempLoc) && !isSolid(tempLoc))
                {
                    nearWalkableTiles.emplace_back(tempLoc);
                }
            }
        }
    }
    return nearWalkableTiles;
}

int InfoRetriever::getDegreesOfFreedom(Location loc) const
{
    int dofs = 4;
    for (int directionInt = North; directionInt != Last; ++directionInt)
    {
       direction dir = static_cast<direction>(directionInt);
       Location sideStep = Utils::offsetLocation(loc, dir, 1);
       if ( isCrate(sideStep) || isSolid(sideStep) )
       {
           --dofs;
       }
    }
    return dofs;
}

bool InfoRetriever::inRange(Location loc) const
{
    return (loc.x > -1 && loc.y > -1 && loc.x < m_container.width && loc.y < m_container.height);
}

bool InfoRetriever::isCrate(Location loc) const
{
    if (inRange(loc))
    {
        if (m_orderedTiles[loc.x][loc.y].crate)
        {
            return true;
        }
    }
    return false;
}

bool InfoRetriever::isSolid(Location loc) const
{
    if (inRange(loc))
    {
        if (m_orderedTiles[loc.x][loc.y].type == "Solid")
        {
            return true;
        }
    }
    return false;
}

void InfoRetriever::orderTiles()
{
    for (auto& tile : m_container.tiles)
    {
        m_orderedTiles[tile.loc.x][tile.loc.y] = tile;
    }
}
