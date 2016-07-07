#include <Adafruit_GFX.h>
#include <RGBmatrixPanel.h>
#include <avr/pgmspace.h>

#include <SuperMessages.h>

// change this when compiling for different arduino
#define PANEL 0
/* ________
  |0 |1 |2 | 
  |__|__|__| */

#if PANEL == 0
#include "led0.h"
#elif PANEL == 1
#include "led1.h"
#elif PANEL == 2
#include "led2.h"
#endif

#define MESSAGE_PIN 42

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

#if PANEL == 0

void setup()
{
    pinMode(MESSAGE_PIN, OUTPUT);
    Serial3.begin(9600);
    matrix.begin();
    draw_picture(led);
    while (1) {
        if (Serial3.available() && Serial3.read() == relay_complete) {
            digitalWrite(MESSAGE_PIN, HIGH);
            delay(50);
            digitalWrite(MESSAGE_PIN, LOW);
            flash();
        }
    }
}

#else

void setup()
{
    pinMode(MESSAGE_PIN, INPUT);
    matrix.begin();
    draw_picture(led);
    while (1) {
        if (digitalRead(MESSAGE_PIN)) {
            flash();
        }
    }
}

#endif

void loop() {}

void flash()
{
    for (int i = 0; i < 2; i++) {
        matrix.fillScreen(matrix.Color333(7, 7, 7));
        delay(1000);
        draw_picture(led);
        delay(1000);
    }
}

void draw_picture(const byte p[64][32][3])
{
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 32; j++) {
            matrix.drawPixel(i, 31 - j, matrix.Color333(
                pgm_read_byte(&(p[i][j][0])),
                pgm_read_byte(&(p[i][j][1])),
                pgm_read_byte(&(p[i][j][2]))));
        }
    }
}
