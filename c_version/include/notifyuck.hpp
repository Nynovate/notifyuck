#pragma once
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <bsd/string.h>
# include <stdbool.h>
# include <sys/wait.h>
# ifndef __INTERNAL_BUFF__
#  define __INTERNAL_BUFF__ 110592
# endif
# ifndef __MAX_NOTIF__
#  define __MAX_NOTIF__ 20
# endif

typedef enum err
{
	__ERROR_READ_TEMPLATE__ = -8,
	__ERROR_OPEN_TEMPLATE__,
	__ERROR_BUSCTL_NOT_OK__,
	__ERROR_PIPE_READING__,
	__ERROR_BUSCTL__,
	__ERROR_PIPE__,
	__ERROR_FORK__,
	__ERROR_FAILURE__,
	__OK__ = 0
}	e_err;

typedef struct notif_obj
{
	bool	__VALID_SLOT;
	char	*__BODY;
	char	*__MESSAGE;
	char	*__SUMMARY;
	char	*__APPNAME;
	char	*__CATEGORY;
	char	*__DEFAULT_ACTION_NAME;
	char	*__ICON_PATH;
	char	*__ID;
	char	*__TIMESTAMP;
	char	*__TIMEOUT;
	char	*__PROGRESS;
	char	*__URGENCY;
	char	*__STACK_TAG;
	char	*__URLS;
}			s_notif;

size_t	output(const char *str);
e_err	error(const char *str, e_err __ERROR_CODE);
bool	fetch_bus_data(char *__BUFFER, char *envp[]);
void	parse_data(char *__BUFFER, s_notif *__OBJS);
e_err	fetch_template(char *__TEMPLATE_BUFFER);
void	print_value(char *__DATA);
void	output_notifications(char *__TEMPLATE_BUFFER, s_notif *__OBJS);
