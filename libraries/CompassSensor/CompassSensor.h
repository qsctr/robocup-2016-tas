#ifndef COMPASS_SENSOR_H
#define COMPASS_SENSOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

struct Compass
{
    Compass(int id);
    void record();
    bool near(float deg);
    float angle();
    Adafruit_HMC5883_Unified sensor;
    float start_angle, prev;
};

#endif
