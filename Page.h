#pragma once

#include <LibGfx/Painter.h>

class Page
{
public:
    Page(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth);
    ~Page() = default;

    void render();

private:
    Painter* m_painter;
    size_t m_width;
    size_t m_height;
};
