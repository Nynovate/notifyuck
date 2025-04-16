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

static void	extract_data(char *main_buffer, s_notif *data, ssize_t total_length)
{
	int	index;
	char	*buffer = main_buffer;

	(void) total_length;
	index = 0;
	buffer += 43;
	while (TRUE)
	{
		data[index].valid = TRUE;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].body = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].message = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].summary = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].appname = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].category = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].default_action_name = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].icon_path = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].id = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].timestamp = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].timeout = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].progress = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].urgency = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].stack_tag = buffer;
		buffer += 11;

		buffer = strnstr(buffer, "\"data\" : ", 256);
		data[index].urls = buffer;
		buffer += 11;

		if (strnstr(buffer, "\"data\" : ", 64) == NULL)
			break ;
		else
			index++;
	}
	int	iteration = 0;

	/*write(STDOUT_FILENO, data[0].body, 64);*/
	while (data[iteration].valid == TRUE)
	{
		print_value(data[iteration].body);
		print_value(data[iteration].message);
		print_value(data[iteration].summary);
		print_value(data[iteration].appname);
		print_value(data[iteration].category);
		print_value(data[iteration].default_action_name);
		print_value(data[iteration].icon_path);
		print_value(data[iteration].id);
		print_value(data[iteration].timestamp);
		print_value(data[iteration].timeout);
		print_value(data[iteration].progress);
		print_value(data[iteration].urgency);
		print_value(data[iteration].stack_tag);
		print_value(data[iteration].urls);
		write(STDOUT_FILENO, "\n", 1);
		iteration++;
	}
}

void	fast_fetch_data(char *buffer, int fd_to_fetch, s_notif *data)
{
	ssize_t	nread;

	nread = read(fd_to_fetch, buffer, BUFF_SIZE);
	if (nread == -1)
		exit(err("An error occured while fetching the data.\n", ERR_FETCHING));
	buffer[nread] = '\0';
	if (nread == 44)
		print("No Notifications\n");
	else
		extract_data(buffer, data, nread);
}
