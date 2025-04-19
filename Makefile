NAME = notifyuck
CC = c++
CFLAGS = -Wall -Werror -Wextra

C_SOURCE = ./cpp_source/main.cpp \
		   ./cpp_source/call_external.cpp

C_OBJECT = ${C_SOURCE:.cpp=.o}

.cpp.o:
	${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

all: ${NAME}

# it's really important to set the program to be executable, otherwise, eww will always silently ignore the output
${NAME}: ${C_OBJECT}
	${CC} ${CFLAGS} ${C_OBJECT} -o ${NAME}

clean:
	rm -f ${C_OBJECT}

fclean: clean
	rm -f ${NAME}

re: clean all

.PHONY: all fclean clean re
