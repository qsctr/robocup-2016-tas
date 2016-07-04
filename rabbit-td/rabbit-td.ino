#include <Servo.h>

#include <Wheels.h>
#include <Pneumatic.h>

void setup()
{
    Servo claw;
    Servo arm;
    Pneumatic jump(32);
    Wheels::init(2, 4, 12, 3, 5, 11);
    Wheels::write(90);
    claw.attach(10);
    arm.attach(10);
    jump.down();
    Serial3.begin(9600);
    unsigned long time;

    while (1) {
        if (Serial3.available()) {
            switch (Serial3.read()) {
                case 'a':
                    Wheels::write(150, 130);
                    for (int i = 0; i < 3; i++) {
                        jump.up();
                        delay(500);
                        jump.down();
                        delay(500);
                    }
                    Wheels::write(90);
                    break;
                case 'b':
                    arm.write(30);
                    delay(400);
                    arm.write(80);
                    delay(500);
                    claw.write(160);
                    delay(3000);
                    claw.write(70);
                    delay(500);
                    arm.write(90);
                    break;
            }
        }
    }
}

void loop() {}