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

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	int	fd_to_store;

	fd_to_store = open("./tmp", O_CREAT | O_WRONLY, 0644);
	if (fd_to_store == -1)
		return (err("Failed to create tmp file.", ERR_TMP_FILE));
	fetch_and_store_dunstctl_history(fd_to_store, envp);
	close(fd_to_store);
	return (0);
}
