#include <cmath>
#include <LibGfx/Painter.h>
#include <iostream>

Painter::Painter(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
    : m_bitmap(bitmap), m_width(width), m_height(height), m_pixelWidth(pixelWidth)
{
    m_font = new Font("Lato-Regular", 40);
}

void Painter::set_color(uint8_t r, uint8_t g, uint8_t b)
{
    m_color.r = r;
    m_color.g = g;
    m_color.b = b;
}

void Painter::set_font(Font* font)
{
    m_font = font;
}

Font* Painter::get_font()
{
    return m_font;
}

void Painter::paint()
{
    clear();
    // draw_line(30, 40, 200, 40);
    // draw_line(200, 40, 200, 400);
    // draw_line(200, 400, 30, 400);
    // draw_line(30, 400, 30, 40);
    std::string s = "Hello World! gijq";
    std::cout << "in paint()\n";
    auto w = m_font->width(s);
    auto h = m_font->height();
    size_t x = 100;
    size_t y = 100;
    Point p = {x, y};
    Size size = {w, h};
    draw_rect(p, size);
    draw_text(s, x, y);
    // draw_line(x, y, x + w, y);
    // draw_line(x+w, y, x + w, y + h);
    // draw_line(x + w, y + h, x, y + h);
    // draw_line(x, y + h, x, y);
    // set_color(0, 0, 0);

    // int x = 0, y = 0;
    // draw_line(x, y, x + 100, y);
    // draw_line(x, y, x, y + 100);
    // m_font = new Font("Lato-Regular", 40);
    // draw_text("Hello World!", x, y);
    // x += m_last_drawn_text_length;
    // m_font = new Font("Lato-Italic", 40);
    // set_color(200, 100, 150);
    // draw_text("0x1234", x, y);
    // x += m_last_drawn_text_length;
    // m_font = new Font("Lato-Regular", 40);
    // set_color(0, 0, 0);
    // draw_text("jgyq", x, y);
    // int bbox_ymax = m_font->get_bbox_ymax();
    // draw_line(x, y + bbox_ymax, x + 200, y + bbox_ymax);
    // std::cout << m_font->get_font_height() << '\n';
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

void Painter::draw_rect(Rect rect)
{
    draw_line(rect.P1(), rect.P2());
    draw_line(rect.P2(), rect.P3());
    draw_line(rect.P3(), rect.P4());
    draw_line(rect.P4(), rect.P1());
}

void Painter::draw_rect(Point point, Size size)
{
    draw_rect({point.x, point.y, point.x + size.width, point.y + size.height});
}

void Painter::draw_line(Point a, Point b)
{
    draw_line(a.x, a.y, b.x, b.y);
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
        m_bitmap[where] = m_color.r;
        m_bitmap[where + 1] = m_color.g;
        m_bitmap[where + 2] = m_color.b;

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
        m_bitmap[where] = m_color.r;
        m_bitmap[where + 1] = m_color.g;
        m_bitmap[where + 2] = m_color.b;

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
    auto bitmap = m_bitmap_font.get_bitmap(ch);
    for (size_t i = 0; i < m_bitmap_font.glyph_height(); i++)
    {
        for (size_t j = 0; j < m_bitmap_font.char_width(ch); j++)
        {
            if (bitmap[i] & (1 << j))
            {
                size_t where = ((y + i)*m_width + (x + j)) * m_pixelWidth;
                m_bitmap[where] = m_color.r;
                m_bitmap[where + 1] = m_color.g;
                m_bitmap[where + 2] = m_color.b;
            }
        }
    }
}

void Painter::draw_char2(char ch, size_t x, size_t y)
{
    y += m_font->get_font_ascender() - m_font->get_bbox_ymax();
    m_font->load_char(ch);
    auto rows = m_font->get_bitmap_rows();
    auto width =  m_font->get_bitmap_width();
    auto pitch = m_font->get_bitmap_pitch();
    unsigned char *bitmap = m_font->get_bitmap();
    int x_off = m_font->get_XOff();
    int y_off = m_font->get_YOff();
    // std::cout << ch << '\n';
    // std::cout << "CHAR: " << ch << " X_OFF" << x_off << '\n';
    // std::cout << "CHAR: " << ch << " Y_OFF" << y_off << '\n';

    // draw_line(x, y + font->get_bbox_ymax() + 2, x + font->get_advance(), y + font->get_bbox_ymax() + 2);
    for (int i = 0; i < rows; i++)
    {
        int row_offset = y + i + y_off;
        for (int j = 0; j < width; j++)
        {
            unsigned char p = bitmap [i * pitch + j];
            size_t where = ((row_offset)*m_width + (x + j + x_off)) * m_pixelWidth;
            if (p) {
                m_bitmap[where] = m_color.r;
                m_bitmap[where + 1] = m_color.g;
                m_bitmap[where + 2] = m_color.b;
            }

            else {
                m_bitmap[where] = 255;
                m_bitmap[where + 1] = 255;
                m_bitmap[where + 2] = 255;
            }
        }
    }
}

void Painter::draw_string(std::string s, size_t x, size_t y)
{
    size_t i = x;
    size_t j = y;
    for (char ch : s)
    {
        draw_char(ch, i, j);
        i += m_bitmap_font.char_width(ch) + 1;
    }
}

void Painter::draw_text(std::string s, size_t x, size_t y)
{
    m_last_drawn_text_length = 0;
    size_t i = x;
    size_t j = y;
    int advance;
    for (char ch : s)
    {
        draw_char2(ch, i, j);
        advance = m_font->get_advance();
        // std::cout << advance << '\n';
        i += advance;
        m_last_drawn_text_length += (size_t) advance;
    }
}
