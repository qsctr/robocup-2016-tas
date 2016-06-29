#include <Arduino.h>
#include "Dress.h"

Dress::Dress(int pin)
{
    lights = Adafruit_NeoPixel(175, pin, NEO_GRB + NEO_KHZ800);
    lights.setBrightness(80);
    lights.begin();
    lights.show();
}

static const int blue_array[48] = {
    170, 30,  80,     205, 52,  152,
    50,  0,   80,     50,  30,  150, 
    70,  70,  150,    93,  136, 230,
    100, 149, 237,    0,   191, 255,
    65,  105, 225,    0,   0,   255,
    0,   0,   205,    0,   0,   128,
    138, 43,  226,    75,  0,   130,
    255, 0,   255,    255, 0,   100
};

void Dress::blue()
{
    static unsigned long time = millis();
    static int i = 0;

    if (millis() - time > 15) {
        if (i >= lights.numPixels()) {
            i = 0;
        }
        for (int p = i; p < lights.numPixels();) {
            for (int x = 0; x < 48; x += 3) {
                lights.setPixelColor(p, lights.Color(blue_array[x], blue_array[x + 1], blue_array[x + 2]));
                p++;
            }
        }
        for (int r = i; r >= 0;) {
            for (int x = 45; x >= -1; x -= 3) {
                lights.setPixelColor(r, lights.Color(blue_array[x], blue_array[x + 1], blue_array[x + 2]));
                r--;
            }
        }
        lights.show();
        i++;
        time = millis();
    }
}

uint32_t Wheel();

void Dress::rainbow()
{
    static unsigned long time = millis();
    static int j = 0, q = 0;
    static bool first_time = true;

    if (millis() - time > 50) {
        if (j >= 256) {
            j = 0;
        }
        if (q >= 3) {
            q = 0;
            j += 8;
        }
        if (first_time) {
            first_time = false;
        } else {
            for (uint16_t i = 0; i < lights.numPixels(); i += 3) {
                lights.setPixelColor(i + q, 0);
            }
            q++;
        }
        for (uint16_t i = 0; i < lights.numPixels(); i += 3) {
            lights.setPixelColor(i + q, Wheel((i + j) & 255));
        }
        lights.show();
        time = millis();
    }
    
    // Synchronous blocking version

    // for (int j = 0; j < 256; j+= 8) {
    //     for (int q = 0; q < 3; q++) {
    //         for (uint16_t i = 0; i < lights.numPixels(); i += 3) {
    //             lights.setPixelColor(i + q, Wheel((i + j) & 255));
    //         }
    //         lights.show();
    //         delay(50);
    //         for (uint16_t i = 0; i < lights.numPixels(); i += 3) {
    //             lights.setPixelColor(i + q, 0);
    //         }
    //     }
    // }
}

uint32_t Dress::Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return lights.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return lights.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return lights.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}