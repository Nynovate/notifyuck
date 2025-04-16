#ifndef __NOTIFYUCK__
# define __NOTIFYUCK__
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	bool;

typedef enum error
{
	ERR_CHILD_FAILURE = -4,
	ERR_FORKING,
	ERR_TMP_FILE,
	NULL_ARGS
}	e_error;

e_error	err(char *s, e_error error_code);
int		print(const char *str);
bool	fetch_and_store_dunstctl_history(int fd_to_store, char *envp[]);
void	extract_data_from_fetch(FILE *stream);

#endif
