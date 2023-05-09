# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yun <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/02 12:34:52 by yun               #+#    #+#              #
#    Updated: 2020/10/17 16:31:51 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS += src/raycasting.c
SRCS += src/verif_map.c
SRCS +=	src/get_next_line.c
SRCS += src/get_next_line_utils.c
SRCS += src/malloc.c
SRCS += src/atoi.c
SRCS += src/key.c
SRCS += src/main.c
SRCS += src/image.c
SRCS += src/sprite.c
SRCS += src/map.c
SRCS += src/exit.c
SRCS += src/parsing.c
SRCS += src/screen.c
SRCS += src/error_parsing.c
SRCS += src/map_construc.c
SRCS += src/sprite_plus.c
SRCS += src/image_splite.c
SRCS += src/verif_map_splite.c
SRCS += src/spawn.c
SRCS += src/segfault.c
SRCS += src/verif_parsing.c
SRCS += src/gnl.c

SRCS_BONUS += src_bonus/raycasting.c
SRCS_BONUS += src_bonus/verif_map.c
SRCS_BONUS += src_bonus/get_next_line.c
SRCS_BONUS += src_bonus/get_next_line_utils.c
SRCS_BONUS += src_bonus/malloc.c
SRCS_BONUS += src_bonus/atoi.c
SRCS_BONUS += src_bonus/key_bonus.c
SRCS_BONUS += src_bonus/main.c
SRCS_BONUS += src_bonus/exit.c
SRCS_BONUS += src_bonus/parsing.c
SRCS_BONUS += src_bonus/image.c
SRCS_BONUS += src_bonus/sprite.c
SRCS_BONUS += src_bonus/map.c
SRCS_BONUS += src_bonus/screen.c
SRCS_BONUS += src_bonus/error_parsing.c
SRCS_BONUS += src_bonus/map_construc.c
SRCS_BONUS += src_bonus/sprite_plus.c
SRCS_BONUS += src_bonus/image_splite.c
SRCS_BONUS += src_bonus/verif_map_splite.c
SRCS_BONUS += src_bonus/spawn.c
SRCS_BONUS += src_bonus/segfault.c
SRCS_BONUS += src_bonus/verif_parsing.c
SRCS_BONUS += src_bonus/gnl.c

OBJS = ${SRCS:.c=.o}
OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME = cub3D

CC = clang -Wall -Wextra -Werror
LIBX = mlx/
FLAGS = -lmlx -lXext -lX11 -lm -lbsd
RM = rm -f


all:	$(NAME)

$(NAME):	$(OBJS)
		${CC} ${OBJS} -o ${NAME} -L ${LIBX} ${FLAGS}
		rm screen.bmp -f

bonus: 		$(OBJS_BONUS)
		${CC} ${OBJS_BONUS} -o cub3D_bonus -L ${LIBX} ${FLAGS}
		rm screen.bmp -f

clean:
		${RM} ${OBJS}
		${RM} ${OBJS_BONUS}
		rm screen.bmp -f
fclean:
		${RM} ${NAME}
		${RM} cub3D_bonus
		${RM} ${OBJS}
		${RM} ${OBJS_BONUS}
		rm screen.bmp -f
re: fclean all
.PHONY: all clean fclean re bonus
