#include <Servo.h>

#include <Wheels.h>
#include <Ping.h>
#include <Pneumatic.h>
#include <SuperMessages.h>

void setup()
{
    Servo arm;
    arm.attach(10);
    Pneumatic jump(32);
    Ping ping(22);
    Wheels::init(2, 4, 12, 3, 5, 11);
    Wheels::write(90);
    Serial3.begin(9600);
    pinMode(42, INPUT_PULLUP);

    while (digitalRead(42));

    while (1) {
        if (ping.cm() < 20) {
            delay(300);
            if (ping.cm() < 20) {
                delay(1000);
                Wheels::write(149, 150);
                while (ping.cm() > 50) {
                    delay(100);
                }
                Wheels::write(90);
            }
        }
        if (Serial3.available() && Serial3.read() == relay_complete) {
            arm.write(30);
            jump.up();
            delay(1000);
            jump.down();
            arm.write(90);
        }
        delay(100);
    }
}

void loop() {}