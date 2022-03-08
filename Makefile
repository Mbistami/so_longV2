NAME=so_long.a
SRC=so_long_assets_utils.c\
	so_long_draw_utils.c\
	so_long_extra_utils.c\
	so_long_handlers_utils.c\
	so_long_moves_utils.c\
	so_long_parsing_utils.c\
	so_long_utils.c\
	so_long_tools.c\
	./get_next_line/get_next_line_utils.c\
	./get_next_line/get_next_line.c
OBJS=$(SRC:.c=.o)
OUTPUT=output
CC=gcc
MLX_FLAGS=-lmlx -framework AppKit -framework OpenGL
FLAGS=-Wall -Werror -Wextra

%.o:%.c
		gcc -c -I ./ -o $@ $< -Wall -Werror -Wextra
all:
	$(CC) main.c $(SRC) $(MLX_FLAGS) $(FLAGS) -o so_long
	
	
clean:
	@rm -rf $(OBJS)
	@echo "CLEANED"

re: clean all
fclean: clean
		rm -rf $(NAME)
um: all
	${CC} $(NAME) ${CFLAGS} main.c -o ${OUTPUT} 
	./$(OUTPUT)