# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 17:12:07 by yunjcho           #+#    #+#              #
#    Updated: 2023/07/03 17:40:08 by hyobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c
SRCS = main.c image.c init.c matrix.c paint.c \
		key_hook.c key_move.c key_rotate.c minimap.c \
	   raycasting1.c raycasting2.c utils.c validation.c
OBJS = $(SRCS:.c=.o) $(GNL_SRC:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

ifdef BONUS
	OBJS = $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)
endif

all : $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft all

%.o: %.c
	$(CC) $(CFLAGS) -I mlx -I gnl -I libft -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -I gnl -L mlx -l mlx -framework OpenGL -framework AppKit -o $(NAME)

clean : 
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

bonus :
	make BONUS=1 all

re : fclean all

sanitize : 
	make SANITIZE=1 re

.PHONY: all clean fclean re libft bonus