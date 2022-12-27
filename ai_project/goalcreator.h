#ifndef GOALCREATOR_H
#define GOALCREATOR_H

#include <memory>

class InfoRetriever;
class Goal;

class GoalCreator
{
public:
    GoalCreator(InfoRetriever& retriever);
    std::unique_ptr<Goal> createGoal();
private:
    InfoRetriever& m_retriever;
};

#endif // GOALCREATOR_H
