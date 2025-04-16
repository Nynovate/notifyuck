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

void	print_value(char *str)
{
	int	len;

	if (!str)
		return ;
	len = 0;
	while (str[len] != '\n' && str[len] != '\0')
		len++;
	write(STDOUT_FILENO, str, len);
}
