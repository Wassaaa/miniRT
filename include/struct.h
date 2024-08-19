#ifndef STRUCT_H
# define STRUCT_H

# include <libft.h>
# include <MLX42/MLX42.h> // mlx 

typedef enum e_shape_type
{
	CYLINDER,
	SPHERE,
	CONE,
	PLANE,
	LIGHT,
	SHAPE_NUM,
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

typedef struct s_lighting
{
	t_color	diffuse;
	t_color	specular;
	t_color	ambient;
}			t_lighting;

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
}	t_light;

typedef struct s_quadratic_coeffs
{
	double	a;
	double	b;
	double	c;
} t_quadratic_coeffs;

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
	double			half_height;
	double			reflectivity;
	double			shine;
	mlx_image_t		*texture;
	mlx_image_t		*bump;
	mlx_image_t		*checkerboard;
	double			half_angle;
	double			tan_half_angle;
	double			cos_theta;
	double			sin_theta;
	t_vector		u_axis;
	t_vector		v_axis;
	t_aabb 			(*boxfunc)(struct s_shape *sphere);
}	t_shape;

typedef struct s_hit
{
	double		distance;
	t_shape		*shape;
	bool		hit;
	bool		inshape;
	t_vector	normal;
	t_vector	normal_pre_perturb;
	t_vector	hit_point;
	t_ray		*ray;
	double		u;
	double		v;
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
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*ui[SHAPE_NUM];
	t_list			*shapes;
	t_list			*unbound;
	t_camera		camera;
	t_list			*lights;
	t_color			ambient;
	// t_scene			*scene;
	t_bvh			*bvh;
	t_bvh			*wireframe_bvh;
	uint32_t		width;
	uint32_t		height;
	int				bvh_node_id;
	int				wireframe;
	int				grid_size;
	int				ssaa;
	t_shape_type	target;
	unsigned int	seed;
	mlx_image_t		*checkerboard;
}	t_rtx;

#endif
