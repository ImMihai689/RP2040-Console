#pragma once
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <pico/time.h>

namespace Console::Led
{
    #define LED 12

    namespace reserved
    {
        int alarm_id = -1;

        long long led_off_callback(alarm_id_t id, void *user_data)
        {
            pwm_set_gpio_level(LED, 0);
            if(user_data != nullptr)
                ((void (*)(void))user_data)();
            alarm_id = -1;
            return 0;
        }
    }

    /// @brief Initialize the onboard LED
    void init()
    {
        gpio_set_function(LED, GPIO_FUNC_PWM);
        uint slice_num = pwm_gpio_to_slice_num(LED);
        pwm_set_wrap(slice_num, 100);
        pwm_set_clkdiv(slice_num, 16.f);
        pwm_set_enabled(slice_num, true);
        pwm_set_gpio_level(LED, 0);
    }

    /// @brief Set the onboard LED to the given value
    /// @param val The percent ([0, 100]) to set the LED to
    void set(int val)
    {
        if(val < 0)
            pwm_set_gpio_level(LED, 0);
        else if(val > 100)
            pwm_set_gpio_level(LED, 100);
        else
            pwm_set_gpio_level(LED, val);
    }

    /// @brief Set the onboard LED to the given value for given milliseconds
    /// @param val The percent ([0, 100]) to set the LED to
    /// @param ms For how many milliseconds the LED will be on, after which the LED turns off (0%)
    void set(int val, int ms)
    {
        if(ms < 0)
            ms = -ms;
        
        if(reserved::alarm_id != -1)
            if(!cancel_alarm(reserved::alarm_id))
                printf("Warning: Tried to cancel alarm that didn't exist! (led.hpp)\n");

        int id = add_alarm_in_ms(ms, reserved::led_off_callback, nullptr, false);

        reserved::alarm_id = id;

        if(id >= 0)
        {
            if(val < 0)
                pwm_set_gpio_level(LED, 0);
            else if(val > 100)
                pwm_set_gpio_level(LED, 100);
            else
                pwm_set_gpio_level(LED, val);
        }
        else
            printf("Warning: No available alarms for onboard LED! (led.hpp)\n");
    }

    /// @brief Set the onboard LED to the given value for given milliseconds
    /// @param val The percent ([0, 100]) to set the LED to
    /// @param ms For how many milliseconds the LED will be on, after which the LED turns off (0%)
    /// @param callback This function will be called after the time is up
    void set(int val, int ms, void callback())
    {
        if(ms < 0)
            ms = -ms;
        
        if(reserved::alarm_id != -1)
            if(!cancel_alarm(reserved::alarm_id))
                printf("Warning: Tried to cancel alarm that didn't exist! (led.hpp)\n");

        int id = add_alarm_in_ms(ms, reserved::led_off_callback, (void *)callback, false);

        reserved::alarm_id = id;

        if(id >= 0)
        {
            if(val < 0)
                pwm_set_gpio_level(LED, 0);
            else if(val > 100)
                pwm_set_gpio_level(LED, 100);
            else
                pwm_set_gpio_level(LED, val);
        }
        else
            printf("Warning: No available alarms for onboard LED! (led.hpp)");
    }
}