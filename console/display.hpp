#pragma once

#include "frame.hpp"

#define SCLK_PIN 2
#define MOSI_PIN 3
#define DC_PIN 4
#define CS_PIN 5
#define RESET_PIN 6

class Display
{
    private:
        static constexpr unsigned char display_init_sequence[26] = {
            0xAE,       // Display off
            0xD5, 0x80, // Display Clock Div
            0xA8, 0x3F, // Multiplex
            0xD3, 0x00, // Display offset
            0x40,       // Display start line -- line #0
            0x8D, 0x14, // Enable charge pump
            0x20, 0x00, // Horizontal addressing mode
            0xA1,       // Segment remap -- 0xA0 - column 0 -> SEG0 / 0xA1 - column 127 -> SEG0
            0xC8,       // COM Output scan direction
            0xDA, 0x12, // COM pins
            0x81, 0xCF, // Contrast
            0xD9, 0xF1, // Pre-charge period
            0xDB, 0x40, // VCOMH Deselect Level -- idk datasheet only has 0x10, 0x20, 0x30
            0xA4,       // Display uses RAM content
            0xA6,       // Normal display (0 in RAM is OFF pixel)
            0x2E,       // Deactivate scroll
            0xAF        // Display on as fuck
        };

        void send_command(unsigned char cmd);
        void reset();
        void init();

    public:
        Display();
        ~Display();

        void update(Frame *buffer);
};