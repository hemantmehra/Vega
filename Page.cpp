#include <Page.h>
#include <vector>
#include <LibHTML/Layout.h>

Page::Page(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
    : m_width(width), m_height(height)
{
    m_painter = new Painter(bitmap, width, height, pixelWidth);
}

void Page::render()
{
    m_painter->clear();
    m_painter->set_color(0, 0, 0);

    LayoutText *layout1 = new LayoutText("Title 1");
    LayoutText *layout2 = new LayoutText("Sub Heading 1 Sub Heading 2 Sub Heading 3 Sub Heading 4 Sub Heading 5");

    layout1->render(m_painter, {0, 0}, m_width);
    size_t height = m_painter->get_font()->height();

    layout2->render(m_painter, {0, height + 5}, m_width);
}
