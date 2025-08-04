#include "globals.hpp"

#include "console/main.hpp"

using namespace Console;

void buttontrigger2()
{
    Led::set(100, 10);
}

int main()
{
    stdio_init_all();

    initialize_console_all();

    Buttons::subscribe_button(Buttons::BUT_B, buttontrigger2);

    while(true){}
}