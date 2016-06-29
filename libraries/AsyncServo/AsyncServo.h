#ifndef ASYNC_SERVO_H
#define ASYNC_SERVO_H

#include <Arduino.h>
#include <Servo.h>

struct AsyncServo
{
    AsyncServo(int pin);
    void move_start(int power);
    void move(int ms);
    Servo motor;
    unsigned long time;
    bool prev;
    int stay_power;
};

#endif