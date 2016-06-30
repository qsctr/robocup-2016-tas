#ifndef ASYNC_SERVO_H
#define ASYNC_SERVO_H

#include <Arduino.h>
#include <Servo.h>

struct AsyncServo
{
    AsyncServo(int pin, int stay_power);
    void move_start(int power);
    void move(int ms);
    void move_cond(bool cond);
    Servo motor;
    unsigned long time;
    bool prev;
    int stay_power;
};

#endif