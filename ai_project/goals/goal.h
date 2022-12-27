#ifndef GOAL_H
#define GOAL_H

#include "public_define.h"

class InfoRetriever;

class Goal
{
public:
    Goal(InfoRetriever& retriever);
    virtual ~Goal() = default;
    int weight;
    virtual ActionType decideAction() = 0;
    virtual void talk() = 0;
protected:
    InfoRetriever& m_retriever;
};

#endif // GOAL_H
