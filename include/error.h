#ifndef ERROR_H
# define ERROR_H

typedef enum e_err_type
{
	E_NOPE,
	E_MLX,
	E_MEM,
	E_PARSER
}	t_err_type;

# define ERR_ARG_COUNT "Wrong argument number!"
# define ERR_INPUT_FORMAT "Wrong input format!"
# define ERR_FILE_OPEN "Open failed!"
# define ERR_CAM_SETUP "Wrong camera setup!"
# define ERR_FOV_RANGE "Wrong horizontal field of view! Range:[0,180]"
# define ERR_LIGHT_SETUP "Wrong light setup!"
# define ERR_LIGHT_BRIGHT "Wrong light brightness ratio! Range:[0.0,1.0]"
# define ERR_SPHERE_DIAM "Invalid sphere diameter! Range:[0.0, DBL_MAX]"
# define ERR_CYL_DIAM "Invalid cylinder diameter! Range:[0.0, DBL_MAX]"
# define ERR_CYL_HEIGHT "Invalid cylinder height! Range:[0.0, DBL_MAX]"
# define ERR_CONE_DIAM "Invalid cone diameter! Range:[0.0, DBL_MAX]"
# define ERR_CONE_HEIGHT "Invalid cone height! Range:[0.0, DBL_MAX]"
# define ERR_ZERO_VECTOR "Direction can't be zero vector"
# define ERR_TEXTURE_FORMAT "Wrong texture format!"
# define ERR_BUMP_FORMAT "Wrong bump map format!"
# define ERR_SHINE_RANGE "Wrong shine value! Range:[0,INT_MAX]"
# define ERR_REFLECT_RANGE "Wrong reflection value! Range:[0.0,1.0]"
# define ERR_DIR_INPUT "Wrong direction input!"
# define ERR_DIR_NOT_NORM "Direction is not normalized!"
//# define ERR_FLOAT_NO_DIGIT "Invalid float! No digits found"
//# define ERR_FLOAT_MULTI_DOT "Invalid float! Multiple dots"
//# define ERR_INVALID_INT "Invalid integer!"
# define ERR_VEC_FORMAT "Wrong vector format!"
# define ERR_VEC_VALUE "Wrong vector value!"
# define ERR_COLOR_FORMAT "Wrong color format!"
# define ERR_AMBIENT_SETUP "Wrong ambient setup!"
# define ERR_AMBIENT_RATIO "Wrong ambient lighting ratio! Range:[0.0, 1.0]"


#endif