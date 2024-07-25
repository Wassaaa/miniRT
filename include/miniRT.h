#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors



# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define WORLD_UP (t_vector){0, 1, 0}

# define CACHE_SIZE 64

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_BG 0x000000FF
// test shapes
// # define TEST_PLANE (t_vector){4, 4, 4}, (t_vector){0, 0, 1}, (t_rgba){0, 255, 0, 255}
# define TEST_PLANE (t_vector){5, -6, 10}, (t_vector){0, 1, 0}, (t_rgba){0, 0, 255, 255}
# define TEST_CYLINDER (t_vector){0, 0, 5}, (t_vector){0, 0, 1}, 4, 6, (t_rgba){0, 255, 255, 255}
# define TEST_SPHERE (t_vector){0, 0, 5}, 4, RGBA(COLOR_CYAN, 1)
# define TEST_SPHERE2 (t_vector){4, 7, 11}, 5, RGBA(COLOR_RED, 1)
# define TEST_SPHERE3 (t_vector){-5, -6, 16}, 6, RGBA(COLOR_LIME, 1)
# define TEST_SPHERE4 (t_vector){3, 2, 16}, 9, RGBA(COLOR_MAROON, 1)
//test cam
# define TEST_CAM_POS (t_vector){0, 0, -10}
# define TEST_CAM_DIR (t_vector){0, 0, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 14
# define MOVE_SPEED 3.0

//test light
# define TEST_LIGHT_DIR (t_vector){14, 22, -25}
# define TEST_LIGHT_POS (t_vector){14, 22, -25}

# define TEST_AMBIENT 0.7

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
	CYLINDER
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

typedef struct s_shape
{
	t_shape_type	type;
	t_vector		pos;
	t_vector		dir;
	double			diameter;
	double			radius;
	double			height;
	t_rgba			color;
	t_aabb			box;
}	t_shape;

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
	t_vector	dir;
	double		bright;
	t_rgba		color;
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
}	t_shape;

typedef struct s_intersection
{
	double	distance;
	t_shape	*shape;
	bool	hit;
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
	t_scene		*scene;
	t_bvh		*bvh;
	int			width;
	int			height;
	t_cache		cache[CACHE_SIZE];
	int			bvh_node_id;
	int			cache_hits;
	int			wireframe;
}	t_rtx;

//basic vector equation
inline t_vector	vector_add(t_vector a, t_vector b);
inline t_vector	vector_subtract(t_vector a, t_vector b);
inline t_vector	vector_scale(t_vector a, double scalar);
inline double	vector_dot(t_vector a, t_vector b);
inline t_vector	vector_cross(t_vector a, t_vector b);
inline double	vector_length(t_vector a);
inline t_vector	vector_normalize(t_vector a);

//rtx
t_rtx			*rtx(void);
void			bvh(t_list *shapes);
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


//testing
void			render_scene_with_aabb(void);
#endif
