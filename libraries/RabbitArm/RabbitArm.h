#ifndef RABBIT_ARM_H
#define RABBIT_ARM_H

#include <Arduino.h>
#include <Servo.h>

struct Arm
{
    Arm(int pin);
    void move_start(int power);
    void move(int ms);
    void move_sync(int power);
    Servo motor;
    unsigned long time;
    bool prev;
    int pin;
};

#endif