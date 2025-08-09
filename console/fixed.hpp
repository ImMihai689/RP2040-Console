#ifndef FIXED_MATH
#define FIXED_MATH

#ifndef FIXED_DECIMALS
    #define FIXED_DECIMALS 18
#endif
#define FIXED_UNIT (1 << FIXED_DECIMALS)

#define PI (double)3.14159265358979323846
#define TWO_PI (double)6.28318530717958647693
#define HALF_PI (double)1.57079632679489661923

#define PI_FIXED_INT (int)(PI * FIXED_UNIT)
#define TWO_PI_FIXED_INT (int)(TWO_PI * FIXED_UNIT)
#define HALF_PI_FIXED_INT (int)(HALF_PI * FIXED_UNIT)

#define FIXED_MAX_INT (int)(1 << (31 - FIXED_DECIMALS))
#define FIXED_MAX_VALUE (int)(1 << 31)
#define FIXED_HALF (int)(1 << (FIXED_DECIMALS - 1))

#define NO_CAST true
#define CAST false

class Fixed
{

    public:
        int value;

        inline Fixed()
        {
            value = 0;
        }

        inline Fixed(int val, bool no_cast = false)
        {
            if(no_cast)
                value = val;
            else
                value = (val << FIXED_DECIMALS);
        }

        inline Fixed(float val)
        {
            value = ((int)(val * FIXED_UNIT));
        }

        inline Fixed(double val)
        {
            value = ((int)(val * FIXED_UNIT));
        }

        inline Fixed(const Fixed& val)
        {
            value = val.value;
        }
        
        inline operator int() const 
        {
            return value >> FIXED_DECIMALS;
        }

        inline operator short() const
        {
            return (short int)(value >> FIXED_DECIMALS);
        }

        inline operator float() const
        {
            return (((float)value) / FIXED_UNIT);
        }

        inline operator double() const
        {
            return (((double)value) / FIXED_UNIT);
        }

        // Fixed on Fixed

        Fixed operator +(const Fixed& other)
        {
            Fixed temp;
            temp.value = value + other.value;
            return temp;
        }
 
        Fixed operator -(const Fixed& other)
        {
            Fixed temp;
            temp.value = value - other.value;
            return temp;
        }

        Fixed operator *(const Fixed& other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> FIXED_DECIMALS);

