#include "SteppedSequence.h"

SteppedSequence::SteppedSequence() {
  steps.setStorage(steps_storage);
}

void SteppedSequence::AddStep(Step* step) {
    steps.push_back(step);
    Serial.print("New step. Count: ");
    Serial.println(steps.size());
}

void SteppedSequence::Start() {
    started = true;
    steps[0]->Begin();
}

void SteppedSequence::Run() {
    if(!started) return;

    static uint16_t lastStep = 0;

    if(currentStepIndex > steps.size()) currentStepIndex = 0;

    Step* currentStep = steps[currentStepIndex];
    if(currentStep == nullptr) {
      currentStepIndex = 0;
      return;
    }

    if(currentStepIndex != lastStep) {
      currentStep->SetConditions();
      lastStep = currentStepIndex;
    }

    currentStep->CheckCondition();
    if(!currentStep->CanExecute()) return;

    currentStep->Start();
    while(!currentStep->IsDone()) {
        currentStep->Run();
    }
    currentStep->Reset();

    currentStepIndex++;
}

uint16_t SteppedSequence::GetCurrentStepIndex() {
    return currentStepIndex;
}

void SteppedSequence::BeginAll() {
    for(uint16_t i = 0; i < steps.size(); i++) {
        if(steps[i] == nullptr) break;
        Serial.print("Beginning step ");
        Serial.println(i);
        steps[i]->Begin();
    }
}