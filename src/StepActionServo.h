#pragma once

#include <Arduino.h>
#include "StepAction.h"
#include <Servo.h>

enum ServoSpeed {
    SLOW = 30UL,
    MEDIUM = 15UL,
    FAST = 0UL
};

class StepActionServo : public StepAction {
    
    private:
        Servo servo;
        uint8_t pin;
        uint8_t targetAngle;
        uint8_t holdAngle;
        uint8_t currentAngle;

        unsigned long lastUpdate;
        ServoSpeed speed;

        void StepToAngle(uint8_t angle);
        void GoToAngle(uint8_t angle);

    public:
        StepActionServo(uint8_t pin, uint8_t angle, uint8_t _hold_hangle, ServoSpeed speed = ServoSpeed::MEDIUM);

        void Begin() override;
        void Start();
        void Run();

        void Reset();
        virtual bool ContinueOnCompleted() { return true; }

};