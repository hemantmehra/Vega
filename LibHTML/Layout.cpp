#include <sstream>
#include <iostream>
#include <vector>
#include <LibHTML/Layout.h>

LayoutText::LayoutText(std::string text) : m_text(text)
{
}

void LayoutText::render(Painter *painter, Point p, size_t width)
{
    size_t height = painter->get_font()->height();
#ifdef LAYOUT_DEBUG
    size_t width = painter->get_font()->width(m_text);
    painter->draw_rect(p, {width, height});
#endif

    std::vector<std::string> words, lines;
    std::istringstream iss(m_text);
    std::string s;
    while ( getline( iss, s, ' ' ) ) {
        words.push_back(s);
    }

    size_t curr_len = 0;
    std::string curr_line = "";
    for (auto word: words)
    {
        size_t word_width = painter->get_font()->width(word + " ");

        if (curr_len + word_width > width)
        {
            lines.push_back(curr_line);
            curr_line = word + " ";
            curr_len = word_width;
        }
        else
        {
            curr_len += word_width;
            curr_line += word + " ";
        }
    }
    lines.push_back(curr_line);
    size_t curr_y = p.y;
    for (auto line: lines)
    {
        painter->draw_text(line, p.x, curr_y);
        curr_y += height + 5;
    }
}
