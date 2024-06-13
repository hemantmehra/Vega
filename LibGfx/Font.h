#pragma once
#include <cstdint>
#include <cstring>

struct FontFileHeader
{
    char magic[4];
    uint8_t glyph_width;
    uint8_t glyph_height;
    uint8_t type;
    uint8_t is_variable_width;
    uint8_t glyph_spacing;
    uint8_t unused[5];
    char name[64];
}__attribute__ ((packed));

class Font
{
public:
    Font();
    ~Font();

    uint8_t glyph_width();
    uint8_t glyph_height();
    uint8_t type();
    uint8_t is_variable_width();
    uint8_t glyph_spacing();
    size_t bytes_per_glyph();
    size_t char_width(uint8_t ch);
    unsigned int* get_bitmap(uint8_t ch);

private:
    char *m_data;
    const FontFileHeader *m_header;
    unsigned int *m_rows;
    uint8_t *m_widths; 
    size_t m_bytes_per_glyph;
};
