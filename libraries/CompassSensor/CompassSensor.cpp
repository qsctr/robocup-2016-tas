#include <Arduino.h>
#include "CompassSensor.h"

static bool deg_gteq(float a, float b, float diff);

Compass::Compass(int id)
{
    sensor = Adafruit_HMC5883_Unified(id);
    if (!sensor.begin()) {
        Serial3.println("Error initializing compass sensor");
    }
}

void Compass::record()
{
    start_angle = prev = angle();
}

bool Compass::near(float deg)
{
    float curr = angle();
    Serial3.println(curr);
    float abs_deg = start_angle + deg;
    if (abs_deg > 360) {
        abs_deg -= 360;
    }
    if (abs_deg < 0) {
        abs_deg += 360;
    }
    float diff;
    if (deg_gteq(curr, prev, 0)) {
        if (prev >= 180) {
            if (curr >= prev) {
                diff = curr - prev;
            } else {
                diff = curr + 360 - prev;
            }
        } else {
            diff = curr - prev;
        }
        float temp_prev = prev;
        prev = curr;
        return !deg_gteq(temp_prev, abs_deg, diff) && deg_gteq(curr, abs_deg, diff);
    } else {
        if (curr >= 180) {
            if (prev >= curr) {
                diff = prev - curr;
            } else {
                diff = prev + 360 - curr;
            }
        } else {
            diff = prev - curr;
        }
        float temp_prev = prev;
        prev = curr;
        return deg_gteq(temp_prev, abs_deg, diff) && !deg_gteq(curr, abs_deg, diff);
    }
}

static bool deg_gteq(float a, float b, float diff)
{
    if (b >= 180) {
        return a >= (b - diff / 2) || a < b - 180;
    } else {
        b -= diff / 2;
        if (b < 0)
            b += 360;
        return a >= b && a < b + 180;
    }
}

float Compass::angle()
{
    sensors_event_t event;
    sensor.getEvent(&event);
    float rad = atan2(event.magnetic.y, event.magnetic.x);
    if (rad < 0) rad += TWO_PI;
    return degrees(rad);
}
