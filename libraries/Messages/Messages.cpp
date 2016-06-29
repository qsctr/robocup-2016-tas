#include <Arduino.h>
#include "Messages.h"

namespace Messages
{
    void wait_for(char message)
    {
        #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
            #define SER Serial3
        #else
            #define SER Serial
        #endif
        while (!(SER.available() && SER.read() == message));
    }
}