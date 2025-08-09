#include "frame.hpp"

#include "common.hpp"

#define fabs(a) (((a) > 0) ? (a) : -(a))
#define fswap(a, b)                                                     \
  (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))) ///< No-temp-var swap operation

Frame::Frame()
{

}

Frame::~Frame()
{

}

void Frame::clearFrame()
{
    for(int i = 0; i < 1024; i++)
    {
        buffer[i] = 0;
    }
}

void Frame::fillFrame(unsigned char data)
{
    for(int i = 0; i < 1024; i++)
    {
        buffer[i] = data;
    }
}

void Frame::drawPixel(int x, int y, color_t color)
{
    if(x < 0 || y < 0 || x > 127 || y > 63) return;
    switch(color)
    {
        case 0:
            break;
        case 1:
            drawPixelFastInverted((unsigned char)(127 - x), (unsigned char)(63 - y));
            break;
        case 2:
            drawPixelFastWhite((unsigned char)(127 - x), (unsigned char)(63 - y));
            break;
        case 3:
            drawPixelFastBlack((unsigned char)(127 - x), (unsigned char)(63 - y));
            break;
        default:
            printf("[Warning][frame.cpp] Invalid color!\n");
    }
}

void Frame::drawLineHorizontal(int x, int y, int w, color_t color)
{
    int final_x = x + w;
        for(int i = x; i < final_x; i++)
            drawPixel(i, y, color);
}

void Frame::drawLineVertical(int x, int y, int h, color_t color)
{
    int final_y = y + h;
        for(int i = y; i < final_y; i++)
            drawPixel(x, i, color);
}

void Frame::drawLine(int x0, int y0, int x1, int y1, color_t color)
{
    bool steep = fabs(y1 - y0) > fabs(x1 - x0);
    if(steep)
    {
        fswap(x0, y0);
        fswap(x1, y1);
    }
    if (x0 > x1) 
    {
        fswap(x0, x1);
        fswap(y0, y1);
    }

    int dx, dy;
    dx = x1 - x0;
    dy = fabs(y1 - y0);

    int err = dx / 2;
    int ystep;

    if (y0 < y1)
        ystep = 1;
    else
        ystep = -1;
    
    for (; x0 <= x1; x0++) 
    {
        if (steep)
            drawPixel(y0, x0, color);
        else
            drawPixel(x0, y0, color);
        
        err -= dy;
        if (err < 0) 
        {
            y0 += ystep;
            err += dx;
        }
    }
}

void Frame::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    drawLine(x0, y0, x1, y1, color);
    drawLine(x2, y2, x1, y1, color);
    drawLine(x0, y0, x2, y2, color);
}

void Frame::drawTriangleFilled(int x0, int y0, int x1, int y1, int x2, int y2, color_t color)
{
    int a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        fswap(y0, y1);
        fswap(x0, x1);
    }
    if (y1 > y2) {
        fswap(y2, y1);
        fswap(x2, x1);
    }
    if (y0 > y1) {
        fswap(y0, y1);
        fswap(x0, x1);
    }

    if (y0 == y2) 
    { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if (x1 < a)
            a = x1;
        else if (x1 > b)
            b = x1;
        if (x2 < a)
            a = x2;
        else if (x2 > b)
            b = x2;
        drawLineHorizontal(a, y0, b - a + 1, color);
        return;
    }

    int 
    dx01 = x1 - x0, 
    dy01 = y1 - y0, 
    dx02 = x2 - x0, 
    dy02 = y2 - y0,
    dx12 = x2 - x1, 
    dy12 = y2 - y1;

    Fixed s01 = Fixed(dx01) / Fixed(dy01);
    Fixed s02 = Fixed(dx02) / Fixed(dy02);
    Fixed s12 = Fixed(dx12) / Fixed(dy12);
    
    int sa = 0, sb = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if (y1 == y2)
        last = y1; // Include y1 scanline
    else
        last = y1 - 1; // Skip it

    for (y = y0; y <= last; y++) {
        a = s01 * sa + x0;
        b = s02 * sb + x0;
        sa++;
        sb++;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b)
            fswap(a, b);
        drawLineHorizontal(a, y, b - a + 1, color);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = 0;
    for (; y <= y2; y++) {
        a = s12 * sa + x1;
        b = s02 * sb + x0;
        sa++;
        sb++;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
        */
        if (a > b)
            fswap(a, b);
        drawLineHorizontal(a, y, b - a + 1, color);
    }
}

void Frame::drawBitmap(int x, int y, const unsigned char* bitmap, int w, int h, color_t color)
{
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            int byte = ((i >> 3) * w) + j;
            int bit = i & 0b111;
            int value = (bitmap[byte]) & (1 << bit);
            if(value)
            {
                drawPixel(j + x, i + y, color);
            }
        }
    }
}

void Frame::drawChar(int x, int y, char character, color_t color)
{
    if(31 < character && character < 128)
    {
        drawBitmap(x, y, font5x7[character - 32], 5, 7, color);
        return;
    }
    else if(127 < character && character < 138)
    {
        drawBitmap(x, y, font5x7[character - 32], 5, 8, color);
        return;
    }
}

void Frame::drawText(int x, int y, char* text, int no_characters, color_t color)
{
    int cursor_x = x;
    int cursor_y = y;
    for(int i = 0; i < no_characters; i++)
    {
        if(text[i] == '\n')
        {
            cursor_y += 8;
            cursor_x = x;
        }
        else
        {
            drawChar(cursor_x, cursor_y, text[i], color);
            cursor_x += 6;
        }   
    }
}

void Frame::drawText(int x, int y, const char* text, int no_characters, color_t color)
{
    int cursor_x = x;
    int cursor_y = y;
    for(int i = 0; i < no_characters; i++)
    {
        if(text[i] == '\n')
        {
            cursor_y += 8;
            cursor_x = x;
        }
        else
        {
            drawChar(cursor_x, cursor_y, text[i], color);
            cursor_x += 6;
        }   
    }
}