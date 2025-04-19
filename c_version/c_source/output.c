#include "../include/notifyuck.hpp"

size_t	output(const char *str)
{
	if (!str)
		return (0);
	return (write(STDOUT_FILENO, str, strlen(str)));
}

e_err	error(const char *str, e_err __ERROR_CODE)
{
	if (!str)
		return (0);
	write(STDERR_FILENO, "\033[31mERROR: \033[0mnotifyuck: ", 28);
	write(STDERR_FILENO, str, strlen(str));
	return (__ERROR_CODE);
}
