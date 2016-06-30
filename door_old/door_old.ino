#include <Messages.h>

void setup()
{
    const int button = 42,
        door_left = 32,
        door_right = 33;
    pinMode(Pins::button, INPUT);
    pinMode(Pins::door_left, OUTPUT);
    pinMode(Pins::door_right, OUTPUT);
    digitalWrite(door_left, HIGH);
    Serial.begin(9600);
    Messages::wait_for(Messages::start);
    while (!digitalRead(button));
    digitalWrite(door_left, LOW);
    digitalWrite(door_right, HIGH);
}