# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyobicho <hyobicho@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 17:12:07 by yunjcho           #+#    #+#              #
#    Updated: 2023/07/02 21:55:29 by hyobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
GNL_SRC = gnl/get_next_line.c gnl/get_next_line_utils.c
SRCS = main.c \
	   deque.c deque_utils.c \
	   validation1.c validation2.c validation3.c \
	   utils1.c utils2.c matrix.c \
	   paint.c image1.c image2.c
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