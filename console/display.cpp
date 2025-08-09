#include "display.hpp"

#include "common.hpp"
#include "hardware/structs/spi.h"
#include "hardware/regs/dreq.h"


Display::Display()
{
    init();
}

Display::~Display()
{

}

void Display::send_command(unsigned char cmd)
{
    gpio_put(DC_PIN, false);
    spi_write_blocking(spi0, &cmd, 1);
}

void Display::init()
{
    (void)spi_init(spi0, 10000000);
    gpio_set_function(CS_PIN, GPIO_FUNC_SPI);
    gpio_set_function(SCLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(MOSI_PIN, GPIO_FUNC_SPI);
    gpio_init(DC_PIN);
    gpio_init(RESET_PIN);
    gpio_set_dir(DC_PIN, GPIO_OUT);
    gpio_set_dir(RESET_PIN, GPIO_OUT);
    gpio_put(DC_PIN, false);
    gpio_put(RESET_PIN, true);
    gpio_put(RESET_PIN, false);
    sleep_ms(10);
    gpio_put(RESET_PIN, true);

    spi_write_blocking(spi0, display_init_sequence, 26);
}

void Display::reset()
{
    gpio_put(RESET_PIN, false);
    sleep_ms(10);
    gpio_put(RESET_PIN, true);
}


void Display::update(Frame *buffer)
{
    gpio_put(DC_PIN, true);
    spi_write_blocking(spi0, buffer->get_data(), 1024);
}