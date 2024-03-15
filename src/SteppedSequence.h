#pragma once

#include <Arduino.h>
#include "Step.h"
#include "StepAction.h"
#include <Vector.h>

class SteppedSequence {

    private:
        Vector<Step*> steps;
        Step* steps_storage[15];
        uint16_t currentStepIndex = 0;

        bool started = false;

    public:
        SteppedSequence();
        
        void AddStep(Step* step);

        void Start();
        void Run();
        void BeginAll();

        uint16_t GetCurrentStepIndex();

};