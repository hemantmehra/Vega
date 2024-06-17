#include <Page.h>

Page::Page(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
{
    m_painter = new Painter(bitmap, width, height, pixelWidth);
}

void Page::render()
{
    m_painter->paint();
}
