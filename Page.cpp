#include <Page.h>
#include <vector>
#include <LibHTML/Layout.h>

Page::Page(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
{
    m_painter = new Painter(bitmap, width, height, pixelWidth);
}

void Page::render()
{
    m_painter->clear();
    m_painter->set_color(0, 0, 0);

    LayoutText *layout1 = new LayoutText("Title 1");
    LayoutText *layout2 = new LayoutText("Sub Heading 2");

    layout1->render(m_painter, {0, 0});
    size_t height = m_painter->get_font()->height();

    layout2->render(m_painter, {0, height + 5});
}
