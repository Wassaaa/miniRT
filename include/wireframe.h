#ifndef WIREFRAME_H
# define WIREFRAME_H

# include <miniRT.h>

# define MAX_DEPTH 10
# define AABB_LINE_THICKNESS 0.1


static const t_color depth_colors[MAX_DEPTH] = {
	RGBA(COLOR_GREEN),
	RGBA(COLOR_BLUE),
	RGBA(COLOR_RED),
	RGBA(COLOR_YELLOW),
	RGBA(COLOR_MAGENTA),
	RGBA(COLOR_CYAN),
	RGBA(COLOR_ORANGE),
	RGBA(COLOR_PURPLE),
	RGBA(COLOR_LIME),
	RGBA(COLOR_GRAY),
};

typedef struct s_coeff
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	e;
}	t_coeff;

#endif