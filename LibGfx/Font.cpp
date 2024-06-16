#include <iostream>
#include <AB/Assert.h>
#include <LibGfx/Font.h>
#include "Font.h"

#define CHECK(x) ASSERT(x == 0)

Font::Font(int height)
{
    m_error = FT_Init_FreeType( &m_font_library );
    CHECK(m_error);

    m_error = FT_New_Face( m_font_library, "/usr/share/fonts/truetype/lato/Lato-Regular.ttf", 0, &m_face );
    CHECK(m_error);

    m_height = height;
    m_error = FT_Set_Pixel_Sizes(m_face, 0, m_height);
    CHECK(m_error);

    m_slot = m_face->glyph;
    
    m_angle = 0;
    m_matrix.xx = (FT_Fixed)( cos( m_angle ) * 0x10000L );
    m_matrix.xy = (FT_Fixed)(-sin( m_angle ) * 0x10000L );
    m_matrix.yx = (FT_Fixed)( sin( m_angle ) * 0x10000L );
    m_matrix.yy = (FT_Fixed)( cos( m_angle ) * 0x10000L );

    // m_pen.x = 300 * 64;
    // m_pen.y = ( m_target_height - 200 ) * 64;
    m_pen.x = 0;
    m_pen.y = 0;
}

Font::~Font()
{
    FT_Done_Face(m_face);
}

void Font::load_char(char ch)
{
    // FT_Set_Transform( m_face, &m_matrix, &m_pen );

    m_error = FT_Load_Char(m_face, ch, FT_LOAD_RENDER);
    if (m_error)
    {
        std::cout << "Error Loading char!" << "\n";
        exit(0);
    }
    // std::cout << "BITMAP LEFT " << m_slot->bitmap_left << '\n';
    // std::cout << "BITMAP TOP " << m_slot->bitmap_top << '\n';
}

void Font::advance_pen()
{
    m_pen.x += m_slot->advance.x;
    m_pen.y += m_slot->advance.y;
}

int Font::get_bitmap_rows()
{
    return m_slot->bitmap.rows;
}

int Font::get_bitmap_width()
{
    return m_slot->bitmap.width;
}

int Font::get_bitmap_pitch()
{
    return m_slot->bitmap.pitch;
}

int Font::get_advance()
{
    return m_face->glyph->metrics.horiAdvance / 64;
}

int Font::get_XOff()
{
    int bbox_ymax = m_face->bbox.yMax / 64;
    int glyph_width = m_face->glyph->metrics.width / 64;
    int advance = m_face->glyph->metrics.horiAdvance / 64;
    int x_off = (advance - glyph_width) / 2;
    return x_off;
}

int Font::get_YOff()
{
    int bbox_ymax = m_face->bbox.yMax / 64;
    int y_off = bbox_ymax - m_face->glyph->metrics.horiBearingY / 64;
    return y_off;
}

int Font::get_bbox_ymax()
{
    return m_face->bbox.yMax / 64;
}

unsigned char *Font::get_bitmap()
{
    return m_slot->bitmap.buffer;
}

int Font::get_font_height()
{
    return (m_face->size->metrics.ascender - m_face->size->metrics.descender) >> 6;
}

int Font::get_font_ascender()
{
    return (m_face->size->metrics.ascender) >> 6;
}

// void Font::load_text(std::string text)
// {
//     for ( int n = 0; n < text.size(); n++ )
//     {
//         /* set transformation */
//         FT_Set_Transform( m_face, &m_matrix, &m_pen );

//         /* load glyph image into the slot (erase previous one) */
//         m_error = FT_Load_Char( m_face, text[n], FT_LOAD_RENDER );
//         if ( m_error )
//         continue;                 /* ignore m_s */

//         /* now, draw to our target surface (convert position) */
//         draw_bitmap( &m_slot->bitmap,
//                     m_slot->bitmap_left,
//                     m_target_height - m_slot->bitmap_top );

//         /* increment pen position */
//         m_pen.x += m_slot->advance.x;
//         m_pen.y += m_slot->advance.y;
//     }
// }

// void Font::draw_bitmap( FT_Bitmap*  bitmap,
//              FT_Int      x,
//              FT_Int      y)
// {
//   FT_Int  i, j, p, q;
//   FT_Int  x_max = x + bitmap->width;
//   FT_Int  y_max = y + bitmap->rows;


//   /* for simplicity, we assume that `bitmap->pixel_mode' */
//   /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

//   for ( i = x, p = 0; i < x_max; i++, p++ )
//   {
//     for ( j = y, q = 0; j < y_max; j++, q++ )
//     {
//       if ( i < 0      || j < 0       ||
//            i >= WIDTH || j >= HEIGHT )
//         continue;

//       image[j][i] |= bitmap->buffer[q * bitmap->width + p];
//     }
//   }
// }
