#pragma once

#include "hardware/timer.h"
#include "pico/multicore.h"

#include "buttons.hpp"
#include "display.hpp"
#include "led.hpp"

namespace Console
{
    #define REFRESH_RATE_US 5000

    namespace reserved
    {
        void looping_callback(uint alarm_id)
        {
            uint current_time = time_us_32();
            hardware_alarm_set_target(alarm_id, current_time + REFRESH_RATE_US);

            Buttons::reserved::update_buttons(current_time);
            Led::reserved::update_led(current_time);
        }

        void actual_init()
        {
            Led::init();
            Buttons::init();

            hardware_alarm_claim(3);
            hardware_alarm_set_callback(3, looping_callback);
            hardware_alarm_set_target(3, time_us_32() + 100000);
        }
    }

    void initialize_console_all()
    {
        multicore_reset_core1();
        multicore_launch_core1(reserved::actual_init);
    }
}