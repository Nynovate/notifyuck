NAME = notifyuck
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g

C_SOURCE = ./c_source/main.c \
		   ./c_source/output.c \
		   ./c_source/fetch_bus_data.c \
		   ./c_source/parse_data.c \
		   ./c_source/fetch_template.c \
		   ./c_source/parse_args.c

C_OBJECT = ${C_SOURCE:.c=.o}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: ${NAME}

${NAME}: ${C_OBJECT}
	${CC} ${CFLAGS} ${C_OBJECT} -o ${NAME} -lbsd

clean:
	rm -f ${C_OBJECT}

fclean: clean
	rm -f ${NAME}

re: clean all

.PHONY: all fclean clean re
