#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors

# define VV (t_vector){0, 0, 0} //dummy 0 vector for initializations

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define WORLD_UP (t_vector){0, 1, 0}

# define CACHE_SIZE 0

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_BG 0x000000FF
// test shapes
// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_PLANEF (t_vector){0, 0, 15}, (t_vector){0, 0, -1}, RGBA(COLOR_NAVY, 1)
# define TEST_PLANEB (t_vector){0, 0, -15}, (t_vector){0, 0, 1}, RGBA(COLOR_NAVY, 1)
# define TEST_PLANEU (t_vector){0, 15, 0}, (t_vector){0, -1, 0}, RGBA(COLOR_NEON_GREEN, 1)
# define TEST_PLANED (t_vector){0, -15, 0}, (t_vector){0, 1, 0}, RGBA(COLOR_NEON_GREEN, 1)
# define TEST_PLANER (t_vector){15, 0, 0}, (t_vector){-1, 0, 0}, RGBA(COLOR_NAVY, 1)
# define TEST_PLANEL (t_vector){-15, 0, 0}, (t_vector){1, 0, 0}, RGBA(COLOR_NAVY, 1)
# define TEST_CYLINDER (t_vector){0, 0, 5}, (t_vector){0, 0, 1}, 4, 6, RGBA(COLOR_NEON_PINK, 1)
# define TEST_SPHERE2 (t_vector){0, 0, 15}, 21, RGBA(COLOR_PINK, 1)
# define TEST_SPHERE (t_vector){4, 2, 5}, 4, RGBA(COLOR_BLACK, 1)
# define TEST_SPHERE4 (t_vector){-4, 2, 5}, 4, RGBA(COLOR_BLACK, 1)
# define TEST_SPHERE3 (t_vector){0, -2, 5}, 2, RGBA(COLOR_RED, 1)
//test cam
# define TEST_CAM_POS (t_vector){0, 0, -14}
# define TEST_CAM_DIR (t_vector){0, 0, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 14
# define MOVE_SPEED 3.0

//test light
# define TEST_LIGHT_BRIGHTNESS 0.7
# define TEST_LIGHT_POS (t_vector){0, 13, 0}

# define TEST_AMBIENT 0.1

typedef struct s_scene t_scene;
typedef struct s_bvh t_bvh;
typedef struct s_aabb t_aabb;
typedef struct s_cache t_cache;


typedef struct s_cache_entry
{
	int node_id;
	bool hit;
}	t_cache_entry;

typedef struct s_cache
{
	t_cache_entry entries[CACHE_SIZE];
}	t_cache;

typedef enum e_shape_type
{
	PLANE,
	SPHERE,
	CYLINDER,
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

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_vector	inv_dir;
}	t_ray;

typedef struct s_amb_light
{
	double	amb_light;
	t_rgba	color;
}	t_amb_light;

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
	t_rgba		color;
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
	t_light		light;
	t_amb_light	amb;
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
	t_rgba			color;
	t_aabb			box;
	double			height;
}	t_shape;

typedef struct s_intersection
{
	double		distance;
	t_shape		*shape;
	bool		hit;
	t_vector	normal;
	t_vector	hit_point;
}	t_intersection;

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
	t_cache		cache[CACHE_SIZE];
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


//rtx
t_rtx			*rtx(void);
t_bvh			*bvh(t_list *shapes);
bool			intersect_sphere(t_ray ray, t_shape *sphere, double* t);
void			key_hook(mlx_key_data_t keydata, void* param);
void			render_scene(void);
bool			intersect(t_shape *shape, t_ray ray, double *t);
bool			intersect_bvh(t_bvh *node, t_ray ray, t_intersection *t);
bool			intersect_aabb(t_ray ray, t_aabb box, double max_t);
int				get_pixel_color(t_ray ray, t_intersection intersection);

void			cache_init(t_cache *cache);

bool			update_hit(t_bvh *node, t_intersection *t, t_ray ray);
bool			next_branches(t_bvh *node, t_ray ray, t_intersection *t);

int				get_rgba(t_rgba color, double intensity);
t_ray			generate_ray(int x, int y);

double			light_intensity(t_intersection *t);
t_light			create_point_light(t_vector pos, double bright);
int				intersect_plane(t_ray ray, t_shape plane, double *t);
int				intersect_cylinder(t_ray ray, t_shape cylinder, double *t);

bool			check_unbound(t_ray *ray, t_intersection *t);


//testing
bool			intersect_aabb_line(t_ray ray, t_shape *line, double *t);
void			generate_aabb_lines(t_bvh *node, int depth, t_list **lines);

#endif
