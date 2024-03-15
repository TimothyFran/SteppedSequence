#pragma once

#include <Arduino.h>
#include <Vector.h>
#include "StepCondition.h"
#include "StepAction.h"
#include "StepActionServo.h"

class Step {

    private:
        Vector<StepCondition*> conditions;
        Vector<StepAction*> actions;

        StepCondition* conditions_storage[10];
        StepAction* actions_storage[10];

    public:
        Step();

        void AddCondition(StepCondition* _condition);
        void AddAction(StepAction* _action);

        bool CanExecute();
        void CheckCondition();

        void SetConditions();
        void Start();
        void Run();

        bool IsDone();

        void Reset();
        void Begin();
};