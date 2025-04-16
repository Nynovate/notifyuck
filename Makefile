NAME = notifyuck
CC = gcc
CFLAGS = -Wall -Werror -Wextra

C_SOURCE = ./source/main.c \
		   ./source/error.c \
		   ./source/print.c

C_OBJECT = ${C_SOURCE:.c=.o}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${C_OBJECT}
	${CC} ${CFLAGS} ${C_OBJECT} -o ${NAME}

clean:
	rm -f ${C_OBJECT}

fclean: clean
	rm -f ${NAME}

re: clean all

.PHONY: all fclean clean re
