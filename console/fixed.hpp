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
 
        Fixed operator -(Fixed other)
        {
            Fixed temp;
            temp.value = value - other.value;
            return temp;
        }

        Fixed operator *(Fixed other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> FIXED_DECIMALS);

            return temp;
        }

        Fixed operator /(Fixed other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) << FIXED_DECIMALS) / other.value);

            return temp;
        }
        

        inline Fixed operator +=(Fixed other)
        {
            value += other.value;
            return *this;
        }

        inline Fixed operator -=(Fixed other)
        {
            value -= other.value;
            return *this;
        }

        inline Fixed operator *=(Fixed other)
        {
            value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> FIXED_DECIMALS);
            return *this;
        }

        inline Fixed operator /=(Fixed other)
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

        inline bool operator ==(Fixed other)
        {
            return (value == other.value);
        }

        inline bool operator !=(Fixed other)
        {
            return (value != other.value);
        }

        inline bool operator >(Fixed other)
        {
            return (value > other.value);
        }

        inline bool operator <(Fixed other)
        {
            return (value < other.value);
        }

        inline bool operator >=(Fixed other)
        {
            return (value >= other.value);
        }

        inline bool operator <=(Fixed other)
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
            int decimals = value & 0b111111111111111111;

            int floored = value >> FIXED_DECIMALS;

            if(decimals != 0)
                floored++;
            
            return floored;
        }

        inline int round2int()
        {
            return (value + FIXED_HALF) >> FIXED_DECIMALS;
        }




        /// @brief Maps val from range [min, max1] to the range [min2, max2]
        /// @param val 
        /// @param min1 
        /// @param max1 
        /// @param min2 
        /// @param max2 
        /// @return 
        static Fixed map(Fixed val, Fixed min1, Fixed max1, Fixed min2, Fixed max2);

        static Fixed inverse_sqrt(Fixed number);


        inline static Fixed sin(Fixed angle)
        {
            int temp_val = angle.value % TWO_PI_FIXED_INT;
            Fixed apropriate = Fixed(temp_val, true);
            return evaluate_sin(apropriate);
        }

        inline static Fixed cos(Fixed angle)
        {
            int temp_val = (angle.value + HALF_PI_FIXED_INT) % TWO_PI_FIXED_INT;
            Fixed apropriate = Fixed(temp_val, true);
            return evaluate_sin(apropriate);
        }
    
    private:

        
        static Fixed evaluate_sin(Fixed angle)
        {
            bool flip_sign = false;

            if(angle.value < -TWO_PI_FIXED_INT || angle.value > TWO_PI_FIXED_INT)
                return Fixed(-1);
            
            if(angle.value < 0)
            {
                flip_sign = true;
                angle.value = -angle.value;
            }

            if(angle.value > PI_FIXED_INT)
            {
                flip_sign = !flip_sign;
                angle.value -= PI_FIXED_INT;
            }
            
            if(angle.value > HALF_PI_FIXED_INT)
            {
                angle.value = HALF_PI_FIXED_INT - (angle.value - HALF_PI_FIXED_INT);
            }

            Fixed result = Fixed();
            
            if(angle.value < (int)235373)
            {
                result.value = angle.value;
                result = result - (angle * angle * angle) / (int)6;
                result = result + (angle * angle * angle * angle * angle) / (int)120;
                result = result - (angle * angle * angle * angle * angle * angle * angle) / (int)5040;
            }
            else
            {
                Fixed sincos_angle = Fixed(HALF_PI_FIXED_INT - angle.value, true);
                result.value = FIXED_UNIT;
                result = result - (sincos_angle * sincos_angle) / (int)2;
                result = result + (sincos_angle * sincos_angle * sincos_angle * sincos_angle) / (int)24;
                result = result - (sincos_angle * sincos_angle * sincos_angle * sincos_angle * sincos_angle * sincos_angle) / (int)720;
            }

            if(flip_sign)
                return -result;
            
            return result;
        }

};

#endif