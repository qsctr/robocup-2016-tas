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
        start_button = 42,
        forward_l    = 130,
        forward_r    = 110,
        backward_l   = 50,
        backward_r   = 70,
        stop         = 90,
        claw_open    = 160,
        claw_close   = 70;

    Servo claw;
    AsyncServo arm(10, 80);
    Pneumatic jump(32);
    Ping ping(22);
    Compass compass(12345);

    pinMode(start_button, INPUT_PULLUP);
    Wheels::init(2, 4, 12, 3, 5, 11);
    Wheels::write(90);
    claw.attach(46);
    jump.down();
    Serial3.begin(9600);

    while (digitalRead(start_button));

    Serial3.print(Messages::start);
    Serial3.print(Messages::start);
    Serial3.print(Messages::start);

    delay(2000);

    Wheels::write(forward_r, forward_r);
    arm.motor.write(50);
    claw.write(claw_open);
    jump.up_and_down_start();

    while (ping.over(15)) {
        jump.up_and_down();
        delay(100);
    }

    jump.down();
    arm.motor.write(80);
    Wheels::write(stop);

    delay(3000);

    claw.write(claw_close);

    delay(3000);

    Wheels::write(stop, forward_r);
    Wheels::reset_encoder();

    while (Wheels::avg_encoder() < 4580);

    Wheels::write(stop);

    delay(500);

    Wheels::write(forward_r, forward_r);

    while (ping.over(40)) {
        delay(100);
    }

    arm.motor.write(40);

    while (ping.over(6)) {
        delay(100);
    }

    arm.motor.write(80);

    Wheels::write(stop);
    claw.write(claw_open);

    delay(500);

    Wheels::write(backward_r);

    while (ping.cm() < 50) {
        delay(100);
    }

    Wheels::write(stop);
    arm.motor.write(100);

    delay(500);

    arm.motor.write(90);
}

void loop() {}
