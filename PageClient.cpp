#include <cmath>
#include "PageClient.h"

PageClient::PageClient(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
    : m_bitmap(bitmap), m_width(width), m_height(height), m_pixelWidth(pixelWidth)
{
}

void PageClient::paint()
{
    clear();
    paintLine(30, 40, 200, 40);
    paintLine(30, 400, 30, 40);
}

void PageClient::clear()
{
    for (size_t x=0; x<m_width; x++)
    {
        for (size_t y=0; y<m_height; y++)
        {
            size_t where = (y*m_width + x) * m_pixelWidth;
            m_bitmap[where] = 255;
            m_bitmap[where + 1] = 255;
            m_bitmap[where + 2] = 255;
        }
    }
}

void PageClient::paintLine(size_t x0, size_t y0, size_t x1, size_t y1)
{
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

    if(abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
            paintLineLow(x1, y1, x0, y0);
        else
            paintLineLow(x0, y0, x1, y1);
    }
    else
    {
        if (y0 > y1)
            paintLineHigh(x1, y1, x0, y0);
        else
            paintLineHigh(x0, y0, x1, y1);
    }
}

void PageClient::paintLineLow(size_t x0, size_t y0, size_t x1, size_t y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    
    if(dy < 0) {
        yi = -1;
        dy = -dy;
    }
    
    int D = (2 * dy) - dx;
    int y = y0;

    for(size_t x=x0; x < x1; x++) {
        size_t where = (y*m_width + x) * m_pixelWidth;
        m_bitmap[where] = 255;
        m_bitmap[where + 1] = 0;
        m_bitmap[where + 2] = 0;

        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        }
        else {
            D = D + 2*dy;
        }
    }
}

void PageClient::paintLineHigh(size_t x0, size_t y0, size_t x1, size_t y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    
    if(dx < 0) {
        xi = -1;
        dx = -dx;
    }
    
    int D = (2 * dx) - dy;
    int x = x0;

    for(size_t y=y0; y < y1; y++) {
        size_t where = (y*m_width + x) * m_pixelWidth;
        m_bitmap[where] = 255;
        m_bitmap[where + 1] = 0;
        m_bitmap[where + 2] = 0;

        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        }
        else {
            D = D + 2*dx;
        }
    }
}
