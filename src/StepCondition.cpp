#include "StepCondition.h"

StepCondition::StepCondition() {
    
}

bool StepCondition::IsMet() {
    return condition_met;
}

StepConditionDelay::StepConditionDelay(unsigned long _delay_time) {
    delay_time = _delay_time;
}

void StepConditionDelay::Begin() {
}

void StepConditionDelay::Set() {
    start_time = millis();
}

void StepConditionDelay::Check() {
    if(start_time == 0) return;
    if((millis() - start_time) > delay_time) {
        condition_met = true;
        Serial.println("Delay met");
    }
}

void StepConditionDelay::Reset() {
    condition_met = false;
    start_time = 0;
}

StepConditionDigitalInput::StepConditionDigitalInput(uint8_t _pin, bool _is_pullup) {
    pin = _pin;
    is_pullup = _is_pullup;
}

void StepConditionDigitalInput::Begin() {
    pinMode(pin, is_pullup ? INPUT_PULLUP : INPUT);
    last_state = digitalRead(pin);
}

void StepConditionDigitalInput::Check() {
    bool reading = digitalRead(pin);

    if(reading != last_state) {
        last_debounce_time = millis();
    }

    if((millis() - last_debounce_time) > debounce_delay) {
        if(reading == is_pullup ? LOW : HIGH) {
            condition_met = true;
        }
    }

    last_state = reading;
}

void StepConditionDigitalInput::Reset() {
    condition_met = false;
    last_debounce_time = 0;
}