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
        forward      = 130,
        backward     = 50,
        stop         = 90,
        arm_up       = 60,
        arm_down     = 110,
        claw_open    = 160,
        claw_close   = 70;

    Servo claw;
    AsyncServo arm(10, 80);
    Pneumatic jump(32);
    Ping ping(22);
    Compass compass(12345);

    pinMode(start_button, INPUT_PULLUP);
    Wheels::init(2, 4, 12, 3, 5, 11);
    claw.attach(46);
    jump.down();
    Serial3.begin(9600);

    while (digitalRead(start_button));

    Serial3.print(Messages::start);

    delay(2000);

    // Wheels::write(150, 130);
    // arm.move_start(arm_up);
    // claw.write(claw_open);
    // jump.up_and_down_start();

    // while (ping.over(15)) {
    //     arm.move(400);
    //     jump.up_and_down();
    // }

    // jump.down();
    // Wheels::write(stop);

    // delay(3000);

    // claw.write(claw_close);

    // delay(1000);

    // Wheels::write(150, 30);
    // Wheels::reset_encoder();

    // while (Wheels::avg_encoder() < 4000);

    // Wheels::write(150, 130);

    // Wheels::reset_encoder();
    // while (Wheels::avg_encoder() < 6000);

    // Wheels::write(150, 50);
    // Wheels::reset_encoder();

    // while (Wheels::avg_encoder() < 4000);

    // Wheels::write(forward);

    // while (ping.over(20));

    // Wheels::write(stop);
    // claw.write(claw_open);

    // delay(500);

    // Wheels::write(backward);

    // while (!ping.over(50));

    // Wheels::write(stop);
    // arm.motor.write(arm_down);

    // delay(500);

    // arm.motor.write(90);

    Wheels::write(150, 30);
    Wheels::reset_encoder();
    while (Wheels::avg_encoder() < 4500);
    Wheels::write(stop);
}

void loop() {}
