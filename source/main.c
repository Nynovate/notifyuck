#include "../include/notifyuck.hpp"

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	/*(void) envp;*/
	int		fd;
	char	main_buffer[BUFF_SIZE];
	s_notif	data[MAX_NOTIFICATION] = {0};

	fd = open("./tmp", O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (err("Failed to create tmp file.", ERR_TMP_FILE));
	fetch_and_store_dunstctl_history(fd, envp);
	close(fd);

	/*stream = fopen("./tmp", "r");*/
	/*extract_data_from_fetch(stream);*/
	/*fclose(stream);*/

	fd = open("./tmp", O_RDONLY);
	if (fd == -1)
		return (err("Failed to fetch tmp file.", ERR_FETCHING));
	fast_fetch_data(main_buffer, fd, data);
	close(fd);

	unlink("./tmp");
	return (0);
}
