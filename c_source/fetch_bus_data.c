#include "../include/notifyuck.hpp"

void	get_information_from_bus(char *__BUFFER, int fd)
{
	size_t	bytes = 0;
	ssize_t	nread;

	while (true)
	{
		nread = read(fd, __BUFFER + bytes, __INTERNAL_BUFF__);
		if (nread == -1)
		{
			output("(label :markup \"<span color=\'#FF0000\'>ERROR:</span> notifyuck: CODE -> <b>__ERROR_PIPE_READING__</b>)\"");
			error("parent process: Failed to read pipe\n", __ERROR_PIPE_READING__);
			exit(0);
		}
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
	{
		output("(label :markup \"<span color=\'#FF0000\'>ERROR:</span> notifyuck: CODE -> <b>__ERROR_PIPE__</b>)\"");
		error("Failed to create a pipe, all operations are aborted\n", __ERROR_PIPE__);
		exit(0);
	}
	dunst_pid = fork();
	if (dunst_pid == __ERROR_FAILURE__)
	{
		output("(label :markup \"<span color=\'#FF0000\'>ERROR:</span> notifyuck: CODE -> <b>__ERROR_FORK__</b>)\"");
		error("Failed to create a fork, all operations are aborted\n", __ERROR_FORK__);
		exit(0);
	}
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
		output("(label :markup \"<span color=\'#FF0000\'>ERROR:</span> notifyuck: CODE -> <b>__ERROR_BUSCTL__</b>)\"");
		error("Failed to execute busctl\n", __ERROR_BUSCTL__);
		exit(0);
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
		output("(label :markup \"<span color=\'#FF0000\'>ERROR:</span> notifyuck: CODE -> <b>__ERROR_BUSCTL_NOT_OK__</b>)\"");
		error("busctl returned a [NOT OK] status, all operations are aborted\n", __ERROR_BUSCTL_NOT_OK__);
		printf("\033[33m[Code Error]: \033[0m[%d]\n", dunst_return_value);
		fflush(stdout);
		exit(0);
	}
	return (true);
}
