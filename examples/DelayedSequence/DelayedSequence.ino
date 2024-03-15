#include <SteppedSequence.h>

#define START_BUTTON_PIN        2
#define IS_START_BUTTON_PULLUP  true

#define PRE_SEQUENCE_DELAY  1000

#define GREEN_LED_PIN   13
#define YELLOW_LED_PIN  12
#define RED_LED_PIN     11

#define GREEN_DURATION  5000
#define YELLOW_DURATION 2000
#define RED_DURATION    5000

SteppedSequence sequence;

Step Step1;
StepConditionDigitalInput Step1Condition(START_BUTTON_PIN, IS_START_BUTTON_PULLUP);

Step Step2;
StepConditionDelay Step2Condition(PRE_SEQUENCE_DELAY);
StepActionGpio Step2Action(GREEN_LED_PIN, HIGH, GREEN_DURATION);

Step Step3;
StepActionGpio Step3Action(YELLOW_LED_PIN, HIGH, YELLOW_DURATION);

Step Step4;
StepActionGpio Step4Action(RED_LED_PIN, HIGH, RED_DURATION);

void setup() {
    Serial.begin(9600);

    Step1.AddCondition(&Step1Condition);

    Step2.AddCondition(&Step2Condition);
    Step2.AddAction(&Step2Action);

    Step3.AddAction(&Step3Action);

    Step4.AddAction(&Step4Action);

    sequence.AddStep(&Step1);
    sequence.AddStep(&Step2);
    sequence.AddStep(&Step3);
    sequence.AddStep(&Step4);

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