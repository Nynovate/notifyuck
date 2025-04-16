#include "../include/notifyuck.hpp"

e_error	err(char *s, e_error error_code)
{
	if (!s)
		return (1);
	write(STDOUT_FILENO, "\033[31mERROR:\033[0m notifyuck: ", 27);
	while (*s)
		write(STDOUT_FILENO, s++, 1);
	return (error_code);
}
