#include <Arduino.h>
#include "RabbitArm.h"

Arm::Arm(int pin) : pin(pin)
{
    motor.attach(10);
}

void Arm::move_start(int power)
{
    motor.write(power);
    prev = false;
    time = millis();
}

void Arm::move(int ms)
{
    if (!prev && millis() - time > ms) {
        prev = true;
        motor.write(80);
    }
}