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
        forward = 150,
        backward = 30,
        stop = 90,
        right_arm_up = 108,
        right_arm_down = 78,
        elbow_up = 150,
        elbow_down = 70,
        claw_open = 70,
        claw_close = 0,
        center_up = 75,
        center_down = 100;

    Servo right_arm;
    Servo elbow;
    Servo claw;
    Servo center;
    Ping height(8);
    Ping distance(9);
    Dress dress(43);

    Wheels::init(3, 5, 13, 2, 4, 12);
    right_arm.attach(14);
    elbow.attach(11);
    claw.attach(46);
    Serial3.begin(9600);
    
    bool rainbow = false;
    while (1) {
        long h = height.cm();
        if (Serial3.available()) {
            switch (Serial3.read()) {
                case 'w':
                    Wheels::write(forward);
                    break;
                case 's':
                    Wheels::write(backward);
                    break;
                case 'a':
                    Wheels::write(backward, forward);
                    break;
                case 'd':
                    Wheels::write(forward, backward);
                case ' ':
                    Wheels::write(stop);
                    break;
                case 'q':
                    Wheels::write(backward, forward);
                    compass.record();
                    while (!compass.near(-90));
                    Wheels::write(stop);
                    break;
                case 'e':
                    Wheels::write(forward, backward);
                    compass.record();
                    while (!compass.near(90));
                    Wheels::write(stop);
                    break;
                case 'r':
                    right_arm.write(right_arm_up);
                    break;
                case 'f':
                    right_arm.write(93);
                    break;
                case 'v':
                    right_arm.write(right_arm_down);
                    break;
                case 't':
                    elbow.write(elbow_up);
                    delay(700);
                    elbow.write(100);
                    break;
                case 'g':
                    elbow.write(90);
                    break;
                case 'b':
                    elbow.write(70);
                    delay(700);
                    elbow.write(90);
                    break;
                case 'y':
                    center.write(h < 55 ? center_up : 95);
                    break;
                case 'h':
                    center.write(95);
                    break;
                case 'n':
                    center.write(h > 30 ? center_down : 95);
                    break;
                case 'o':
                    claw.write(claw_open);
                    break;
                case 'p':
                    claw.write(claw_close);
                    break;
                case 'i':
                    rainbow = false;
                    break;
                case 'k':
                    rainbow = true;
                    break;
            }
        }
        Serial.print("Ping height (cm): ");
        Serial3.println(h);
        Serial.print("Ping distance (cm): ");
        Serial3.println(distance.cm());
        if (rainbow) {
            dress.rainbow();
        } else {
            dress.blue();
        }
        delay(15);
    }
}