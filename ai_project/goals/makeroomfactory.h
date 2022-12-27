#ifndef MAKEROOMFACTORY_H
#define MAKEROOMFACTORY_H

#include "goalfactory.h"

class MakeRoomFactory : public GoalFactory
{
public:
    MakeRoomFactory(InfoRetriever& retriever);
    virtual int weightGoal() override;
    virtual std::unique_ptr<Goal> giveGoal() override;
};

#endif // MAKEROOMFACTORY_H
