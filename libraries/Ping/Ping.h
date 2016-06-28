#ifndef PING_H
#define PING_H

#include <Arduino.h>

struct Ping
{
    Ping(int pin);
    bool over(long x);
    long cm();
    int pin;
};

#endif