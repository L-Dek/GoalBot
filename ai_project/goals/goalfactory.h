#ifndef GOALFACTORY_H
#define GOALFACTORY_H

#include <memory>

class InfoRetriever;
class Goal;

class GoalFactory
{
public:
    GoalFactory(InfoRetriever& retriever);
    virtual ~GoalFactory() = default;
    virtual int weightGoal() = 0;
    virtual std::unique_ptr<Goal> giveGoal() = 0;
protected:
    InfoRetriever& m_retriever;
};

#endif // GOALFACTORY_H
