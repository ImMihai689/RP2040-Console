#include "console/common.hpp"
#include "console/main.hpp"

int main()
{
    stdio_init_all();

    while(true){
        printf("PI is %f, TwoPI is %f, HalfPI is %f\n", (double)Fixed(PI_FIXED_INT, true), (double)Fixed(TWO_PI_FIXED_INT, true), (double)Fixed(HALF_PI_FIXED_INT, true) );
        sleep_ms(1000);
    }
}