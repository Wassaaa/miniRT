#include <miniRT.h>

t_color	color_create(double r, double g, double b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color	color_from_int(int r, int g, int b)
{
	return (color_create(r / 255.0, g / 255.0, b / 255.0));
}

t_color	color_from_hex(unsigned int hex)
{
	t_color	color;

	color.r = ((hex >> 24) & 0xFF) / 255.0;
	color.g = ((hex >> 16) & 0xFF) / 255.0;
	color.b = ((hex >> 8) & 0xFF) / 255.0;
	return (color);
}

int	color_to_int(t_color c)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (int)(c.r * 255.0);
	g = (int)(c.g * 255.0);
	b = (int)(c.b * 255.0);
	a = 255;

	r = clampi(r, 0, 255);
	g = clampi(g, 0, 255);
	b = clampi(b, 0, 255);

	return (r << 24 | g << 16 | b << 8 | a);
}
