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
        forward = 120,
        backward = 60,
        stop = 90,
        right_arm_up = 108,
        right_arm_down = 78,
        elbow_up = 150,
        elbow_down = 70,
        claw_open = 160,
        claw_close = 70,
        center_up = 80,
        center_down = 100;

    unsigned long time;

    Servo right_arm;
    Servo elbow;
    Servo center;
    Servo claw;
    Ping height(8);
    Ping distance(7);
    Dress dress(28);

    Wheels::init(3, 5, 12, 2, 4, 11);
    Wheels::write(stop);
    right_arm.attach(44);
    elbow.attach(10);
    center.attach(45);
    claw.attach(46);
    Serial3.begin(9600);
    center.write(93);
    claw.write(claw_open);

    Wheels::write(87, 89);
    
    Messages::wait_for(Messages::door_change);

    Wheels::write(forward);
    
    while (Wheels::avg_encoder() < 1500) {
        dress.blue();
    }   

    Wheels::write(stop);

    Wheels::write(backward, forward);
    Wheels::reset_encoder();

    while (Wheels::avg_encoder() < 655) {
        dress.blue();
    }

    Wheels::write(stop);

    // Wheels::write(forward);
    // center.move_start(center_down);
    // elbow.move_start(elbow_up);

    // while (Wheels::avg_encoder() < 2000) {
    //     dress.blue();
    //     center.move_cond(!height.over(35));
    //     elbow.move(800);
    // }

    // Wheels::write(87, 89);

    // // Wheels::write(stop);
    // // claw.write(claw_close);
    // // time = millis();
    
    // // while (millis() - time < 500) {
    // //     dress.blue();
    // // }

    // // Wheels::write(backward);
    // // center.move_start(center_up);

    // // while (!(distance.over(50))) {
    // //     dress.blue();
    // //     center.move_cond(height.over(50));
    // // }

    // // Wheels::write(forward, backward);
    // // compass.record();

    // // while (!compass.near(90)) {
    // //     dress.blue();
    // //     center.move_cond(height.over(50));
    // // }

    // // Wheels::write(forward);

    // // while (Wheels::avg_encoder() < 5000) {
    // //     dress.blue();
    // // }

    // // Wheels::write(stop);

    // // elbow.motor.write(30);
    // // right_arm.move_start(right_arm_up);
    // // time = millis();

    // // while (millis() - time < 500) {
    // //     dress.blue();
    // //     right_arm.move(300);
    // // }

    // // elbow.motor.write(80);
    // // center.motor.write(center_down);

    // // while (height.over(35)) {
    // //     dress.rainbow();
    // // }

    // // center.motor.write(95);

    // // while (true) {
    // //     dress.rainbow();
    // // }

    // Wheels::write(forward);
    // Wheels::reset_encoder();
    // while (Wheels::avg_encoder() < 6000) {
    //     dress.blue();
    // }
    // elbow.motor.write(30);
    // right_arm.move_start(right_arm_up);
    // time = millis();

    // while (millis() - time < 1000) {
    //     dress.blue();
    //     right_arm.move(300);
    // }

    // elbow.motor.write(80);
    // center.motor.write(center_down);

    // while (height.over(35)) {
    //     dress.rainbow();
    // }

    // center.motor.write(95);

    // while (true) {
    //     dress.rainbow();
    // }

}

void loop() {}