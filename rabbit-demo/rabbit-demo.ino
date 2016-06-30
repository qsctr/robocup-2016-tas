#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include <Messages.h>
#include <Wheels.h>
#include <Ping.h>
#include <AsyncServo.h>
#include <Pneumatic.h>
#include <CompassSensor.h>

void setup()
{
    const int
        forward = 120,
        backward = 60,
        stop = 90,
        arm_up = 30,
        arm_down = 100,
        claw_open = 160,
        claw_close = 70;

    Servo claw;
    Servo arm;
    Pneumatic jump(32);
    Ping ping(22);
    Compass compass(12345);

    Wheels::init(2, 4, 12, 3, 5, 11);
    claw.attach(46);
    arm.attach(10);
    jump.down();
    Serial3.begin(9600);

    while (1) {
        if (Serial3.available()) {
            switch (Serial3.read()) {
                case 'w':
                    Wheels::write(150, 130);
                    break;
                case 's':
                    Wheels::write(30, 50);
                    break;
                case 'a':
                    Wheels::write(stop, forward);
                    break;
                case 'd':
                    Wheels::write(forward, stop);
                    break;
                case ' ':
                    Wheels::write(stop);
                    break;
                case 'q':
                    Wheels::write(stop, forward);
                    Wheels::reset_encoder();
                    while (Wheels::avg_encoder() < 2200);
                    Wheels::write(stop);
                    break;
                case 'e':
                    Wheels::write(forward, stop);
                    Wheels::reset_encoder();
                    while (Wheels::avg_encoder() < 2200);
                    Wheels::write(stop);
                    break;
                case 'u':
                    arm.write(arm_up);
                    delay(2000);
                    arm.write(80);
                    break;
                case 'j':
                    arm.write(arm_down);
                    delay(1000);
                    arm.write(90);
                    break;
                case 'i':
                    jump.up();
                    break;
                case 'k':
                    jump.down();
                    break;
                case 'o':
                    claw.write(claw_open);
                    break;
                case 'p':
                    claw.write(claw_close);
                    break;
            }
        }
        Serial3.print("Ping distance (cm): ");
        Serial3.print(ping.cm());
        Serial3.print(" Compass (degrees from north): ");
        Serial3.print(compass.angle());
        Serial3.println();
        delay(100);
    }
}

void loop() {}