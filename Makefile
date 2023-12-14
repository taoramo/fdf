NAME = fdf
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -o2fast
LIBMLX = ./MLX42
HEADERS = -I ./include -I $(LIBMLX)/include
LIBS = $(MLX) $(LIBFT)
MLX = $(LIBMLX)/build/libmlx42.a -Iinclude -lglfw
SRCS = draw_lines.c fdf.c matrix.c matrix2.c parse.c pipeline.c t_utils.c vertexutils.c vertexutils2.c vertexutils3.c ft_hexstr_to_int.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(LIBFT):
	make -C ./libft/

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx
