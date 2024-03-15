#include <SteppedSequence.h>

#define START_BUTTON_PIN        2
#define IS_START_BUTTON_PULLUP  true

#define SERVO_PIN           9
#define SERVO_SPEED         ServoSpeed::MEDIUM
#define SERVO_TARGET_ANGLE  90
#define SERVO_HOLD_ANGLE    0

#define DONE_LED_PIN        13
#define DONE_PULSE_DURATION 1000

SteppedSequence sequence;

Step Step1;
StepConditionDigitalInput Step1Condition(START_BUTTON_PIN, IS_START_BUTTON_PULLUP);
StepActionServo Step1Action(SERVO_PIN, SERVO_TARGET_ANGLE, SERVO_HOLD_ANGLE, SERVO_SPEED);

Step Step2;
StepActionGpio Step2Action(DONE_LED_PIN, HIGH, DONE_PULSE_DURATION);

void setup() {
    Serial.begin(9600);

    Step1.AddCondition(&Step1Condition);
    Step1.AddAction(&Step1Action);

    Step2.AddAction(&Step2Action);

    sequence.AddStep(&Step1);
    sequence.AddStep(&Step2);

    sequence.BeginAll();
    sequence.Start();
}

void loop() {
    
    static uint16_t lastStep = -1;

    sequence.Run();

    uint16_t currentStep = sequence.GetCurrentStepIndex();
    if (currentStep != lastStep) {
        Serial.print("Running step: ");
        Serial.println(currentStep);
        lastStep = currentStep;
    }

}