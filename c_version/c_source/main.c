#include "../include/notifyuck.hpp"

int	main(int argc, char *argv[], char *envp[])
{
	char	__BUFFER[__INTERNAL_BUFF__] = {0};
	char	__TEMPLATE_BUFFER[__INTERNAL_BUFF__] = {0};
	s_notif	__NOTIFICATION_OBJECTS__[__MAX_NOTIF__] = {0};
	size_t	len;

	(void)argc;
	(void)argv;
	(void)__NOTIFICATION_OBJECTS__;

	fetch_bus_data(__BUFFER, envp);
	len = strlen(__BUFFER);
	if (len < 13)
		output("No notifications\n");
	else
	{
		char	*__PTR_BUFFER = __BUFFER;
		e_err	__CODE_ERROR;

		__PTR_BUFFER += 12;
		parse_data(__PTR_BUFFER, __NOTIFICATION_OBJECTS__);
		fetch_template(__TEMPLATE_BUFFER);
		if (__CODE_ERROR == __OK__)
		{
			/*write(STDOUT_FILENO, __TEMPLATE_BUFFER, strlen(__TEMPLATE_BUFFER));*/
		}
	}

	return (EXIT_SUCCESS);
}
