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
		__CODE_ERROR = fetch_template(__TEMPLATE_BUFFER);
		if (__CODE_ERROR == __OK__)
		{
			size_t	iteration = 0;

			output("(box :class \"box\" :orientation \"v\" :space-evenly false\n");
			while (__NOTIFICATION_OBJECTS__[iteration].__VALID_SLOT == true)
			{
				output_notifications(__TEMPLATE_BUFFER, &__NOTIFICATION_OBJECTS__[iteration]);
				iteration++;
			}
			output(")\n");
		}
	}
	return (EXIT_SUCCESS);
}
