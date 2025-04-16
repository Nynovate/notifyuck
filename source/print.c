#include "../include/notifyuck.hpp"

int	print(const char *str)
{
	if (!str)
		return (0);
	return ((int) write(STDOUT_FILENO, str, strlen(str)));
}
