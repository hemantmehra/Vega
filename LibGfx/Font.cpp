#include <fstream>
#include <filesystem>
#include <LibGfx/Font.h>

Font::Font()
{
    auto filename = "Katica10.font";
    std::filesystem::path p{filename};
    size_t size = std::filesystem::file_size(p);

    char *m_data = (char *) malloc(size);
    std::ifstream in(filename, std::ios::binary);
    in.read(m_data, size);
    m_header = reinterpret_cast<const FontFileHeader*>(m_data);
    m_rows = const_cast<unsigned*>((const unsigned*)(m_data + sizeof(FontFileHeader)));
    size_t m_bytes_per_glyph = sizeof(unsigned) * m_header->glyph_height;
    m_widths = (uint8_t*)(m_rows) + 256 * m_bytes_per_glyph;
}

Font::~Font()
{
    free(m_data);
}

uint8_t Font::glyph_width() {return m_header->glyph_width; }
uint8_t Font::glyph_height() {return m_header->glyph_height; }
uint8_t Font::type() {return m_header->type; }
uint8_t Font::is_variable_width() {return m_header->is_variable_width; }
uint8_t Font::glyph_spacing() {return m_header->glyph_spacing; }
size_t Font::bytes_per_glyph() { return m_bytes_per_glyph; };
size_t Font::char_width(uint8_t ch) { return m_widths[ch]; }

unsigned int *Font::get_bitmap(uint8_t ch)
{
    auto r = &m_rows[(u_int8_t)ch * m_header->glyph_height];
    return r;
}
