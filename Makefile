NAME = notifyuck
CC = c++
CFLAGS = -Wall -Werror -Wextra -g

C_SOURCE = ./cpp_source/main.cpp \
		   ./cpp_source/call_external.cpp

C_OBJECT = ${C_SOURCE:.cpp=.o}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all: ${NAME}

${NAME}: ${C_OBJECT}
	${CC} ${CFLAGS} ${C_OBJECT} -o ${NAME}

clean:
	rm -f ${C_OBJECT}

fclean: clean
	rm -f ${NAME}

re: clean all

.PHONY: all fclean clean re
