#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#include <Messages.h>
#include <Wheels.h>
#include <Dress.h>

void setup()
{
    unsigned long time;

    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(45, OUTPUT);

    Servo center;
    center.attach(45);
    Dress dress(28);
    Wheels::init(3, 5, 12, 2, 4, 11);
    Wheels::write(87, 89);
    center.write(95);
    Serial3.begin(9600);

    Messages::wait_for('c');
    Wheels::write(110, 111);
    time = millis();
    while (millis() - time > 3000) {
        dress.blue();
    }
    Wheels::write(87, 89);

    while (!(Serial.available() && Serial.read() == 'd')) {
        dress.blue();
    } 
    center.write(104);
    time = millis();
    while (millis() - time > 3000) {
        dress.rainbow();
    }
    center.write(95);
    while (1) {
        dress.rainbow();
    }
}

void loop() {}