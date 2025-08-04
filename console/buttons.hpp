#pragma once

namespace Console::Buttons
{
    enum buttons_t {
        BUT_A = 0,
        BUT_B = 1,
        BUT_1 = 10,
        BUT_2 = 11,
        BUT_3 = 9,
        BUT_4 = 8,
    };

    const int debounce_ms = 80;

    namespace reserved
    {
        void (* callback_A_fall)() = nullptr;
        void (* callback_B_fall)() = nullptr;
        void (* callback_1_fall)() = nullptr;
        void (* callback_2_fall)() = nullptr;
        void (* callback_3_fall)() = nullptr;
        void (* callback_4_fall)() = nullptr;

        void (* callback_A_rise)() = nullptr;
        void (* callback_B_rise)() = nullptr;
        void (* callback_1_rise)() = nullptr;
        void (* callback_2_rise)() = nullptr;
        void (* callback_3_rise)() = nullptr;
        void (* callback_4_rise)() = nullptr;

        uint last_check[6] = {0};

        unsigned int micros()
        {
            return get_absolute_time();
        }

        void init_gpio(uint gpio)
        {
            gpio_init(gpio);
            gpio_set_dir(gpio, false);
            gpio_set_pulls(gpio, true, false);
        }

        void reset_callbacks()
        {
            callback_1_fall = nullptr;
            callback_2_fall = nullptr;
            callback_3_fall = nullptr;
            callback_4_fall = nullptr;
            callback_A_fall = nullptr;
            callback_B_fall = nullptr;
            callback_1_rise = nullptr;
            callback_2_rise = nullptr;
            callback_3_rise = nullptr;
            callback_4_rise = nullptr;
            callback_A_rise = nullptr;
            callback_B_rise = nullptr;
        }

        void gpio_irq(uint gpio, uint32_t event_mask)
        {
            switch(gpio)
            {
                case BUT_A:
                    if(last_check[0] + debounce_ms < micros())
                    {
                        last_check[0] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_A_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_A_fall();
                    }
                    break;
                case BUT_B:
                    if(last_check[1] + debounce_ms < micros())
                    {
                        last_check[1] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_B_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_B_fall();
                    }
                    break;
                case BUT_1:
                    if(last_check[2] + debounce_ms < micros())
                    {
                        last_check[2] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_1_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_1_fall();
                    }
                    break;
                case BUT_2:
                    if(last_check[3] + debounce_ms < micros())
                    {
                        last_check[3] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_2_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_2_fall();
                    }
                    break;
                case BUT_3:
                    if(last_check[4] + debounce_ms < micros())
                    {
                        last_check[4] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_3_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_3_fall();
                    }
                    break;
                case BUT_4:
                    if(last_check[5] + debounce_ms < micros())
                    {
                        last_check[5] = micros();
                        if(event_mask & GPIO_IRQ_EDGE_RISE)
                            callback_4_rise();
                        else if(event_mask & GPIO_IRQ_EDGE_FALL)
                            callback_4_fall();
                    }
                    break;

            }
        }
    }

    /// @brief Initialize buttons for input
    void init()
    {
        reserved::init_gpio(BUT_A);
        reserved::init_gpio(BUT_B);
        reserved::init_gpio(BUT_1);
        reserved::init_gpio(BUT_2);
        reserved::init_gpio(BUT_3);
        reserved::init_gpio(BUT_4);

        gpio_set_irq_callback(reserved::gpio_irq);
        gpio_set_irq_enabled(BUT_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        gpio_set_irq_enabled(BUT_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        gpio_set_irq_enabled(BUT_1, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        gpio_set_irq_enabled(BUT_2, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        gpio_set_irq_enabled(BUT_3, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
        gpio_set_irq_enabled(BUT_4, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true);
    }

    /// @brief Subscribe to a button, rising or falling 
    /// @param button Which button to subscribe to, from [Buttons::buttons_t]
    /// @param state The state on which to call the callback, true for rising, false for falling
    /// @param callback The callback that is called once every time the button reaches the event
    void subscribe_button(uint button, bool state, void (*callback)())
    {
        switch(button)
        {
            case BUT_A:
                if(state)
                    reserved::callback_A_rise = callback;
                else
                    reserved::callback_A_fall = callback;
                break;
            case BUT_B:
                if(state)
                    reserved::callback_B_rise = callback;
                else
                    reserved::callback_B_fall = callback;
                break;
            case BUT_1:
                if(state)
                    reserved::callback_1_rise = callback;
                else
                    reserved::callback_1_fall = callback;
                break;
            case BUT_2:
                if(state)
                    reserved::callback_2_rise = callback;
                else
                    reserved::callback_2_fall = callback;
                break;
            case BUT_3:
                if(state)
                    reserved::callback_3_rise = callback;
                else
                    reserved::callback_3_fall = callback;
                break;
            case BUT_4:
                if(state)
                    reserved::callback_4_rise = callback;
                else
                    reserved::callback_4_fall = callback;
                break;
            default:
                printf("Warning: Tried to subscribe to non-button! (buttons.hpp)\n");
        }
    }

    /// @brief Unsubscribe from a button, rising or falling
    /// @param button Which button to unsubscribe from, from [Buttons::buttons_t]
    /// @param state The state on which to unsubscribe, true for rising, false for falling
    void unsubscribe_button(uint button, bool state)
    {
        switch(button)
        {
            case BUT_A:
                if(state)
                    reserved::callback_A_rise = nullptr;
                else
                    reserved::callback_A_fall = nullptr;
                break;
            case BUT_B:
                if(state)
                    reserved::callback_B_rise = nullptr;
                else
                    reserved::callback_B_fall = nullptr;
                break;
            case BUT_1:
                if(state)
                    reserved::callback_1_rise = nullptr;
                else
                    reserved::callback_1_fall = nullptr;
                break;
            case BUT_2:
                if(state)
                    reserved::callback_2_rise = nullptr;
                else
                    reserved::callback_2_fall = nullptr;
                break;
            case BUT_3:
                if(state)
                    reserved::callback_3_rise = nullptr;
                else
                    reserved::callback_3_fall = nullptr;
                break;
            case BUT_4:
                if(state)
                    reserved::callback_4_rise = nullptr;
                else
                    reserved::callback_4_fall = nullptr;
                break;
            default:
                printf("Warning: Tried to unsubscribe to non-button! (buttons.hpp)\n");
        }
    }

    void cancel_all_callbacks()
    {
        reserved::reset_callbacks();
    }
}