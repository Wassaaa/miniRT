#ifndef COLORS_H
# define COLORS_H
//remove macro
# define RGBA(hex, alpha) (t_rgba){(hex >> 24) & 0xFF, (hex >> 16) & 0xFF, (hex >> 8) & 0xFF, alpha * 0xFF}

// Basic colors
# define COLOR_BLACK   0x000000FF
# define COLOR_WHITE   0xFFFFFFFF
# define COLOR_RED     0xFF0000FF
# define COLOR_GREEN   0x00FF00FF
# define COLOR_BLUE    0x0000FFFF

// Mixed colors
# define COLOR_YELLOW  0xFFFF00FF
# define COLOR_MAGENTA 0xFF00FFFF
# define COLOR_CYAN    0x00FFFFFF

// Shades
# define COLOR_GRAY    0x808080FF
# define COLOR_DARKGRAY 0x404040FF
# define COLOR_LIGHTGRAY 0xC0C0C0FF

// Additional colors
# define COLOR_ORANGE  0xFF8000FF
# define COLOR_PURPLE  0x8000FFFF
# define COLOR_LIME    0x00FF80FF
# define COLOR_PINK    0xFFC0CBFF
# define COLOR_BROWN   0xA52A2AFF
# define COLOR_NAVY    0x000080FF
# define COLOR_TEAL    0x008080FF
# define COLOR_OLIVE   0x808000FF
# define COLOR_MAROON  0x800000FF

// Pastel colors
# define COLOR_PASTEL_BLUE    0xAEC6CFFF
# define COLOR_PASTEL_GREEN   0x77DD77FF
# define COLOR_PASTEL_YELLOW  0xFDFD96FF
# define COLOR_PASTEL_PINK    0xFFB3BAFF
# define COLOR_PASTEL_PURPLE  0xB39EB5FF
# define COLOR_PASTEL_ORANGE  0xFFB347FF

// Neon colors
# define COLOR_NEON_GREEN  0x39FF14FF
# define COLOR_NEON_PINK   0xFF6EC7FF
# define COLOR_NEON_BLUE   0x00FFFFFF
# define COLOR_NEON_ORANGE 0xFF9900FF

#endif