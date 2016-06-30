#include <Arduino.h>
#include "AsyncServo.h"

AsyncServo::AsyncServo(int pin, int stay_power) : stay_power(stay_power)
{
    motor.attach(pin);
}

void AsyncServo::move_start(int power)
{
    motor.write(power);
    prev = false;
    time = millis();
}

void AsyncServo::move(int ms)
{
    move_cond(millis() - time > ms);
}

void AsyncServo::move_cond(bool cond)
{
    Serial3.println(motor.read());
    if (!prev && cond) {
        prev = true;
        motor.write(stay_power);
    }
}