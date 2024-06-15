#include <cmath>
#include <LibGfx/Painter.h>
#include <iostream>

Painter::Painter(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
    : m_bitmap(bitmap), m_width(width), m_height(height), m_pixelWidth(pixelWidth)
{
    m_font2 = new Font2(100);
}

void Painter::paint()
{
    clear();
    draw_line(30, 40, 200, 40);
    draw_line(200, 40, 200, 400);
    draw_line(200, 400, 30, 400);
    draw_line(30, 400, 30, 40);
    draw_string("Hello World!", 100, 100);

    draw_char2('A', 500, 500);
}

void Painter::clear()
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

void Painter::draw_line(size_t x0, size_t y0, size_t x1, size_t y1)
{
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

    if(abs((int)(y1 - y0)) < abs((int)(x1 - x0)))
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

void Painter::paintLineLow(size_t x0, size_t y0, size_t x1, size_t y1)
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

void Painter::paintLineHigh(size_t x0, size_t y0, size_t x1, size_t y1)
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

void Painter::draw_char(uint8_t ch, size_t x, size_t y)
{
    auto bitmap = m_font.get_bitmap(ch);
    for (size_t i = 0; i < m_font.glyph_height(); i++)
    {
        for (size_t j = 0; j < m_font.char_width(ch); j++)
        {
            if (bitmap[i] & (1 << j))
            {
                size_t where = ((y + i)*m_width + (x + j)) * m_pixelWidth;
                m_bitmap[where] = 255;
                m_bitmap[where + 1] = 0;
                m_bitmap[where + 2] = 0;
            }
        }
    }
}

void Painter::draw_char2(char ch, size_t x, size_t y)
{
    m_font2->load_char(ch);
    auto height = m_font2->get_bitmap_rows();
    auto width =  m_font2->get_bitmap_width();
    unsigned char *bitmap = m_font2->get_bitmap();

    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
                std::cout << (int) bitmap[j + width + i] << " ";
            if (bitmap[j + width + i])
            {
                size_t where = ((y + i)*m_width + (x + j)) * m_pixelWidth; 
                m_bitmap[where] = bitmap[j + width + i];
                m_bitmap[where + 1] = 0;
                m_bitmap[where + 2] = 0;
            }
        }
            std::cout << "\n";
    }

}

void Painter::draw_string(std::string s, size_t x, size_t y)
{
    size_t i = x;
    size_t j = y;
    for (char ch : s)
    {
        draw_char(ch, i, j);
        i += m_font.char_width(ch) + 1;
    }
}
