#ifndef DRESS_H
#define DRESS_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

struct Dress
{
    Dress(int pin);
    Adafruit_NeoPixel lights;
    void blue();
    void blue_sync();
    void rainbow();
    void rainbow_sync();

    private:
        uint32_t Wheel(byte WheelPos);
};

#endif