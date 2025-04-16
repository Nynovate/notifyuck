#include "../include/notifyuck.hpp"

int	print(const char *str)
{
	if (!str)
		return (0);
	return ((int) write(STDOUT_FILENO, str, strlen(str)));
}

int	print_nbytes(const char *str, unsigned int bytes)
{
	if (!str)
		return (0);
	return (write(STDOUT_FILENO, str, bytes));
}
