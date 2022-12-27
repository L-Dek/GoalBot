#include "safetymatrix.h"
#include "public_define.h"
#include "inforetriever.h"
#include "utils.h"

#include <iostream>


SafetyMatrix::SafetyMatrix(const InfoRetriever& retriever) :
    InfoMatrix(retriever)
{}

// Creates a matrix where the indices correspond to the tile location.
// Each element of the matrix contains the number of cycles that the tile is safe.
void SafetyMatrix::buildMatrix()
{
    // First initialize matrix with -1 (i.e. assume every tile safe)
    int safeCycles = -1;
    m_matrix = std::vector< std::vector<int> >(m_retriever.getWidth(), std::vector<int>(m_retriever.getHeight(), safeCycles));;

    auto bombs = m_retriever.getBombs();
    for (auto& bomb : bombs)
    {
        placeBomb(bomb.loc, bomb.duration);
    }

    auto solidifiers = m_retriever.getSolidifiers();
    for (auto& solidifier : solidifiers)
    {
        updateMatrixVal(solidifier.loc, solidifier.duration);
    }
}

void SafetyMatrix::updateMatrixVal(Location loc, int safeCycles)
{
    if (!m_retriever.inRange(loc))
    {
        return;
    } else
    {
        if (getMatrixVal(loc) > 0)
        {
            if (safeCycles < getMatrixVal(loc))
            {
                m_matrix[loc.x][loc.y] = safeCycles;
            } else
            {
                return;
            }
        } else
        {
            m_matrix[loc.x][loc.y] = safeCycles;
        }
    }
}

// Updates the matrix with the duration values of a bomb.
void SafetyMatrix::placeBomb(Location loc, int duration)
{
    int safeCycles = -1;
    for (int dir = North; dir != Last; ++dir)
    {
        for (int depth = 0; depth < 4; depth++)
        {
            Location offsetLoc = Utils::offsetLocation(loc, (direction)dir, depth);
            if (!m_retriever.inRange(offsetLoc) || m_retriever.isCrate(offsetLoc) || m_retriever.isSolid(offsetLoc)) // Cannot stand here
            {
                break;
            } else
            {
                safeCycles = duration;
            }
            updateMatrixVal(offsetLoc, safeCycles);
        }
    }
}

std::vector<Location> SafetyMatrix::findNearSafeTiles(Location loc) const
{
    int x;
    int y;
    std::vector<Location> nearSafeTiles;

    for (int deltaX = -3; deltaX < 4; ++deltaX)
    {
        for (int deltaY = -3; deltaY < 4; ++deltaY)
        {
            x = loc.x + deltaX;
            y = loc.y + deltaY;
            Location newLoc = Location(x, y);

            if (m_retriever.inRange(newLoc) && isSafe(newLoc))
            {
                nearSafeTiles.emplace_back(newLoc);
            }
        }
    }
    return nearSafeTiles;
}

bool SafetyMatrix::isSafe(Location loc) const
{
    if (m_retriever.inRange(loc))
    {
        return (m_matrix[loc.x][loc.y] == -1);
    } else
    {
        return false; // outside of playing field
    }
}
