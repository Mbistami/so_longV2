NAME=so_long
SRC=so_long_assets_utils.c\
	so_long_draw_utils.c\
	so_long_extra_utils.c\
	so_long_handlers_utils.c\
	so_long_moves_utils.c\
	so_long_parsing_utils.c\
	so_long_utils.c\
	so_long_tools.c\
	so_long.c\
	./get_next_line/get_next_line_utils.c\
	./get_next_line/get_next_line.c
SRCB=so_long_assets_utils_bonus.c\
	so_long_draw_utils_bonus.c\
	so_long_extra_utils_bonus.c\
	so_long_handlers_utils_bonus.c\
	so_long_moves_utils_bonus.c\
	so_long_parsing_utils_bonus.c\
	so_long_utils_bonus.c\
	so_long_tools_bonus.c\
	so_long_bonus.c\
	./get_next_line/get_next_line_utils.c\
	./get_next_line/get_next_line.c
CC=gcc
MLX_FLAGS=-lmlx -framework AppKit -framework OpenGL
FLAGS=-Wall -Werror -Wextra

all:
	@echo Building game...
	@$(CC) $(SRC) $(MLX_FLAGS) $(FLAGS) -o $(NAME)
	@echo Built Successfully!
	@echo Start your game by using
	@echo ./$(NAME) ./maps/[map_name].ber
	
bonus:
	@echo Building game -BONUS-...
	@$(CC) $(SRCB) $(MLX_FLAGS) $(FLAGS) -o $(NAME)_bonus
	@echo Built Successfully!
	@echo Start your game by using
	@echo ./$(NAME)_bonus ./maps/[map_name]_bonus.ber
clean:
	@rm -rf $(NAME)
	@rm -rf $(NAME)_bonus
	@echo "CLEANED"

re: clean all
fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(NAME)_bonus