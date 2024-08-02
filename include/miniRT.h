#ifndef MINIRT_H
# define MINIRT_H

# include <libft.h>
# include <math.h> // math
# include <stdio.h> // printf
# include <MLX42/MLX42.h> // mlx
# include <float.h>
# include <colors.h> //colors
# include <struct.h> //colors


# define VV (t_vector){0, 0, 0} //dummy 0 vector for initializationsõ

# define LINE_THICKNESS 0.45

# define WIDTH 800
# define HEIGHT 600
# define M_PI 3.14159265358979323846

# define EPSILON 1e-6
# define SCALE 100

# define WORLD_UP (t_vector){0, 1, 0}

# define AXIS_X 1
# define AXIS_Y 2
# define AXIS_Z 3

# define TEST_BG 0x000000FF

// test shapes
# define TEST_PLANEF (t_vector){0, 0, 30}, (t_vector){0, 0, -1}, RGBA(WALL_COLOR)
# define TEST_PLANEB (t_vector){0, 0, -165}, (t_vector){0, 0, 1}, RGBA(WALL_COLOR)
# define TEST_PLANEU (t_vector){0, 30, 0}, (t_vector){0, -1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANED (t_vector){0, -30, 0}, (t_vector){0, 1, 0}, RGBA(WALL_COLOR)
# define TEST_PLANER (t_vector){30, 0, 0}, (t_vector){-1, 0, 0}, RGBA(WALL_COLOR)
# define TEST_PLANEL (t_vector){-30, 0, 0}, (t_vector){1, 0, 0}, RGBA(WALL_COLOR)

# define TEST_CYLINDER1 (t_vector){-25, 0, 0}, (t_vector){1, 0, 0}, 60, 1, RGBA(WALL_COLOR)
# define TEST_CYLINDER2 (t_vector){25, 0, 0}, (t_vector){-1, 0, 0}, 60, 1, RGBA(WALL_COLOR)

# define TEST_CONE (t_vector){0, 0, 15}, (t_vector){0, 1, 0}, 12, 15, RGBA(COLOR_MAGENTA)

# define TEST_SPHERE2 (t_vector){0, 0, 15}, 21, RGBA(COLOR_PINK)
# define TEST_SPHERE (t_vector){4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE4 (t_vector){-4, 2, 5}, 4, RGBA(COLOR_BLACK)
# define TEST_SPHERE3 (t_vector){0, -2, 5}, 2, RGBA(COLOR_RED)

# define WALL_COLOR COLOR_MAROON
# define TEXT_COLOR COLOR_METALLIC_GOLD
# define LIGHT_COLOR COLOR_WARM_WHITE

# define SHINE 1000

# define REFLECT_DEPTH 100
//test cam
# define TEST_CAM_POS (t_vector){0, 0.8, -35}
# define TEST_CAM_DIR (t_vector){0, -0.2, 1}
# define TEST_FOV 80.0
# define FOV_STEP 10.0
# define MIN_FOV 10.0
# define MAX_FOV 170.0

# define PAN_AMOUNT M_PI / 24
# define MOVE_SPEED 3.0

//test light
# define TEST_LIGHT (t_vector){0, 15, -15}, RGBA(COLOR_PASTEL_BLUE), 1.0
# define TEST_LIGHT2 (t_vector){0, -7, -8}, RGBA(COLOR_PASTEL_ORANGE), 1.0
# define TEST_LIGHT3 (t_vector){10, 10, 0}, RGBA(COLOR_GREEN), 1.0

# define TEST_AMBIENT_COL RGBA(COLOR_WARM_WHITE)
# define TEST_AMBIENT_INT 0.15

typedef struct s_scene t_scene;
typedef struct s_bvh t_bvh;
typedef struct s_aabb t_aabb;

// parsing
t_vector	check_dir(t_vector dir);

//basic vector equation
t_vector	vector_add(t_vector a, t_vector b);
t_vector	vector_subtract(t_vector a, t_vector b);
t_vector	vector_scale(t_vector a, double scalar);
double		vector_dot(t_vector a, t_vector b);
t_vector	vector_cross(t_vector a, t_vector b);
double		vector_length(t_vector a);
t_vector	vector_normalize(t_vector a);
double		vector_length_squared(t_vector a);
t_vector	vector_min(t_vector a, t_vector b);
t_vector	vector_max(t_vector a, t_vector b);

//clamp
int			clampi(int value, int min, int max);
double		clampd(double value, double min, double max);

//lights
double	get_diffuse(t_hit *hit, t_vector *light_dir);

void		fix_hit_normal(t_hit *hit);
//colors
t_color			get_pixel_color(t_ray *ray, t_hit *hit, int depth);
int				color_to_int(t_color c);
t_color			color_from_int(int r, int g, int b);
t_color			color_from_hex(unsigned int hex);
t_color			color_clamp(t_color c);
t_color			color_scale(t_color c, double scale);
t_color			color_multiply(t_color c1, t_color c2);
t_color			color_subtract(t_color c1, t_color c2);
t_color			color_add(t_color c1, t_color c2);
t_color			color_create(double r, double g, double b);
t_color			color_blend(t_color c1, t_color c2, double factor);

//init
void		fix_camera(void);
void		render(void);

//rtx
void			render_multi_threaded(void);
void			render_scene(void);
t_rtx			*rtx(void);
bool			intersect_sphere(t_ray ray, t_shape *sphere, double* t);
void			key_hook(mlx_key_data_t keydata, void* param);
bool			intersect(t_shape *shape, t_ray ray, double *t);
t_color			trace_ray (t_ray *ray, int depth);

//render
t_ray			create_ray(t_vector origin, t_vector direction);

//normal
void			fix_hit_normal(t_hit *hit);

//lighting
t_lighting		calc_lighting(t_hit *hit);

t_ray		generate_ray(int x, int y);

int			intersect_plane(t_ray ray, t_shape plane, double *t);
int			intersect_cylinder(t_ray ray, t_shape cylinder, double *t);


//bvh
t_bvh		*bvh(t_list *shapes);
bool		intersect_bvh(t_bvh *node, t_ray ray, t_hit *hit);
bool		check_unbound(t_ray *ray, t_hit *hit);

//shapes
t_shape		*make_cone(t_vector pos, t_vector dir, double diameter, double height, t_color color);
int			intersect_cone(t_ray ray, t_shape *cone, double *t);
t_shape		*make_plane(t_vector pos, t_vector dir, t_color color);
t_shape		*make_cylinder(t_vector pos, t_vector dir, double diameter, double height, t_color color);

//axis-aligned bounding boxes
bool		intersect_aabb(t_ray ray, t_aabb box, double max_t);
t_aabb		box_sphere(t_shape sphere);
t_aabb		box_cylinder(t_shape cylinder);
t_aabb		box_line(t_shape line);
t_aabb		box_cone(t_shape *cone);

//uv
void		sphere_uv(t_vector point, double *u, double *v);
void		plane_uv(t_vector normal, t_vector point, double *u, double *v);
void		cylinder_uv(t_vector point, t_vector axis, double height, double *u, double *v);
void		cone_uv(t_vector point, t_vector apex, t_vector axis, double height, double *u, double *v);

//testing
void		make_aabb_line(t_list **lines, t_vector start, t_vector end, t_color color, t_shape_type type);
bool		intersect_aabb_line(t_ray ray, t_shape *line, double *t);
void		generate_aabb_lines(t_bvh *node, int depth, t_list **lines);

#endif
