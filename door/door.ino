#include <Servo.h>

#include <Messages.h>
#include <Ping.h>

void setup()
{
    Servo motor;
    motor.attach(10);
    motor.write(87);
    Ping ping(9);
    Serial.begin(9600);

    // Messages::wait_for(Messages::start);
    // while (ping.over(100)) {
    //     delay(100);
    // }
    // motor.write(140);
    // delay(7300);
    // motor.write(87);
    // Serial.print(Messages::door_change);

    // Messages::wait_for('z');
    // motor.write(40);
    // delay(7600);
    // motor.write(87);

    while (1) {
        while (ping.over(300)) {
            delay(100);
        }
        motor.write(140);
        delay(7300);
        motor.write(87);
        delay(1000);
        motor.write(40);
        delay(7600);
        motor.write(87);
    }

}

void loop() {}
