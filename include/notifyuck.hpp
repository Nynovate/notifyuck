#ifndef __NOTIFYUCK__
# define __NOTIFYUCK__
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <bsd/string.h>
# include <sys/wait.h>
# ifndef BUFF_SIZE
#  define BUFF_SIZE 98304
# endif
# ifndef MAX_NOTIFICATION
#  define MAX_NOTIFICATION 20
# endif

typedef enum e_bool
{
	FALSE,
	TRUE
}	bool;

typedef enum error
{
	ERR_FETCHING = -5,
	ERR_CHILD_FAILURE,
	ERR_FORKING,
	ERR_TMP_FILE,
	NULL_ARGS
}	e_error;

typedef struct notif
{
	bool	valid;
	char	*body;
	char	*message;
	char	*summary;
	char	*appname;
	char	*category;
	char	*default_action_name;
	char	*icon_path;
	char	*id;
	char	*timestamp;
	char	*timeout;
	char	*progress;
	char	*urgency;
	char	*stack_tag;
	char	*urls;
}			s_notif;

e_error	err(char *s, e_error error_code);
int		print(const char *str);
int		print_nbytes(const char *str, unsigned int bytes);
bool	fetch_and_store_dunstctl_history(int fd_to_store, char *envp[]);
void	fast_fetch_data(char *main_buffer, int fd_to_fetch, s_notif *data);

#endif
