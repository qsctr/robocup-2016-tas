#ifndef MESSAGES_H
#define MESSAGES_H

#include <Arduino.h>

namespace Messages
{
    const char start = 'a', door_change = 'b';
    void wait_for(char message);
};

#endif