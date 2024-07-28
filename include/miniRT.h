#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors

# define VV (t_vector){0, 0, 0} //dummy 0 vector for initializations

# define WIDTH 640
# define HEIGHT 360
# define M_PI 3.14159265358979323846

# define WORLD_UP (t_vector){0, 1, 0}

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_color){0, 255, 0, 255}
# define TEST_BG 0x000000FF
// test shapes
// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_PLANEF (t_vector){0, 0, 15}, (t_vector){0, 0, -1}, RGBA(COLOR_PASTEL_PINK)
# define TEST_PLANEB (t_vector){0, 0, -45}, (t_vector){0, 0, 1}, RGBA(COLOR_PASTEL_PINK)
# define TEST_PLANEU (t_vector){0, 15, 0}, (t_vector){0, -1, 0}, RGBA(COLOR_PASTEL_PINK)
# define TEST_PLANED (t_vector){0, -15, 0}, (t_vector){0, 1, 0}, RGBA(COLOR_PASTEL_PINK)
# define TEST_PLANER (t_vector){15, 0, 0}, (t_vector){-1, 0, 0}, RGBA(COLOR_PASTEL_PINK)
# define TEST_PLANEL (t_vector){-15, 0, 0}, (t_vector){1, 0, 0}, RGBA(COLOR_PASTEL_PINK)
# define TEST_CYLINDER (t_vector){0, 0, 5}, (t_vector){0, 0, 1}, 4, 6, RGBA(COLOR_NEON_PINK)
# define TEST_SPHERE2 (t_vector){0, 0, 15}, 21, RGBA(COLOR_PINK)
# define TEST_SPHERE (t_vector){4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE4 (t_vector){-4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE3 (t_vector){0, -2, 5}, 2, RGBA(COLOR_RED)
//test cam
# define TEST_CAM_POS (t_vector){0, 1, -14}
# define TEST_CAM_DIR (t_vector){0, 0, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 14
# define MOVE_SPEED 3.0

//test light
# define TEST_LIGHT (t_vector){0, 10, 0}, RGBA(COLOR_CYAN), 1.0
# define TEST_LIGHT2 (t_vector){0, 10, 0}, RGBA(COLOR_RED), 1.0
# define TEST_LIGHT3 (t_vector){10, 10, 0}, RGBA(COLOR_GREEN), 1.0

# define TEST_AMBIENT_COL RGBA(COLOR_WHITE)
# define TEST_AMBIENT_INT 0.1

typedef struct s_scene t_scene;
typedef struct s_bvh t_bvh;
typedef struct s_aabb t_aabb;

typedef enum e_shape_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	LINE,
	WIREFRAME
}	t_shape_type;

typedef enum e_direction
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	FORWARD,
	BACK
}	t_direction;


typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}			t_color;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_vector	inv_dir;
}	t_ray;

typedef struct s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	right;
	t_vector	up;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	pos;
	t_color		color;
	double		bright;
	double		intensity;
}	t_light;

typedef struct s_quadratic_coeffs
{
	double	a;
	double	b;
	double	c;
} t_quadratic_coeffs;

typedef struct s_scene
{
	t_camera	camera;
	t_list		*lights;
	t_color		ambient;
}	t_scene;

typedef struct s_aabb
{
	t_vector min;
	t_vector max;
}	t_aabb;

typedef struct s_shape
{
	t_shape_type	type;
	t_vector		pos;
	t_vector		dir;
	double			diameter;
	double			radius;
	t_color			color;
	t_aabb			box;
	double			height;
}	t_shape;

typedef struct s_hit
{
	double		distance;
	t_shape		*shape;
	bool		hit;
	t_vector	normal;
	t_vector	hit_point;
}	t_hit;

typedef struct s_bvh
{
	int				id;
	t_aabb			box;
	struct s_bvh	*left;
	struct s_bvh	*right;
	t_shape			*shape;
}	t_bvh;

typedef struct s_rtx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_list		*shapes;
	t_list		*unbound;
	t_scene		*scene;
	t_bvh		*bvh;
	t_bvh		*wireframe_bvh;
	int			width;
	int			height;
	int			bvh_node_id;
	int			cache_hits;
	int			wireframe;
}	t_rtx;

//basic vector equation
t_vector		vector_add(t_vector a, t_vector b);
t_vector		vector_subtract(t_vector a, t_vector b);
t_vector		vector_scale(t_vector a, double scalar);
double			vector_dot(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
double			vector_length(t_vector a);
t_vector		vector_normalize(t_vector a);
double			vector_length_squared(t_vector a);
t_vector		vector_min(t_vector a, t_vector b);
t_vector		vector_max(t_vector a, t_vector b);

//clamp
int				clampi(int value, int min, int max);
double			clampd(double value, double min, double max);

//lights
t_color			get_diffuse(t_hit *hit);

void			fix_hit_normal(t_hit *hit);
//colors
int				get_pixel_color(t_ray *ray, t_hit *hit);
int				color_to_int(t_color c);
t_color			color_from_int(int r, int g, int b);
t_color			color_from_hex(unsigned int hex);
t_color			color_clamp(t_color c);
t_color			color_scale(t_color c, double scale);
t_color			color_multiply(t_color c1, t_color c2);
t_color			color_subtract(t_color c1, t_color c2);
t_color			color_add(t_color c1, t_color c2);
t_color			color_create(double r, double g, double b);

//rtx
t_rtx			*rtx(void);
bool			intersect_sphere(t_ray ray, t_shape *sphere, double* t);
void			key_hook(mlx_key_data_t keydata, void* param);
void			render_scene(void);
bool			intersect(t_shape *shape, t_ray ray, double *t);

t_ray			generate_ray(int x, int y);

int				intersect_plane(t_ray ray, t_shape plane, double *t);
int				intersect_cylinder(t_ray ray, t_shape cylinder, double *t);


//bvh
t_bvh			*bvh(t_list *shapes);
bool			intersect_bvh(t_bvh *node, t_ray ray, t_hit *hit);
bool			check_unbound(t_ray *ray, t_hit *hit);

//shapes
t_shape			*make_cone(t_vector pos, t_vector dir, double diameter, double height, t_color color);
int				intersect_cone(t_ray ray, t_shape *cone, double *t);
//axis-aligned bounding boxes
bool			intersect_aabb(t_ray ray, t_aabb box, double max_t);
t_aabb			box_sphere(t_shape sphere);
t_aabb			box_cylinder(t_shape cylinder);
t_aabb			box_line(t_shape line);
t_aabb			box_cone(t_shape *cone);



//testing
bool			intersect_aabb_line(t_ray ray, t_shape *line, double *t);
void			generate_aabb_lines(t_bvh *node, int depth, t_list **lines);

#endif
