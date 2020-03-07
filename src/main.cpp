/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <mbed.h>
#include "Adafruit_DotStar.h"

constexpr int NUM_LEDS = 10;
DigitalOut led(PC_13);
Adafruit_DotStar strip(NUM_LEDS, PinName::PC_4, PinName::PC_5);

int main() {
    int      head  = 0, tail = -10; // Index of first 'on' and 'off' pixels
    uint32_t color = 0xFF0000;      // 'On' color (starts red)
    
    strip.begin(); // Initialize pins for output
    strip.show();  // Turn all LEDs off ASAP

    while(true) {
        led.write(0);
        strip.setPixelColor(head, color); // 'On' pixel at head
        strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
        strip.show();                     // Refresh strip
        thread_sleep_for(20);

        if(++head >= NUM_LEDS) {         // Increment head index.  Off end of strip?
            head = 0;                       //  Yes, reset head index to start
            if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
                color = 0xFF0000;             //   Yes, reset to red
        }
        
        if(++tail >= NUM_LEDS) tail = 0; // Increment, reset tail index
        led.write(1);
    }
}

// LED Strip Code
