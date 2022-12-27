#ifndef DONTGETKILLEDFACTORY_H
#define DONTGETKILLEDFACTORY_H

#include "goalfactory.h"

class DontGetKilledFactory : public GoalFactory
{
public:
    DontGetKilledFactory(InfoRetriever& retriever);
    virtual int weightGoal() override;
    virtual std::unique_ptr<Goal> giveGoal() override;
};

#endif // DONTGETKILLEDFACTORY_H
