#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

#include <Messages.h>
#include <Wheels.h>
#include <Ping.h>
#include <RabbitArm.h>
#include <Pneumatic.h>
#include <CompassSensor.h>

void setup()
{
    const int start_button = 24;
    
    pinMode(start_button, INPUT);
    Wheels::init(2, 4, 42, 3, 5, 43);
    Arm arm(10);
    Servo claw;
    claw.attach(48);
    Pneumatic jump(32);
    jump.down();
    Ping ping(22);
    Compass compass(12345);
    Serial3.begin(9600);

    while (!digitalRead(start_button));
    // Messages::wait_for(Messages::start);

    Serial3.print(Messages::start);

    delay(2000);

    Wheels::write(left_forward, right_forward);
    arm.move_start(30);
    claw.write(160);
    jump.up_and_down_start();

    while (ping.over(30)) {
        arm.move(1000);
        jump.up_and_down();
    }

    jump.down();
    Wheels::write(90);

    delay(1000);

    claw.write(70);

    delay(500);

    turn_right_90();

    forward(5000);

    turn_right_90();

    forward(10000);

    turn_right(90);

    

}

void forward(int enc)
{
    Wheels::write(150, 130);
    while (Wheels::avg_encoder() < enc);
}

void turn_right_90()
{
    compass.record();
    Wheels::write(130, 50);
    do {
        delay(200);
    } while (!(Wheels::avg_encoder() > 200 && compass.near(90)));
}

void loop() {}
