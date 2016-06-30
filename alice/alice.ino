#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_NeoPixel.h>

#include <Messages.h>
#include <Wheels.h>
#include <Ping.h>
#include <AsyncServo.h>
#include <CompassSensor.h>
#include <Dress.h>

void setup()
{
    const int
        forward  = 120,
        backward = 60,
        stop     = 90;

    Compass compass(12345);
    // Dress dress(43);
    Wheels::init(3, 5, 13, 2, 4, 12);
    Serial3.begin(9600);
    
    Messages::wait_for(Messages::start);
    Serial3.println(Messages::start);
    delay(2000);
    // Wheels::write(forward, backward);
    compass.record();
    while (!compass.near(90));
    // Wheels::write(stop);
}

void loop() {}