#include "globals.hpp"

#include "console/main.hpp"

using namespace Console;

int main()
{
    stdio_init_all();

    Led::init();

    

    void *h;
    float b = 6;
    int c = 7;

    h = &b;

    c = *(int *)h;

    printf("%d", c);

    while(true)
    {
        Led::set(100, 400);
        sleep_ms(1200);
    }
}