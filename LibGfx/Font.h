#pragma once
#include <ft2build.h>
#include <cmath>
#include <string>
#include FT_FREETYPE_H

class Font
{
public:
    Font(std::string font_name, int target_height);
    ~Font();
    void load_char(char ch);
    void advance_pen();
    unsigned char* get_bitmap();
    int get_bitmap_rows();
    int get_bitmap_width();
    int get_bitmap_pitch();
    int get_advance();
    int get_XOff();
    int get_YOff();
    int get_bbox_ymax();
    int get_font_height();
    int get_font_ascender();
    size_t width(std::string text);
    size_t height();
    
    void load_text(std::string text);
    void draw_bitmap( FT_Bitmap*  bitmap,
             FT_Int      x,
             FT_Int      y);

private:
    FT_Library m_font_library;
    FT_Face m_face;
    FT_GlyphSlot m_slot;
    FT_Matrix m_matrix;
    FT_Vector m_pen;
    FT_Error m_error;
    double m_angle;
    int m_height;
};
