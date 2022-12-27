#include "makeroomgoal.h"
#include "AStar.hpp"
#include "inforetriever.h"
#include "safetymatrix.h"
#include "utils.h"
#include "memorycontainer.h"

#include <iostream>


MakeRoomGoal::MakeRoomGoal(InfoRetriever& retriever) :
    Goal(retriever)
{}

ActionType MakeRoomGoal::decideAction()
{
    SafetyMatrix safetyMatrix(m_retriever);
    safetyMatrix.buildMatrix();

    int dir = chooseRandomDirection();
    Location newLoc = Utils::offsetLocation(m_retriever.getMyLoc(), (direction)dir, 1);
    Location previousLoc = m_retriever.m_memory.m_location;

    int rotation = 0;
    while ( (m_retriever.isSolid(newLoc) || !m_retriever.inRange(newLoc) || (newLoc.x == previousLoc.x && newLoc.y == previousLoc.y)) && rotation < 5 )
    {
        dir = (dir+1)%4;
        rotation++;
        newLoc = Utils::offsetLocation(m_retriever.getMyLoc(), (direction)dir, 1);
    }

    if (m_retriever.isSolid(newLoc) || !(m_retriever.inRange(newLoc)) )
    {
        return ActionType::Hold;
    } else if (m_retriever.isCrate(newLoc))
    {
        return ActionType::Bomb;
        // return placeBomb(newLoc.x, newLoc.y);
    }

    std::vector<Location> nearSafeTiles = safetyMatrix.findNearSafeTiles(m_retriever.getMyLoc());
    std::vector<AStar::Vec2i> nearSafeTilesAStar = Utils::locationVec_to_AStarVec(nearSafeTiles);
    AStar::Vec2i newLocAStar = {newLoc.x, newLoc.y};
    if (std::count(nearSafeTilesAStar.begin(), nearSafeTilesAStar.end(), newLocAStar)) {
        switch ((direction)dir)
        {
        case North:
            return ActionType::Up;
            break;
        case East:
            return ActionType::Right;
            break;
        case South:
            return ActionType::Down;
            break;
        case West:
            return ActionType::Left;
            break;
        }
    }
    return ActionType::Hold;
}

void MakeRoomGoal::talk()
{
    std::cout << "MakeRoomGoal" << std::endl;
}

int MakeRoomGoal::chooseRandomDirection() const
{
    int xOffset = m_retriever.getMyLoc().x - m_retriever.getWidth()/2;
    int yOffset = m_retriever.getMyLoc().y - m_retriever.getHeight()/2;

    std::vector<int> directions{0, 0, 0, 0, 0, 0};

    if (xOffset < 0 && yOffset < 0) // upper left quadrant
    {
        directions = {0, 1, 1, 2, 2, 3}; // north, east, east, south, south, west
    } else if (xOffset > 0 && yOffset < 0) // upper right quadrant
    {
        directions = {0, 1, 2, 2, 3, 3}; // n, e, s, s, w, w
    } else if (xOffset > 0 && yOffset > 0) // lower right quadrant
    {
        directions = {0, 0, 1, 2, 3, 3}; // n, n, e, s, w, w
    } else if (xOffset < 0 && yOffset > 0) // lower left quadrant
    {
        directions = {0, 0, 1, 1, 2, 3}; // n, n, e, e, s, w
    }

    int randomIndex = rand() % 6;

    return directions[randomIndex];
    // note: havent checked yet if an if-clause is always chosen
}
