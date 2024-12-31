NAME = fdf
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -o2fast
LIBMLX = ./MLX42
HEADERS = -I ./include -I $(LIBMLX)/include
LIBS = $(MLX) $(LIBFT)
MLX = $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/"
SRCS = draw_lines.c draw_lines2.c hooks.c fdf.c matrix.c parse.c parse2.c pipeline.c t_utils.c vertexutils.c vertexutils2.c ft_hexstr_to_int.c color.c color2.c transform.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) $(CFLAGS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	rm -rf $(OBJS)
	rm -rf $(LIBMLX)/build
	make clean -C ./libft/

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
