# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obellado <obellado@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/13 12:35:54 by obellado          #+#    #+#              #
#    Updated: 2021/10/04 23:19:06 by obellado         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -O3

PTFLAGS = -lpthread

NAME = miniRT

SRCS_DIR = ./srcs

SRCS = minirt_1.c minirt_2.c parser.c parser_2.c parser_3.c parser_4.c \
vector.c vector_2.c vector_3.c utils.c rotations.c rotations_utils.c shadows.c \
re_parser.c cam_move.c create_bmp.c draw.c ft_check_plane.c ft_errors.c \
ft_free_rt.c ft_scene.c get_next_line.c get_next_line_utils.c inter_cy.c \
inter_sp_pl.c inter_sq_tr.c list_utils.c obj_move.c

SRCS_R = $(addprefix ${SRCS_DIR}/, ${SRCS})

INCLUDES = ./includes

LIBMLX = libmlx.dylib

OBJS = $(SRCS_R:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./mlx
	@cp ./mlx/libmlx.dylib .
	@$(CC) $(CFLAGS) $(PTFLAGS) $(SRCS_R) -I $(INCLUDES) $(LIBMLX) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(INCLUDES) -o $@ -c $<

bonus:
	@make -C ./mlx
	@cp ./mlx/libmlx.dylib .
	@$(CC) $(CFLAGS) $(PTFLAGS) $(SRCS_R) -I $(INCLUDES) $(LIBMLX) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make clean -C ./mlx

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBMLX)

re: fclean all

.PHONY: all clean fclean re bonus
