#include <Arduino.h>
#include "Pneumatic.h"

Pneumatic::Pneumatic(int pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
}

void Pneumatic::up_and_down_start()
{
    time = millis();
}

void Pneumatic::up_and_down()
{
    unsigned long curr = millis();
    if (curr - time > 1000) {
        down();
        up_and_down_start();
    } else if (curr - time > 500) {
        up();
    }
}

void Pneumatic::up()
{
    digitalWrite(pin, HIGH);
}

void Pneumatic::down()
{
    digitalWrite(pin, LOW);
}