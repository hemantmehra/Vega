#include <iostream>
#include <AB/Assert.h>
#include <LibGfx/Font2.h>

#define CHECK(x) ASSERT(x == 0)

Font2::Font2(int target_height)
{
    m_error = FT_Init_FreeType( &m_font_library );
    CHECK(m_error);

    m_error = FT_New_Face( m_font_library, "/usr/share/fonts/truetype/lato/Lato-Regular.ttf", 0, &m_face );
    CHECK(m_error);

    m_error = FT_Set_Pixel_Sizes(m_face, 0, 20);
    CHECK(m_error);

    m_slot = m_face->glyph;

    m_angle = 0;
    m_matrix.xx = (FT_Fixed)( cos( m_angle ) * 0x10000L );
    m_matrix.xy = (FT_Fixed)(-sin( m_angle ) * 0x10000L );
    m_matrix.yx = (FT_Fixed)( sin( m_angle ) * 0x10000L );
    m_matrix.yy = (FT_Fixed)( cos( m_angle ) * 0x10000L );

    m_target_height = target_height;
    // m_pen.x = 300 * 64;
    // m_pen.y = ( m_target_height - 200 ) * 64;
    m_pen.x = 0;
    m_pen.y = 0;
}

Font2::~Font2()
{
    FT_Done_Face(m_face);
}

void Font2::load_char(char ch)
{
    FT_Set_Transform( m_face, &m_matrix, &m_pen );
    m_error = FT_Load_Char(m_face, ch, FT_LOAD_RENDER);
    if (m_error)
    {
        std::cout << "Error Loading char!" << "\n";
        exit(0);
    }
    std::cout << "BITMAP LEFT " << m_slot->bitmap_left << '\n';
    std::cout << "BITMAP TOP " << m_slot->bitmap_top << '\n';
}

void Font2::advance_pen()
{
    m_pen.x += m_slot->advance.x;
    m_pen.y += m_slot->advance.y;
}

int Font2::get_bitmap_rows()
{
    return m_slot->bitmap.rows;
}

int Font2::get_bitmap_width()
{
    return m_slot->bitmap.width;
}

int Font2::get_bitmap_pitch()
{
    return m_slot->bitmap.pitch;
}

unsigned char* Font2::get_bitmap()
{
    return m_slot->bitmap.buffer;
}

// void Font2::load_text(std::string text)
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

// void Font2::draw_bitmap( FT_Bitmap*  bitmap,
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
