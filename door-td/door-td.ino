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

    Messages::wait_for('a');
    while (ping.over(50)) {
        delay(100);
    }
    motor.write(140);
    delay(7300);
    motor.write(87);
    Serial.print('c');
}

void loop() {}