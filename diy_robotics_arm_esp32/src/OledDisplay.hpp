#ifndef OledDisplay_HPP_
#define OledDisplay_HPP_

#include <Arduino.h>
#include <Wire.h>
#include "SSD1306Wire.h"

class OledDisplay {
private:
    SSD1306Wire display;

public:
    OledDisplay(int address = 0x3c, int sda = SDA, int scl = SCL) : display(address, sda, scl) {
        // Initialize the display
        display.init();
        display.flipScreenVertically();
    };

    ~OledDisplay() {}

    void DrawDisplay(String text) {
        // Clear the display
        display.clear();

        // Text
        display.setTextAlignment(TEXT_ALIGN_LEFT);
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 0, text);

        // Write buffer to the display
        display.display();
    }
};

#endif
