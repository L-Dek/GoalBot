#include "dontgetkilledgoal.h"
#include "inforetriever.h"
#include "pathfinder.h"
#include "safetymatrix.h"
#include "utils.h"

#include <iostream>


DontGetKilledGoal::DontGetKilledGoal(InfoRetriever& retriever) :
    Goal(retriever)
{}

ActionType DontGetKilledGoal::decideAction()
{
    SafetyMatrix safetyMatrix(m_retriever);
    safetyMatrix.buildMatrix();

    int dofs = m_retriever.getDegreesOfFreedom(m_retriever.getMyLoc());

    if (!safetyMatrix.isSafe(m_retriever.getMyLoc()) || dofs < 4)
    {
        PathFinder pathFinder(m_retriever);
        Location firstTile = pathFinder.getFleeingTile();
        int deltaX = firstTile.x - m_retriever.getMyLoc().x;
        int deltaY = firstTile.y - m_retriever.getMyLoc().y;
        if (deltaX == 1)
        {
            return ActionType::Right;
        } else if (deltaX == -1)
        {
            return ActionType::Left;
        } else if (deltaY == 1)
        {
            return ActionType::Down;
        } else if (deltaY == -1)
        {
            return ActionType::Up;
        } else
        {
            return ActionType::Hold;
        }
    }
    return ActionType::Hold;
}

void DontGetKilledGoal::talk()
{
    std::cout << "DontGetKilledGoal" << std::endl;
}
