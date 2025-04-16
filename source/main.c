#include "../include/notifyuck.hpp"

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	int		fd_to_store;
	FILE	*stream;

	fd_to_store = open("./tmp", O_CREAT | O_WRONLY, 0644);
	if (fd_to_store == -1)
		return (err("Failed to create tmp file.", ERR_TMP_FILE));
	fetch_and_store_dunstctl_history(fd_to_store, envp);
	close(fd_to_store);

	stream = fopen("./tmp", "r");
	extract_data_from_fetch(stream);
	fclose(stream);

	unlink("./tmp");
	return (0);
}
