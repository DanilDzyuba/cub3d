.PHONY: all clean fclean re
NAME = cub3D
FLAGS = -Wall -Werror -Wextra
SOURCES_DIR = ./
SOURCES_LIST =	main.c\
				map.c\
				parser.c\
				raycaster.c\
				sprites.c\
				textures.c\
				utils.c\
				parser_utils.c\
				drawing_utils.c\
				../gnl/get_next_line.c

SOURCES = $(addprefix $(SOURCES_DIR), $(SOURCES_LIST))
OBJECTS_DIR = obj/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIR), $(OBJECTS_LIST))
HEADER = includes/cub3d.h
FRAMEWORKS = -framework OpenGL -framework AppKit
LIB = -Llibft -lft -Lminilibx -lmlx

all: $(NAME)
$(NAME): $(OBJECTS_DIR) $(OBJECTS) $(HEADER)
	make -C libft/
	make -C minilibx/
	@gcc $(FLAGS)  -o $(NAME) $(OBJECTS) $(LIB) $(FRAMEWORKS)
	@echo "$(NAME) compiled"

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
	@echo "$(NAME)'s $(OBJECTS_DIR) created"

$(OBJECTS_DIR)%.o : $(SOURCES_DIR)%.c $(HEADER)
	@gcc $(FLAGS) -c $< -o $@
	@echo "$< compiled to $@"

clean:
	@rm -rf $(OBJECTS_DIR)
	@rm -rf ./gnl/get_next_line.o
	@echo "$(NAME)'s $(OBJECTS_DIR) deleted"
	@make -C libft/ clean
	@make -C minilibx/ clean

fclean: clean
	@rm -f $(NAME)
	@echo "$(NAME) deleted"
	@make -C libft/ fclean

re:
	@$(MAKE) fclean
	@$(MAKE) all
