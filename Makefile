# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtraiman <gtraiman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/11 16:45:54 by gtraiman          #+#    #+#              #
#    Updated: 2025/01/04 21:01:05 by gtraiman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = philo
CC          = cc
CFLAGS      = -Werror -Wall -Wextra -I . -g3

SRCS        = main.c \
              philo_utils.c \
              philo.c

OBJS        = ${SRCS:.c=.o}

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
