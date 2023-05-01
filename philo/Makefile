SRCS	= philo.c \
		philo_routine.c \
		philo_parse_params.c \
		utils.c \
		utils2.c
OBJS	= ${SRCS:.c=.o}
NAME	= philo
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -I.
RM		= rm -f

all: ${NAME}

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re