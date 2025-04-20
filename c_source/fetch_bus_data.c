#include "../include/notifyuck.hpp"

void	get_information_from_bus(char *__BUFFER, int fd)
{
	size_t	bytes = 0;
	ssize_t	nread;

	while (true)
	{
		nread = read(fd, __BUFFER + bytes, __INTERNAL_BUFF__);
		if (nread == -1)
			exit(error("parent process: Failed to read pipe\n", __ERROR_PIPE_READING__));
		else if (nread == 0)
			break ;
		bytes += nread;
	}
}

bool	fetch_bus_data(char *__BUFFER, char *envp[])
{
	int	__FD[2];
	int	dunst_pid;
	int	dunst_return_value = 0;

	if (pipe(__FD) == __ERROR_FAILURE__)
		exit(error("Failed to create a pipe, all operations are aborted\n", __ERROR_PIPE__));
	dunst_pid = fork();
	if (dunst_pid == __ERROR_FAILURE__)
		exit(error("Failed to create a fork, all operations are aborted\n", __ERROR_FORK__));
	else if (dunst_pid == 0)
	{
		setenv("DBUS_SESSION_BUS_ADDRESS", "unix:path=/run/user/1000/bus", 1);
		close(__FD[STDIN_FILENO]);
		dup2(__FD[STDOUT_FILENO], STDOUT_FILENO);
		close(__FD[STDOUT_FILENO]);
		execve(
				"/usr/bin/busctl",
				(char *[])
				{
					"/usr/bin/busctl",
					"--user",
					"--json=short",
					"call",
					"org.freedesktop.Notifications",
					"/org/freedesktop/Notifications",
					"org.dunstproject.cmd0",
					"NotificationListHistory",
					NULL
				},
				envp
		);
		exit(error("Failed to execute busctl\n", __ERROR_BUSCTL__));
	}
	else
	{
		close(__FD[STDOUT_FILENO]);
		get_information_from_bus(__BUFFER, __FD[STDIN_FILENO]);
		wait(&dunst_return_value);
		close(__FD[STDIN_FILENO]);
	}
	if (dunst_return_value != __OK__)
	{
		error("busctl returned a [NOT OK] status, all operations are aborted\n", __ERROR_BUSCTL_NOT_OK__);
		printf("\033[33m[Code Error]: \033[0m[%d]\n", dunst_return_value);
		fflush(stdout);
		exit(__ERROR_BUSCTL_NOT_OK__);
	}
	return (true);
}
