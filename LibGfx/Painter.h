#pragma once
#include <cstdint>
#include <cstring>
#include <math.h>

class Painter
{
public:
    Painter(uint8_t* bitmap, size_t width, size_t height, size_t pixelWidth);
    void clear();
    void paint();
    void draw_line(size_t x0, size_t y0, size_t x1, size_t y1);

private:
    void paintLineLow(size_t x0, size_t y0, size_t x1, size_t y1);
    void paintLineHigh(size_t x0, size_t y0, size_t x1, size_t y1);

    uint8_t *m_bitmap;
    size_t m_width;
    size_t m_height;
    size_t m_pixelWidth;
};
