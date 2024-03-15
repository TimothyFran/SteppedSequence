#pragma once

#include <Arduino.h>

class StepAction {

    protected:
        unsigned long duration;
        unsigned long start_time;
        bool completed;

    public:
        StepAction();
        virtual void Begin();
        virtual void Start();
        virtual void Run();
        virtual void Finish() {};

        void SetDuration(unsigned long _duration);
        unsigned long GetDuration();

        bool IsCompleted();
        virtual bool ContinueOnCompleted() { return false; }

};

class StepActionGpio : public StepAction {
    
    private:
        uint8_t pin;
        bool target_state;

    public:
        StepActionGpio(uint8_t _pin, bool _target_state, unsigned long _duration = 0);

        void Begin();
        void Start();
        void Run();
        void Finish() override;

};