            return temp;
        }

        Fixed operator /(const Fixed& other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) << FIXED_DECIMALS) / other.value);

            return temp;
        }
        

        inline Fixed operator +=(const Fixed& other)
        {
            value += other.value;
            return *this;
        }

        inline Fixed operator -=(const Fixed& other)
        {
            value -= other.value;
            return *this;
        }

        inline Fixed operator *=(const Fixed& other)
        {
            value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> FIXED_DECIMALS);
            return *this;
        }

        inline Fixed operator /=(const Fixed& other)
        {   
            value = (int)((((signed long long)(value)) << FIXED_DECIMALS) / (signed long long)other.value);
            return *this;
        }

        // Fixed on int

        Fixed operator +(int intValue)
        {
            Fixed temp;
            temp.value = value + (intValue << FIXED_DECIMALS);
            return temp;
        }

        Fixed operator -(int intValue)
        {
            Fixed temp;
            temp.value = value - (intValue << FIXED_DECIMALS);
            return temp;
        }

        Fixed operator *(int intValue)
        {
            return Fixed(value * intValue, true);
        }

        Fixed operator /(int intValue)
        {
            return Fixed((value) / intValue, true);
        }
        

        inline Fixed operator +=(int intValue)
        {
            value += (intValue << FIXED_DECIMALS);
            return *this;
        }

        inline Fixed operator -=(int intValue)
        {
            value -= (intValue << FIXED_DECIMALS);
            return *this;
        }

        inline Fixed operator *=(int intValue)
        {
            value = value * intValue;
            return *this;
        }

        inline Fixed operator /=(int intValue)
        {
            value = value / intValue;
            return *this;
        }

        // Fixed on float

        Fixed operator +(float floatValue)
        {
            Fixed temp;

            temp.value = value + ((int)(floatValue * FIXED_UNIT));

            return temp;
        }

        Fixed operator -(float floatValue)
        {
            Fixed temp;

            temp.value = value - ((int)(floatValue * FIXED_UNIT));
            
            return temp;
        }

        Fixed operator *(float floatValue)
        {
            Fixed temp;

            temp.value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> FIXED_DECIMALS));
            
            return temp;
        }

        Fixed operator /(float floatValue)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value) << FIXED_DECIMALS) / (signed long long)(Fixed(floatValue)).value));
            
            return temp;
        }
        

        Fixed operator +=(float floatValue)
        {
            value = value + Fixed(floatValue).value;

            return *this;
        }

        Fixed operator -=(float floatValue)
        {
            value = value - Fixed(floatValue).value;
            
            return *this;
        }

        inline Fixed operator *=(float floatValue)
        {
            value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> FIXED_DECIMALS));
            
            return *this;
        }

        inline Fixed operator /=(float floatValue)
        {
            value = (int)((((signed long long)(value) << FIXED_DECIMALS) / (signed long long)(Fixed(floatValue)).value));
            
            return *this;
        }
        

        // Fixed on double

        Fixed operator +(double floatValue)
        {
            Fixed temp;

            temp.value = value + ((int)(floatValue * FIXED_UNIT));

            return temp;
        }

        Fixed operator -(double floatValue)
        {
            Fixed temp;

            temp.value = value - ((int)(floatValue * FIXED_UNIT));
            
            return temp;
        }

        Fixed operator *(double floatValue)
        {
            Fixed temp;

            temp.value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> FIXED_DECIMALS));
            
            return temp;
        }

        Fixed operator /(double floatValue)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value) << FIXED_DECIMALS) / (signed long long)(Fixed(floatValue).value)));
            
            return temp;
        }
        

        inline Fixed operator +=(double floatValue)
        {
            value = value + Fixed(floatValue).value;

            return *this;
        }

        inline Fixed operator -=(double floatValue)
        {
            value = value - Fixed(floatValue).value;

            return *this;
        }

        inline Fixed operator *=(double floatValue)
        {
            value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> FIXED_DECIMALS));
            
            return *this;
        }

        inline Fixed operator /=(double floatValue)
        {
            value = (int)((((signed long long)(value) << FIXED_DECIMALS) / (signed long long)(Fixed(floatValue).value)));
            
            return *this;
        }

        
        // Comparasion (Fixed on Fixed)

        inline bool operator ==(const Fixed& other)
        {
            return (value == other.value);
        }

        inline bool operator !=(const Fixed& other)
        {
            return (value != other.value);
        }

        inline bool operator >(const Fixed& other)
        {
            return (value > other.value);
        }

        inline bool operator <(const Fixed& other)
        {
            return (value < other.value);
        }

        inline bool operator >=(const Fixed& other)
        {
            return (value >= other.value);
        }

        inline bool operator <=(const Fixed& other)
        {
            return (value <= other.value);
        }
        

        // Comparasion (Fixed on float)

        inline bool operator ==(float other)
        {
            return (value == (Fixed(other)).value);
        }

        inline bool operator !=(float other)
        {
            return (value != (Fixed(other)).value);
        }

        inline bool operator >(float other)
        {
            return (value > (Fixed(other)).value);
        }

        inline bool operator <(float other)
        {
            return (value < (Fixed(other)).value);
        }

        inline bool operator >=(float other)
        {
            return (value >= (Fixed(other)).value);
        }

        inline bool operator <=(float other)
        {
            return (value <= Fixed(other).value);
        }


        // Comparasion (Fixed on double)

        inline bool operator ==(double other)
        {
            return (value == (Fixed(other)).value);
        }

        inline bool operator !=(double other)
        {
            return (value != (Fixed(other)).value);
        }

        inline bool operator >(double other)
        {
            return (value > (Fixed(other)).value);
        }

        inline bool operator <(double other)
        {
            return (value < (Fixed(other)).value);
        }

        inline bool operator >=(double other)
        {
            return (value >= (Fixed(other)).value);
        }

        inline bool operator <=(double other)
        {
            return (value <= Fixed(other).value);
        }

        // Comparasion (Fixed on int)

        inline bool operator ==(int other)
        {
            return (value == (other << FIXED_DECIMALS));
        }

        inline bool operator !=(int other)
        {
            return (value != (other << FIXED_DECIMALS));
        }

        inline bool operator >(int other)
        {
            return (value > (other << FIXED_DECIMALS));
        }

        inline bool operator <(int other)
        {
            return (value < (other << FIXED_DECIMALS));
        }

        inline bool operator >=(int other)
        {
            return (value >= (other << FIXED_DECIMALS));
        }

        inline bool operator <=(int other)
        {
            return (value <= (other << FIXED_DECIMALS));
        }
        

        // Other math

        Fixed operator+()
        {
            return Fixed(value, true);
        }

        Fixed operator-()
        {
            return Fixed(-value, true);
        }

        inline Fixed floor()
        {
            return Fixed((value >> FIXED_DECIMALS));
        }

        inline int floor2int()
        {
            return value >> FIXED_DECIMALS;
        }

        inline int ceil2int()
        {
            int decimals = value & (FIXED_UNIT - 1);

            int floored = value >> FIXED_DECIMALS;

            if(decimals != 0)
                floored++;
            
            return floored;
        }

        inline int round2int()
        {
            return (value + FIXED_HALF) >> FIXED_DECIMALS;
        }

        inline Fixed decimals()
        {
            return Fixed(value & (FIXED_UNIT - 1), true);
        }




        /// @brief Maps val from range [min, max1] to the range [min2, max2]
        /// @param val 
        /// @param min1 
        /// @param max1 
        /// @param min2 
        /// @param max2 
        /// @return 
        static Fixed map(Fixed val, Fixed min1, Fixed max1, Fixed min2, Fixed max2)
        {
            return min2 + (val - min1) * (max2 - min2) / (max1 - min1);
        }

        static Fixed inverse_sqrt(Fixed number)
        {
            float floating = (float)number.value / (float)FIXED_UNIT;
            long i;
            float x2, y;
            const float threehalfs = 1.5F;

            x2 = floating * 0.5F;
            y  = floating;
            i  = * ( long * ) &y;                       // evil floating point bit level hacking
            i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
            y  = * ( float * ) &i;
            y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
            y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

            return Fixed(y);
        }

        static Fixed sin(const Fixed& angle)
        {
            Fixed trimmed = Fixed(angle.value % TWO_PI_FIXED_INT, true);
            bool neg = false;
            if(trimmed.value < 0)
            {
                trimmed.value = -trimmed.value;
                neg = true;
            }
            
            Fixed lut_position = trimmed * (256 / TWO_PI);

            int lut_addr = lut_position.floor2int() & 255;
            int lut_addr_ = (lut_addr + 1) & 255;

            Fixed frac = lut_position.decimals();

            if(!neg)
                return Fixed(frac.sin_lut[lut_addr] + (int)(frac * (frac.sin_lut[lut_addr_] - frac.sin_lut[lut_addr])), true);
            else
                return -Fixed(frac.sin_lut[lut_addr] + (int)(frac * (frac.sin_lut[lut_addr_] - frac.sin_lut[lut_addr])), true);
        }

        static Fixed cos(const Fixed& angle)
        {
            Fixed trimmed = Fixed((angle.value + HALF_PI_FIXED_INT) % TWO_PI_FIXED_INT, true);
            if(trimmed.value < 0)
                trimmed.value = -trimmed.value;
            
            Fixed lut_position = trimmed * (256 / TWO_PI);

            int lut_addr = lut_position.floor2int() & 255;
            int lut_addr_ = (lut_addr + 1) & 255;

            Fixed frac = lut_position.decimals();

            return Fixed(Fixed::sin_lut[lut_addr] + (int)(frac * (Fixed::sin_lut[lut_addr_] - Fixed::sin_lut[lut_addr])), true);
        }
    
        static constexpr int sin_lut[256] = 
        {
            (int)( 0.0 * FIXED_UNIT ), 
            (int)( 0.024541228522912288 * FIXED_UNIT ), 
            (int)( 0.049067674327418015 * FIXED_UNIT ), 
            (int)( 0.07356456359966743 * FIXED_UNIT ), 
            (int)( 0.0980171403295606 * FIXED_UNIT ), 
            (int)( 0.1224106751992162 * FIXED_UNIT ), 
            (int)( 0.14673047445536175 * FIXED_UNIT ), 
            (int)( 0.17096188876030122 * FIXED_UNIT ), 
            (int)( 0.19509032201612825 * FIXED_UNIT ), 
            (int)( 0.2191012401568698 * FIXED_UNIT ), 
            (int)( 0.24298017990326387 * FIXED_UNIT ), 
            (int)( 0.26671275747489837 * FIXED_UNIT ), 
            (int)( 0.29028467725446233 * FIXED_UNIT ), 
            (int)( 0.3136817403988915 * FIXED_UNIT ), 
            (int)( 0.33688985339222005 * FIXED_UNIT ), 
            (int)( 0.3598950365349881 * FIXED_UNIT ), 
            (int)( 0.3826834323650898 * FIXED_UNIT ), 
            (int)( 0.40524131400498986 * FIXED_UNIT ), 
            (int)( 0.4275550934302821 * FIXED_UNIT ), 
            (int)( 0.44961132965460654 * FIXED_UNIT ), 
            (int)( 0.47139673682599764 * FIXED_UNIT ), 
            (int)( 0.49289819222978404 * FIXED_UNIT ), 
            (int)( 0.5141027441932217 * FIXED_UNIT ), 
            (int)( 0.5349976198870972 * FIXED_UNIT ), 
            (int)( 0.5555702330196022 * FIXED_UNIT ), 
            (int)( 0.5758081914178453 * FIXED_UNIT ), 
            (int)( 0.5956993044924334 * FIXED_UNIT ), 
            (int)( 0.6152315905806268 * FIXED_UNIT ), 
            (int)( 0.6343932841636455 * FIXED_UNIT ), 
            (int)( 0.6531728429537768 * FIXED_UNIT ), 
            (int)( 0.6715589548470183 * FIXED_UNIT ), 
            (int)( 0.6895405447370668 * FIXED_UNIT ), 
            (int)( 0.7071067811865475 * FIXED_UNIT ), 
            (int)( 0.7242470829514669 * FIXED_UNIT ), 
            (int)( 0.7409511253549591 * FIXED_UNIT ), 
            (int)( 0.7572088465064845 * FIXED_UNIT ), 
            (int)( 0.773010453362737 * FIXED_UNIT ), 
            (int)( 0.7883464276266062 * FIXED_UNIT ), 
            (int)( 0.8032075314806448 * FIXED_UNIT ), 
            (int)( 0.8175848131515837 * FIXED_UNIT ), 
            (int)( 0.8314696123025452 * FIXED_UNIT ), 
            (int)( 0.844853565249707 * FIXED_UNIT ), 
            (int)( 0.8577286100002721 * FIXED_UNIT ), 
            (int)( 0.8700869911087113 * FIXED_UNIT ), 
            (int)( 0.8819212643483549 * FIXED_UNIT ), 
            (int)( 0.8932243011955153 * FIXED_UNIT ), 
            (int)( 0.9039892931234433 * FIXED_UNIT ), 
            (int)( 0.9142097557035307 * FIXED_UNIT ), 
            (int)( 0.9238795325112867 * FIXED_UNIT ), 
            (int)( 0.9329927988347388 * FIXED_UNIT ), 
            (int)( 0.9415440651830208 * FIXED_UNIT ), 
            (int)( 0.9495281805930367 * FIXED_UNIT ), 
            (int)( 0.9569403357322089 * FIXED_UNIT ), 
            (int)( 0.9637760657954398 * FIXED_UNIT ), 
            (int)( 0.970031253194544 * FIXED_UNIT ), 
            (int)( 0.9757021300385286 * FIXED_UNIT ), 
            (int)( 0.9807852804032304 * FIXED_UNIT ), 
            (int)( 0.9852776423889412 * FIXED_UNIT ), 
            (int)( 0.989176509964781 * FIXED_UNIT ), 
            (int)( 0.99247953459871 * FIXED_UNIT ), 
            (int)( 0.9951847266721968 * FIXED_UNIT ), 
            (int)( 0.9972904566786902 * FIXED_UNIT ), 
            (int)( 0.9987954562051724 * FIXED_UNIT ), 
            (int)( 0.9996988186962042 * FIXED_UNIT ), 
            (int)( 1.0 * FIXED_UNIT ), 
            (int)( 0.9996988186962042 * FIXED_UNIT ), 
            (int)( 0.9987954562051724 * FIXED_UNIT ), 
            (int)( 0.9972904566786902 * FIXED_UNIT ), 
            (int)( 0.9951847266721969 * FIXED_UNIT ), 
            (int)( 0.99247953459871 * FIXED_UNIT ), 
            (int)( 0.989176509964781 * FIXED_UNIT ), 
            (int)( 0.9852776423889412 * FIXED_UNIT ), 
            (int)( 0.9807852804032304 * FIXED_UNIT ), 
            (int)( 0.9757021300385286 * FIXED_UNIT ), 
            (int)( 0.970031253194544 * FIXED_UNIT ), 
            (int)( 0.9637760657954398 * FIXED_UNIT ), 
            (int)( 0.9569403357322089 * FIXED_UNIT ), 
            (int)( 0.9495281805930367 * FIXED_UNIT ), 
            (int)( 0.9415440651830208 * FIXED_UNIT ), 
            (int)( 0.9329927988347388 * FIXED_UNIT ), 
            (int)( 0.9238795325112867 * FIXED_UNIT ), 
            (int)( 0.9142097557035307 * FIXED_UNIT ), 
            (int)( 0.9039892931234434 * FIXED_UNIT ), 
            (int)( 0.8932243011955152 * FIXED_UNIT ), 
            (int)( 0.881921264348355 * FIXED_UNIT ), 
            (int)( 0.8700869911087115 * FIXED_UNIT ), 
            (int)( 0.8577286100002721 * FIXED_UNIT ), 
            (int)( 0.8448535652497072 * FIXED_UNIT ), 
            (int)( 0.8314696123025455 * FIXED_UNIT ), 
            (int)( 0.8175848131515837 * FIXED_UNIT ), 
            (int)( 0.8032075314806449 * FIXED_UNIT ), 
            (int)( 0.7883464276266063 * FIXED_UNIT ), 
            (int)( 0.7730104533627371 * FIXED_UNIT ), 
            (int)( 0.7572088465064847 * FIXED_UNIT ), 
            (int)( 0.740951125354959 * FIXED_UNIT ), 
            (int)( 0.7242470829514669 * FIXED_UNIT ), 
            (int)( 0.7071067811865476 * FIXED_UNIT ), 
            (int)( 0.689540544737067 * FIXED_UNIT ), 
            (int)( 0.6715589548470186 * FIXED_UNIT ), 
            (int)( 0.6531728429537766 * FIXED_UNIT ), 
            (int)( 0.6343932841636455 * FIXED_UNIT ), 
            (int)( 0.6152315905806269 * FIXED_UNIT ), 
            (int)( 0.5956993044924335 * FIXED_UNIT ), 
            (int)( 0.5758081914178454 * FIXED_UNIT ), 
            (int)( 0.5555702330196022 * FIXED_UNIT ), 
            (int)( 0.5349976198870972 * FIXED_UNIT ), 
            (int)( 0.5141027441932218 * FIXED_UNIT ), 
            (int)( 0.49289819222978415 * FIXED_UNIT ), 
            (int)( 0.47139673682599786 * FIXED_UNIT ), 
            (int)( 0.4496113296546069 * FIXED_UNIT ), 
            (int)( 0.42755509343028203 * FIXED_UNIT ), 
            (int)( 0.4052413140049899 * FIXED_UNIT ), 
            (int)( 0.3826834323650899 * FIXED_UNIT ), 
            (int)( 0.35989503653498833 * FIXED_UNIT ), 
            (int)( 0.33688985339222033 * FIXED_UNIT ), 
            (int)( 0.3136817403988914 * FIXED_UNIT ), 
            (int)( 0.2902846772544624 * FIXED_UNIT ), 
            (int)( 0.2667127574748985 * FIXED_UNIT ), 
            (int)( 0.24298017990326407 * FIXED_UNIT ), 
            (int)( 0.21910124015687005 * FIXED_UNIT ), 
            (int)( 0.1950903220161286 * FIXED_UNIT ), 
            (int)( 0.17096188876030122 * FIXED_UNIT ), 
            (int)( 0.1467304744553618 * FIXED_UNIT ), 
            (int)( 0.12241067519921635 * FIXED_UNIT ), 
            (int)( 0.09801714032956083 * FIXED_UNIT ), 
            (int)( 0.07356456359966773 * FIXED_UNIT ), 
            (int)( 0.049067674327417966 * FIXED_UNIT ), 
            (int)( 0.024541228522912326 * FIXED_UNIT ), 
            (int)( 1.2246467991473532e-16 * FIXED_UNIT ), 
            (int)( -0.02454122852291208 * FIXED_UNIT ), 
            (int)( -0.049067674327417724 * FIXED_UNIT ), 
            (int)( -0.0735645635996675 * FIXED_UNIT ), 
            (int)( -0.09801714032956059 * FIXED_UNIT ), 
            (int)( -0.1224106751992161 * FIXED_UNIT ), 
            (int)( -0.14673047445536158 * FIXED_UNIT ), 
            (int)( -0.17096188876030097 * FIXED_UNIT ), 
            (int)( -0.19509032201612836 * FIXED_UNIT ), 
            (int)( -0.2191012401568698 * FIXED_UNIT ), 
            (int)( -0.24298017990326382 * FIXED_UNIT ), 
            (int)( -0.26671275747489825 * FIXED_UNIT ), 
            (int)( -0.2902846772544621 * FIXED_UNIT ), 
            (int)( -0.3136817403988912 * FIXED_UNIT ), 
            (int)( -0.3368898533922201 * FIXED_UNIT ), 
            (int)( -0.3598950365349881 * FIXED_UNIT ), 
            (int)( -0.38268343236508967 * FIXED_UNIT ), 
            (int)( -0.4052413140049897 * FIXED_UNIT ), 
            (int)( -0.4275550934302818 * FIXED_UNIT ), 
            (int)( -0.44961132965460665 * FIXED_UNIT ), 
            (int)( -0.47139673682599764 * FIXED_UNIT ), 
            (int)( -0.4928981922297839 * FIXED_UNIT ), 
            (int)( -0.5141027441932216 * FIXED_UNIT ), 
            (int)( -0.5349976198870969 * FIXED_UNIT ), 
            (int)( -0.555570233019602 * FIXED_UNIT ), 
            (int)( -0.5758081914178453 * FIXED_UNIT ), 
            (int)( -0.5956993044924332 * FIXED_UNIT ), 
            (int)( -0.6152315905806267 * FIXED_UNIT ), 
            (int)( -0.6343932841636453 * FIXED_UNIT ), 
            (int)( -0.6531728429537765 * FIXED_UNIT ), 
            (int)( -0.6715589548470184 * FIXED_UNIT ), 
            (int)( -0.6895405447370668 * FIXED_UNIT ), 
            (int)( -0.7071067811865475 * FIXED_UNIT ), 
            (int)( -0.7242470829514668 * FIXED_UNIT ), 
            (int)( -0.7409511253549589 * FIXED_UNIT ), 
            (int)( -0.7572088465064842 * FIXED_UNIT ), 
            (int)( -0.7730104533627367 * FIXED_UNIT ), 
            (int)( -0.7883464276266059 * FIXED_UNIT ), 
            (int)( -0.803207531480645 * FIXED_UNIT ), 
            (int)( -0.8175848131515838 * FIXED_UNIT ), 
            (int)( -0.8314696123025452 * FIXED_UNIT ), 
            (int)( -0.844853565249707 * FIXED_UNIT ), 
            (int)( -0.857728610000272 * FIXED_UNIT ), 
            (int)( -0.8700869911087113 * FIXED_UNIT ), 
            (int)( -0.8819212643483549 * FIXED_UNIT ), 
            (int)( -0.8932243011955152 * FIXED_UNIT ), 
            (int)( -0.9039892931234431 * FIXED_UNIT ), 
            (int)( -0.9142097557035305 * FIXED_UNIT ), 
            (int)( -0.9238795325112865 * FIXED_UNIT ), 
            (int)( -0.932992798834739 * FIXED_UNIT ), 
            (int)( -0.9415440651830208 * FIXED_UNIT ), 
            (int)( -0.9495281805930367 * FIXED_UNIT ), 
            (int)( -0.9569403357322088 * FIXED_UNIT ), 
            (int)( -0.9637760657954398 * FIXED_UNIT ), 
            (int)( -0.970031253194544 * FIXED_UNIT ), 
            (int)( -0.9757021300385285 * FIXED_UNIT ), 
            (int)( -0.9807852804032303 * FIXED_UNIT ), 
            (int)( -0.9852776423889411 * FIXED_UNIT ), 
            (int)( -0.9891765099647809 * FIXED_UNIT ), 
            (int)( -0.9924795345987101 * FIXED_UNIT ), 
            (int)( -0.9951847266721969 * FIXED_UNIT ), 
            (int)( -0.9972904566786902 * FIXED_UNIT ), 
            (int)( -0.9987954562051724 * FIXED_UNIT ), 
            (int)( -0.9996988186962042 * FIXED_UNIT ), 
            (int)( -1.0 * FIXED_UNIT ), 
            (int)( -0.9996988186962042 * FIXED_UNIT ), 
            (int)( -0.9987954562051724 * FIXED_UNIT ), 
            (int)( -0.9972904566786902 * FIXED_UNIT ), 
            (int)( -0.9951847266721969 * FIXED_UNIT ), 
            (int)( -0.9924795345987101 * FIXED_UNIT ), 
            (int)( -0.9891765099647809 * FIXED_UNIT ), 
            (int)( -0.9852776423889412 * FIXED_UNIT ), 
            (int)( -0.9807852804032304 * FIXED_UNIT ), 
            (int)( -0.9757021300385286 * FIXED_UNIT ), 
            (int)( -0.970031253194544 * FIXED_UNIT ), 
            (int)( -0.96377606579544 * FIXED_UNIT ), 
            (int)( -0.9569403357322089 * FIXED_UNIT ), 
            (int)( -0.9495281805930368 * FIXED_UNIT ), 
            (int)( -0.9415440651830209 * FIXED_UNIT ), 
            (int)( -0.9329927988347391 * FIXED_UNIT ), 
            (int)( -0.9238795325112866 * FIXED_UNIT ), 
            (int)( -0.9142097557035306 * FIXED_UNIT ), 
            (int)( -0.9039892931234433 * FIXED_UNIT ), 
            (int)( -0.8932243011955153 * FIXED_UNIT ), 
            (int)( -0.881921264348355 * FIXED_UNIT ), 
            (int)( -0.8700869911087115 * FIXED_UNIT ), 
            (int)( -0.8577286100002722 * FIXED_UNIT ), 
            (int)( -0.8448535652497072 * FIXED_UNIT ), 
            (int)( -0.8314696123025455 * FIXED_UNIT ), 
            (int)( -0.817584813151584 * FIXED_UNIT ), 
            (int)( -0.8032075314806453 * FIXED_UNIT ), 
            (int)( -0.7883464276266061 * FIXED_UNIT ), 
            (int)( -0.7730104533627369 * FIXED_UNIT ), 
            (int)( -0.7572088465064846 * FIXED_UNIT ), 
            (int)( -0.7409511253549591 * FIXED_UNIT ), 
            (int)( -0.724247082951467 * FIXED_UNIT ), 
            (int)( -0.7071067811865477 * FIXED_UNIT ), 
            (int)( -0.6895405447370672 * FIXED_UNIT ), 
            (int)( -0.6715589548470187 * FIXED_UNIT ), 
            (int)( -0.6531728429537771 * FIXED_UNIT ), 
            (int)( -0.6343932841636459 * FIXED_UNIT ), 
            (int)( -0.6152315905806274 * FIXED_UNIT ), 
            (int)( -0.5956993044924332 * FIXED_UNIT ), 
            (int)( -0.5758081914178452 * FIXED_UNIT ), 
            (int)( -0.5555702330196022 * FIXED_UNIT ), 
            (int)( -0.5349976198870973 * FIXED_UNIT ), 
            (int)( -0.5141027441932219 * FIXED_UNIT ), 
            (int)( -0.49289819222978426 * FIXED_UNIT ), 
            (int)( -0.4713967368259979 * FIXED_UNIT ), 
            (int)( -0.449611329654607 * FIXED_UNIT ), 
            (int)( -0.42755509343028253 * FIXED_UNIT ), 
            (int)( -0.4052413140049904 * FIXED_UNIT ), 
            (int)( -0.3826834323650904 * FIXED_UNIT ), 
            (int)( -0.359895036534988 * FIXED_UNIT ), 
            (int)( -0.33688985339222 * FIXED_UNIT ), 
            (int)( -0.3136817403988915 * FIXED_UNIT ), 
            (int)( -0.2902846772544625 * FIXED_UNIT ), 
            (int)( -0.2667127574748986 * FIXED_UNIT ), 
            (int)( -0.24298017990326418 * FIXED_UNIT ), 
            (int)( -0.21910124015687016 * FIXED_UNIT ), 
            (int)( -0.19509032201612872 * FIXED_UNIT ), 
            (int)( -0.17096188876030177 * FIXED_UNIT ), 
            (int)( -0.1467304744553624 * FIXED_UNIT ), 
            (int)( -0.12241067519921603 * FIXED_UNIT ), 
            (int)( -0.0980171403295605 * FIXED_UNIT ), 
            (int)( -0.07356456359966741 * FIXED_UNIT ), 
            (int)( -0.04906767432741809 * FIXED_UNIT ), 
            (int)( -0.024541228522912448 * FIXED_UNIT ), 
        };
        

};

#endif