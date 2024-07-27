################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror -pthread
DB_FLAGS		=	-g
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) -I $(MLX42_DIR)/include
AGGR_OPTI		=	-ffast-math -mavx2 -mfma -fno-exceptions
OPTIMIZATION	=	-Ofast -march=native -flto -fno-signed-zeros \
					-fno-trapping-math -funroll-loops \
					$(AGGR_OPTI)
CC_FULL			=	$(CC) $(CC_STRICT) $(DB_FLAGS) $(HEADERS) $(OPTIMIZATION)

################################################################################
# LIBFT
################################################################################
LIBFT_DIR		=	./lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	=	$(LIBFT_DIR)

################################################################################
# MLX
################################################################################
MLX42			= $(MLX42_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
MLX42_DIR		= ./lib/MLX42
MLX_DEBUG		= -DDEBUG=0

################################################################################
# MANDATORY
################################################################################
NAME			=	miniRT
INCLUDES		=	./include
M_HEADERS		=	$(INCLUDES)/miniRT.h $(INCLUDES)/wireframe.h
OBJ_DIR			=	./obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
SRC_DIR			=	./src
SRCS			=	main.c \
					basic_equation.c \
					quadratic_formula.c \
					game_loop.c \
					plane.c \
					cylinder.c \
					aabb_intersect.c \
					bvh.c \
					intersect_bvh.c \
					point_light.c \
					 \
					aabb_intersect_line.c \
					aabb_generate_rays.c \
					cone.c \
					aabb_boxes.c \
					color.c \
					color_utils.c \
					color_utils2.c \
					clamp.c \

################################################################################
# RULES
################################################################################
vpath %.c $(SRC_DIR) $(SRC_DIR)/wireframe $(SRC_DIR)/bvh $(SRC_DIR)/colors

all: libmlx $(NAME)

libmlx:
	cmake $(MLX42_DIR) $(MLX_DEBUG) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(LIBFT) $(MLX42) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(M_HEADERS)
	mkdir -p $(@D)
	$(CC_FULL) -c $< -o $@

$(LIBFT): libft_force
	make -C $(LIBFT_DIR)

libft_force:
	@true

clean:
	@rm -rf $(NAME).dSYM/ $(OBJECTS) $(OBJ_DIR)
	@rm -rf $(MLX42_DIR)/build
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(OBJ_DIR)
	make fclean -C $(LIBFT_DIR)

re: fclean all

################################################################################
# NORM
################################################################################
norm:
	norminette $(SRC_DIR) $(M_HEADERS) | grep -v "OK!" || true

norm2:
	norminette $(SRC_DIR) $(M_HEADERS)

################################################################################
# PROFILE
################################################################################
PROF_NAME = $(NAME)_profile
PROF_OUT = gprof_analysis.txt
GMON_OUT = gmon.out

profile: $(OBJECTS)
	$(CC_FULL) -pg $(OBJECTS) $(LIBFT) $(MLX42) -o $(PROF_NAME)
	./$(PROF_NAME)
	gprof $(NAME)_profile $(GMON_OUT) > $(PROF_OUT)

pclean:
	rm -f $(PROF_NAME) $(PROF_OUT) $(GMON_OUT)

################################################################################
# VALGRIND
################################################################################
VG = valgrind

VG_FLAGS = --leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--track-fds=yes \
	--quiet \
	--suppressions=readline.supp

VG_LOG_FLAGS = $(VG_FLAGS) \
	--log-file=$(VG_LOG) \
	--track-origins=yes \
	--verbose \
	--gen-suppressions=all

VG_LOG = valgrind_leaks.log

VG_ARGS =

vg: vg_build
	$(VG) $(VG_FLAGS) ./$(NAME) $(VG_ARGS)

vglog: vg_build
	$(VG) $(VG_LOG_FLAGS) ./$(NAME) $(VG_ARGS)

vg_build: $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(READLINE) $(LIBFT) -o $(NAME)

vglog_clean: fclean
	rm -f $(VG_LOG)

################################################################################
# PHONY
################################################################################
.PHONY: all bonus re clean fclean libft_force libmlx db vg vglog vglog_clean norm norm2

################################################################################
# Colors
################################################################################
# Black, Red, Green, Yellow, Blue, Purple, Cyan, White
BK = \033[0;30m
R = \033[0;31m
G = \033[0;32m
Y = \033[0;33m
B = \033[0;34m
P = \033[0;35m
C = \033[0;36m
W = \033[0;37m
# Bold
BKB = \033[1;30m
RB = \033[1;31m
GB = \033[1;32m
YB = \033[1;33m
BB = \033[1;34m
PB = \033[1;35m
CB = \033[1;36m
WB = \033[1;37m
# Reset Color
RC = \033[0m
