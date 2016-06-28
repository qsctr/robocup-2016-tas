#ifndef PNEUMATIC_H
#define PNEUMATIC_H

#include <Arduino.h>

struct Pneumatic
{
    Pneumatic(int pin);
    void up_and_down_start();
    void up_and_down();
    void up();
    void down();
    unsigned long time;
    int pin;
};

#endif