#include "globals.hpp"

#include "console/main.hpp"

using namespace Console;

int main()
{
    stdio_init_all();

    Led::init();

    while(true)
    {
        Led::set(100, 400);
        sleep_ms(1200);
    }
}