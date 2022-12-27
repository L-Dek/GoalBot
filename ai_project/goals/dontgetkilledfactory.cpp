#include "dontgetkilledfactory.h"
#include "dontgetkilledgoal.h"
#include "inforetriever.h"
#include "safetymatrix.h"

#include <memory>
#include <iostream>


DontGetKilledFactory::DontGetKilledFactory(InfoRetriever& retriever) :
    GoalFactory(retriever)
{}

int DontGetKilledFactory::weightGoal()
{
    SafetyMatrix safetyMatrix(m_retriever);
    safetyMatrix.buildMatrix();

    int weight;
    if (safetyMatrix.isSafe(m_retriever.getMyLoc()) && m_retriever.getEnemyDist() > 4)
    {
        weight = 0;
    } else
    {
        weight = 10;
    }
    return weight;
}

std::unique_ptr<Goal> DontGetKilledFactory::giveGoal()
{
    return std::unique_ptr<Goal>(new DontGetKilledGoal(m_retriever));
}
