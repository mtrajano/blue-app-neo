#include "glyphs.h"
unsigned int const C_icon_colors[]
 = {
  0x00000000, 
  0x00ffffff, 
};
	
unsigned char const C_icon_bitmap[] = {
0x00, 0x00, 0x80, 0x01, 0xe0, 0x07, 0xf8, 0x1f, 0xfe, 0x07, 0xf8, 0x19, 0x66, 0x1e, 0x1e, 0x1e, 
  0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1c, 0x1e, 0x18, 0x1e, 0x00, 0x1c, 0x00, 0x18, 0x00, 0x00, 0x00, 
  };

#ifdef OS_IO_SEPROXYHAL
#include "os_io_seproxyhal.h"
const bagl_icon_details_t C_icon = { GLYPH_icon_WIDTH, GLYPH_icon_HEIGHT, 1, C_icon_colors, C_icon_bitmap };
#endif // OS_IO_SEPROXYHAL
