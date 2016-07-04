#include <SuperMessages.h>
#include <Ping.h>

void setup()
{
    Serial3.begin(9600);
    Ping ping(6);
    long prev, curr;
    while (1) {
        curr = ping.cm();
        if (curr < 300 && prev >= 300) {
            Serial3.print(relay_complete);
            delay(2000);
        }
        prev = curr;
        delay(100);
    }
}

void loop() {}