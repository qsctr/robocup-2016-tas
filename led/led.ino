#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
#include <avr/pgmspace.h>

#include <Messages.h>

// converted from same file name pngs
#include "intro.h"
#include "roses_red.h"
#include "roses_white.h"

// change this when compiling for different arduino
#define PANEL 2
/* ________
  |0 |1 |2 | 
  |__|__|__| */

#define MESSAGE_PIN 42

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

#if PANEL == 2

#define PING_PIN 5

void setup()
{
    matrix.begin();
    draw_picture(intro);
    // pinMode(MESSAGE_PIN, OUTPUT);
    // // Serial3.begin(9600);
    // matrix.begin();
    // // Messages::wait_for(Messages::start);
    // draw_and_send(intro);
    // while (ping_cm() > 50) delay(100);
    // draw_and_send(roses_white);
    // delay(5000);
    // while (ping_cm() > 50) delay(100);
    // draw_and_send(roses_red);
}

void draw_and_send(const byte p[64][96][4])
{
    digitalWrite(MESSAGE_PIN, HIGH);
    draw_picture(p);
    delay(50);
    digitalWrite(MESSAGE_PIN, HIGH);
}

long ping_cm()
{
    pinMode(PING_PIN, OUTPUT);
    digitalWrite(PING_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(PING_PIN, HIGH);
    delayMicroseconds(5);
    digitalWrite(PING_PIN, LOW);
    pinMode(PING_PIN, INPUT);
    return pulseIn(PING_PIN, HIGH) / 29 / 2;
}

#else

void setup()
{
    pinMode(MESSAGE_PIN, INPUT);
    wait_to_draw(intro);
    wait_to_draw(roses_white);
    wait_to_draw(roses_red);
}

void wait_to_draw(const byte p[64][96][4])
{
    while (!digitalRead(MESSAGE_PIN));
    draw_picture(p);
    delay(100);
}

#endif

void loop() {}

void draw_picture(const byte p[64][96][4])
{
    for (int i = 0; i < 64; i++) {
        for (int j = 32 * PANEL; j < 32 * (PANEL + 1); j++) {
            matrix.drawPixel(j, i, matrix.Color333(
                pgm_read_byte(&(p[i][j][0])),
                pgm_read_byte(&(p[i][j][1])),
                pgm_read_byte(&(p[i][j][2]))));
        }
    }
}
