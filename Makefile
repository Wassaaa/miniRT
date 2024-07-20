################################################################################
# COMPILATION
################################################################################
CC				=	cc
CC_STRICT		=	-Wall -Wextra -Werror
DB_FLAGS		=	-g
HEADERS			=	-I $(LIBFT_INCLUDES) -I $(INCLUDES) \
CC_FULL			=	$(CC) $(CC_STRICT) $(DB_FLAGS) $(HEADERS)

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
MLX_DEBUG		= -DDEBUG=1

################################################################################
# MANDATORY
################################################################################
NAME			=	miniRT
INCLUDES		=	./include
M_HEADERS		=	$(INCLUDES)/miniRT.h
OBJ_DIR			=	..obj
OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
SRC_DIR			=	./src
SRCS			=	main.c\
					test.c\

################################################################################
# RULES
################################################################################
vpath %.c $(SRC_DIR) $(SRC_DIR)/math

all: libmlx $(NAME)

libmlx:
	cmake $(MLX42_DIR) $(MLX_DEBUG) -B $(MLX42_DIR)/build && make -C $(MLX42_DIR)/build -j4

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(M_HEADERS)
	$(CC_FULL) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(NAME).dSYM/ obj/
	rm -rf $(MLX42_DIR)/build
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

debug:
	@echo "OBJECTS: $(OBJECTS)"
	@echo "SRC_DIR: $(SRC_DIR)"
	@echo "SRCS: $(SRCS)"
	@echo "OBJ_DIR: $(OBJ_DIR)"
################################################################################
# NORM
################################################################################
norm:
	norminette . | grep -v "OK!" || true

norm2:
	norminette .

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