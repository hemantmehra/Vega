#pragma once

#include <string>
#include <LibGfx/Painter.h>

class LayoutText
{
public:
    LayoutText(std::string text);
    void render(Painter* painter, Point p);

private:
    std::string m_text;

};
