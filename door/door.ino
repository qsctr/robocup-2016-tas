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
    // while (ping.over(50));
    // motor.write(140);
    // delay(6300);
    // motor.write(87);
    // Serial.print(Messages::door_change);

    Messages::wait_for('z');
    motor.write(40);
    delay(6300);
    motor.write(87);
}

void loop() {}
