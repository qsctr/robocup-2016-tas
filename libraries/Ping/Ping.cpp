#include <Arduino.h>
#include "Ping.h"

Ping::Ping(int pin) : pin(pin) {}

bool Ping::over(long x)
{
    long y = cm();
    return y > x || y <= 0;
}

long Ping::cm()
{
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    return pulseIn(pin, HIGH) / 29 / 2;
}