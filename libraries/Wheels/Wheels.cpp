#include <Arduino.h>
#include "Wheels.h"

void l_enc_cb();
void r_enc_cb();

Servo Wheels::left_motor, Wheels::right_motor;
volatile long Wheels::left_encoder_raw = 0, Wheels::right_encoder_raw = 0;
int Wheels::left_encoder_pin_a, Wheels::left_encoder_pin_b, Wheels::left_motor_pin,
    Wheels::right_encoder_pin_a, Wheels::right_encoder_pin_b, Wheels::right_motor_pin;

void Wheels::init(int l_enc_pin_a, int l_enc_pin_b, int l_mot_pin, int r_enc_pin_a, int r_enc_pin_b, int r_mot_pin)
{
    left_encoder_pin_a  = l_enc_pin_a;
    left_encoder_pin_b  = l_enc_pin_b;
    left_motor_pin      = l_mot_pin;
    right_encoder_pin_a = r_enc_pin_a;
    right_encoder_pin_b = r_enc_pin_b;
    right_motor_pin     = r_mot_pin;

    pinMode(left_encoder_pin_b, INPUT);
    pinMode(right_encoder_pin_b, INPUT);
    left_motor.attach(left_motor_pin);
    right_motor.attach(right_motor_pin);
    attachInterrupt(digitalPinToInterrupt(left_encoder_pin_a), l_enc_cb, RISING);
    attachInterrupt(digitalPinToInterrupt(right_encoder_pin_a), r_enc_cb, RISING);
}

void Wheels::write(int power)
{
    write(power, power);
}

void Wheels::write(int l_power, int r_power)
{
    left_motor.write(l_power);
    right_motor.write(r_power);
}

long Wheels::avg_encoder()
{
    return (abs(left_encoder_raw) + abs(right_encoder_raw)) / 2;
}

void l_enc_cb()
{
    if (digitalRead(Wheels::left_encoder_pin_b))
        Wheels::left_encoder_raw++; 
    else
        Wheels::left_encoder_raw--;
}

void r_enc_cb()
{
    if (digitalRead(Wheels::right_encoder_pin_b))
        Wheels::right_encoder_raw++;
    else
        Wheels::right_encoder_raw--;
}