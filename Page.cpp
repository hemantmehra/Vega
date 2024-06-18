#include <Page.h>
#include <vector>

Page::Page(uint8_t *bitmap, size_t width, size_t height, size_t pixelWidth)
{
    m_painter = new Painter(bitmap, width, height, pixelWidth);
}

void Page::render()
{
    int line_space = 5;
    int font_size = 40;

    std::vector<std::string> lines;
    lines.push_back("Text Examples!");
    lines.push_back("This is a line.");
    lines.push_back("Is this a question?");

    m_painter->paint();
    // m_painter->clear();
    // m_painter->set_color(0, 0, 0);

    int y = 0;
    for (auto s: lines)
    {
        // m_painter->draw_text(s, 0, y);
        y += font_size + line_space;
    }
}
