# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pllucian <pllucian@21-school.ru>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/06 14:04:05 by pllucian          #+#    #+#              #
#    Updated: 2021/04/09 23:41:02 by pllucian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	cub3d.c get_next_line.c utils.c utils_mlx.c	save_to_bmp.c				\
		parse_file0.c parse_file1.c parse_file2.c parse_file3.c parse_file4.c	\
		raycast0.c raycast1.c raycast2.c raycast3.c raycast4.c raycast5.c		\
		raycast6.c raycast7.c

OBJS = $(SRCS:.c=.o)

INCL = cub3d.h

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

%.o:		%.c $(INCL)
			$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) -Ilibft -Imlx

$(NAME):	$(OBJS)
			make bonus -C ./libft
			make -C ./mlx
			$(CC) -o $(NAME) $(OBJS) -Llibft -Lmlx -lft -lmlx -lXext -lX11 -lm -lz

all:		$(NAME)

clean:
			make clean -C ./libft
			make clean -C ./mlx
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C ./libft
			make clean -C ./mlx
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
