#ifndef WHEELS_H
#define WHEELS_H

#include <Arduino.h>
#include <Servo.h>

struct Wheels
{
    static void init(int l_enc_pin_a, int l_enc_pin_b, int l_mot_pin, int r_enc_pin_a, int r_enc_pin_b, int r_mot_pin);
    static void delay_encoder(int x);
    static void write(int power);
    static void write(int l_power, int r_power);
    static long avg_encoder();
    static Servo left_motor, right_motor;
    static volatile long left_encoder_raw, right_encoder_raw;
    static int left_encoder_pin_a, left_encoder_pin_b, left_motor_pin,
        right_encoder_pin_a, right_encoder_pin_b, right_motor_pin;
};

#endif