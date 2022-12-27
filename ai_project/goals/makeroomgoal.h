#ifndef MAKEROOMGOAL_H
#define MAKEROOMGOAL_H

#include "goal.h"

class MakeRoomGoal : public Goal
{
public:
    MakeRoomGoal(InfoRetriever& retriever);
    virtual ActionType decideAction() override;
    virtual void talk() override;
private:
    int chooseRandomDirection() const;
};

#endif // MAKEROOMGOAL_H
