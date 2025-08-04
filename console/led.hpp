#pragma once
#include <hardware/gpio.h>
#include <hardware/pwm.h>
#include <pico/time.h>

/// @brief The Console::Led namespace is made to be able to interface with the
///        onboard LED intuitively
/// @attention The Console::Led namespace uses alarm 3 of the RP2040
namespace Console::Led
{
    #define LED 12

    namespace reserved
    {
        const uint alarm_num = 3;
        void (*user_callback)();

        void led_off_callback(__unused uint alarm_id)
        {
            pwm_set_gpio_level(LED, 0);
            if(user_callback != nullptr)
            {
                ((void (*)(void))user_callback)();
                user_callback = nullptr;
            }
        }

        void update_led(uint time)
        {
            
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

        hardware_alarm_claim(reserved::alarm_num);
        hardware_alarm_set_callback(reserved::alarm_num, reserved::led_off_callback);
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
        
        if(reserved::user_callback != nullptr)
            reserved::user_callback();
        
        hardware_alarm_set_target(reserved::alarm_num, time_us_32() + ms * 1000);
        

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
    /// @param callback This function will be called after the time is up
    void set(int val, int ms, void callback())
    {
        if(ms < 0)
            ms = -ms;

        if(reserved::user_callback != nullptr)
            reserved::user_callback();
        reserved::user_callback = callback;

        hardware_alarm_set_target(reserved::alarm_num, time_us_32() + ms * 1000);

        if(val < 0)
            pwm_set_gpio_level(LED, 0);
        else if(val > 100)
            pwm_set_gpio_level(LED, 100);
        else
            pwm_set_gpio_level(LED, val);
    
    }
}