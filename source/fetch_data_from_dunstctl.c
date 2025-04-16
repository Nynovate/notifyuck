#include "../include/notifyuck.hpp"

bool	fetch_and_store_dunstctl_history(int fd_to_store, char *envp[])
{
	int	child_pid;
	int	child_status;

	child_pid = fork();
	if (child_pid == -1)
		exit(err("An error occured during the forking process\n", ERR_FORKING));
	else if (child_pid == 0)
	{
		dup2(fd_to_store, STDOUT_FILENO);
		close(fd_to_store);
		execve("/usr/bin/dunstctl", (char *[]){"/usr/bin/dunstctl", "history", NULL}, envp);
		exit(err("The child process failed for some reasons, dunstctl may not be installed correctly.\n", ERR_CHILD_FAILURE));
	}
	else
		wait(&child_status);
	if (child_status != 0)
	{
		err("Could not fetch the history from dunstctl.\n", ERR_CHILD_FAILURE);
		return (FALSE);
	}
	return (TRUE);
}

static void	skip_first_five_lines(char *line, size_t *size, FILE *stream)
{
	int		iteration;

	iteration = 0;
	while (iteration++ < 5)
		getline(&line, size, stream);
	free(line);
}

static void	extract_data(char *buffer, s_notif *data)
{

}

void	fast_fetch_data(char *buffer, int fd_to_fetch, s_notif *data)
{
	ssize_t	nread;

	nread = read(fd_to_fetch, buffer, BUFF_SIZE);
	if (nread == -1)
		exit(err("An error occured while fetching the data.\n", ERR_FETCHING));
	buffer[nread] = '\0';
}
