#include "StepAction.h"

StepAction::StepAction() {
}

void StepAction::SetDuration(unsigned long _duration) {
    duration = _duration;
}

unsigned long StepAction::GetDuration() {
    return duration;
}

void StepAction::Begin() {
}

StepActionGpio::StepActionGpio(uint8_t _pin, bool _target_state, unsigned long _duration) {
    pin = _pin;
    target_state = _target_state;
    duration = _duration;
}

void StepActionGpio::Begin() {
    pinMode(pin, OUTPUT);
}

void StepActionGpio::Start() {
    start_time = millis();
    digitalWrite(pin, target_state);
    completed = false;
}

void StepActionGpio::Run() {
    if (millis() - start_time > duration && duration != 0) {
        digitalWrite(pin, !target_state);
        completed = true;
    }
}

void StepActionGpio::Finish() {
    digitalWrite(pin, !target_state);
    completed = false;
}

bool StepAction::IsCompleted() {
    return completed;
}