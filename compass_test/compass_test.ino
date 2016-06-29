#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include <CompassSensor.h>

void setup()
{
    Serial.begin(9600);
    Compass compass(12345);
    delay(1000);
    compass.record();
    while (!compass.near(-90)) {
        delay(1);
    }
}

void loop() {}