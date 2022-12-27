#include "botroutine.h"
#include "inforetriever.h"
#include "MemoryContainer.h"
#include "goalcreator.h"
#include "goals/goal.h"


BotRoutine::BotRoutine(InfoRetriever& retriever, MemoryContainer& memory) :
    m_retriever(retriever),
    m_memory(memory)
{}

ActionType BotRoutine::generateAction()
{
    GoalCreator goalCreator(m_retriever);
    std::unique_ptr<Goal> goal = goalCreator.createGoal();
    ActionType action = goal->decideAction();
    m_memory.m_location = m_retriever.getMyLoc();

    return action;
}
