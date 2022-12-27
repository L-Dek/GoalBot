#include "goalcreator.h"
#include "goals/goalfactory.h"
#include "goals/dontgetkilledfactory.h"
#include "goals/makeroomfactory.h"
#include "inforetriever.h"
#include "goals/goal.h"
#include "goals/dontgetkilledgoal.h"
#include "goals/makeroomgoal.h"
#include "safetymatrix.h"
#include "utils.h"

#include <algorithm>
#include <iostream>


GoalCreator::GoalCreator(InfoRetriever& retriever) :
    m_retriever(retriever)
{}

std::unique_ptr<Goal> GoalCreator::createGoal()
{     
    std::vector< GoalFactory* > goalFactories;

    DontGetKilledFactory dontGetKilledFactory(m_retriever);
    MakeRoomFactory makeRoomFactory(m_retriever);

    goalFactories.emplace_back(&dontGetKilledFactory);
    goalFactories.emplace_back(&makeRoomFactory);

    std::vector<int> goalWeights;

    for (GoalFactory* goalFactory : goalFactories)
    {
      goalWeights.emplace_back(goalFactory->weightGoal());
    }

    int maxWeight = *std::max_element(goalWeights.begin(), goalWeights.end());
    int weightIndex = Utils::getIndex(goalWeights, maxWeight);

    std::unique_ptr<Goal> bestGoal = goalFactories[weightIndex]->giveGoal();

    return bestGoal;
}
