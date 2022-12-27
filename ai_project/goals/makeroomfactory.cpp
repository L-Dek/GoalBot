#include "makeroomfactory.h"
#include "makeroomgoal.h"


MakeRoomFactory::MakeRoomFactory(InfoRetriever& retriever) :
    GoalFactory(retriever)
{}

int MakeRoomFactory::weightGoal()
{
    return 5;
}

std::unique_ptr<Goal> MakeRoomFactory::giveGoal()
{
    return std::unique_ptr<Goal>(new MakeRoomGoal(m_retriever));
}
