#pragma once

#include <Arduino.h>

class StepCondition {

    protected:
        bool condition_met = false;
    
    public:
        StepCondition();
        virtual void Begin();
        virtual void Check();
        virtual void Reset();
        virtual void Set() {}

        bool IsMet();
};

class StepConditionDelay : public StepCondition {
    
    private:
        unsigned long start_time = 0;
        unsigned long delay_time;

    public:
        StepConditionDelay(unsigned long _delay_time);
        void Begin();
        void Check();

        void Set() override;
        void Reset();
};

class StepConditionDigitalInput : public StepCondition {
    
    private:
        uint8_t pin;
        bool is_pullup;

        bool last_state;
        unsigned long last_debounce_time = 0;

        const unsigned long debounce_delay = 50;

    public:
        StepConditionDigitalInput(uint8_t _pin, bool _is_pullup);
        void Begin();
        void Check();

        void Reset();
};