#ifndef DONTGETKILLEDGOAL_H
#define DONTGETKILLEDGOAL_H

#include "goal.h"

class DontGetKilledGoal : public Goal
{
public:
    DontGetKilledGoal(InfoRetriever& retriever);
    virtual ActionType decideAction() override;
    virtual void talk() override;
};

#endif // DONTGETKILLEDGOAL_H
