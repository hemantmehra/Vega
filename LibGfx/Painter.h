#pragma once
#include <cstdint>
#include <cstring>
#include <math.h>
#include <string>
#include <LibGfx/BitmapFont.h>
#include <LibGfx/Font.h>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Point
{
    size_t x;
    size_t y;
};

struct Rect
{
    size_t left;
    size_t top;
    size_t right;
    size_t bottom;

    Point P1() { return {left, top}; }
    Point P2() { return {right, top}; }
    Point P3() { return {right, bottom}; }
    Point P4() { return {left, bottom}; }
};

struct Size
{
    size_t width;
    size_t height;
};

class Painter
{
public:
    Painter(uint8_t* bitmap, size_t width, size_t height, size_t pixelWidth);
    void clear();
    void paint();
    void draw_line(size_t x0, size_t y0, size_t x1, size_t y1);
    void draw_line(Point a, Point b);
    void draw_char(uint8_t ch, size_t x, size_t y);
    void draw_string(std::string s, size_t x, size_t y);
    void draw_char2(char ch, size_t x, size_t y);
    void draw_text(std::string s, size_t x, size_t y);
    void draw_rect(Rect rect);
    void draw_rect(Point point, Size size);
    void set_color(uint8_t r, uint8_t g, uint8_t b);
    void set_font(Font* font);
    Font* get_font();

private:
    void paintLineLow(size_t x0, size_t y0, size_t x1, size_t y1);
    void paintLineHigh(size_t x0, size_t y0, size_t x1, size_t y1);

    uint8_t *m_bitmap;
    size_t m_width;
    size_t m_height;
    size_t m_pixelWidth;
    BitmapFont m_bitmap_font;
    Font* m_font;
    Color m_color;
    size_t m_last_drawn_text_length;
};
