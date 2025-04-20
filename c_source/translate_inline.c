#include "../include/notifyuck.hpp"

static void	translate(char *__BUFFER, ssize_t nread)
{
	ssize_t	__POS = 0;

	while (__POS < nread)
	{
		if (__BUFFER[__POS] == '\t' || __BUFFER[__POS] == '\n')
		{
			__POS += strspn(__BUFFER + __POS, "\t\n ");
			if (__BUFFER[__POS + 1] != '\n')
				write(STDOUT_FILENO, " ", 1);
			continue ;
		}
		else if (__BUFFER[__POS] == ' ')
		{
			__POS += strspn(__BUFFER + __POS, " \t\n");
			write(STDOUT_FILENO, " ", 1);
			continue ;
		}
		else if (__BUFFER[__POS] == '\"')
			write(STDOUT_FILENO, "\\\\\"", 3);
		else if (__BUFFER[__POS] == '\'')
			write(STDOUT_FILENO, "\\\'", 2);
		else
			write(STDOUT_FILENO, __BUFFER + __POS, 1);
		__POS++;
	}
}

void	translate_inline(char *__BUFFER, int argc, char *argv[])
{
	int		fd;
	ssize_t	nread;


	if (argc == 2)
	{
		fd = open("template.yuck", O_RDONLY);
		if (fd == __ERROR_FAILURE__)
		{
			error("Couldn't open template.yuck for inline translation.\n", __ERROR_FAILURE__);
			exit(0);
		}
		output("-ts \\\"");
		while (true)
		{
			nread = read(fd, __BUFFER, __INTERNAL_BUFF__);
			if (nread == __ERROR_FAILURE__)
			{
				error("Can't read template.yuck, all operations are aborted.\n", __ERROR_FAILURE__);
				exit(0);
			}
			else if (nread == 0)
				break ;
			translate(__BUFFER, nread);
		}
	}
	else
	{
		fd = open(argv[2], O_RDONLY);
		if (fd == __ERROR_FAILURE__)
		{
			error("Couldn't open the file you provided for inline translation.\n", __ERROR_FAILURE__);
			exit(0);
		}
		output("-ts \\\"");
		while (true)
		{
			nread = read(fd, __BUFFER, __INTERNAL_BUFF__);
			if (nread == __ERROR_FAILURE__)
			{
				error("Can't read the file you provided, all operations are aborted.\n", __ERROR_FAILURE__);
				exit(0);
			}
			else if (nread == 0)
				break ;
			translate(__BUFFER, nread);
		}

	}
	output("\\\"\n");
	exit(0);
}
