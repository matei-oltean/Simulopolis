#pragma once

#include "ai/GoalEvaluator.h"

class GoalGetBetterHomeEvaluator : public GoalEvaluator
{
public:
    GoalGetBetterHomeEvaluator(float bias);

    virtual float computeDesirability(Person* person) override;

    virtual void setGoal(Person* person) override;

private:
};
