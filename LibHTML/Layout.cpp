#include <LibHTML/Layout.h>

LayoutText::LayoutText(std::string text) : m_text(text)
{
}

void LayoutText::render(Painter *painter, Point p)
{
    size_t width = painter->get_font()->width(m_text);
    size_t height = painter->get_font()->height();

    painter->draw_text(m_text, p.x, p.y);
    painter->draw_rect(p, {width, height});
}
