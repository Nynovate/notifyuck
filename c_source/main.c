#include "../include/notifyuck.hpp"

int	main(int argc, char *argv[], char *envp[])
{
	s_rules	__RULES = {0};
	char	__BUFFER[__INTERNAL_BUFF__] = {0};
	char	__TEMPLATE_BUFFER[__INTERNAL_BUFF__] = {0};
	s_notif	__NOTIFICATION_OBJECTS__[__MAX_NOTIF__] = {0};
	size_t	len;
	ssize_t	__PARSED_DATA = 0;

	__RULES.__ARG_MAX_NOTIF = -1;
	if (argc != 1)
	{
		parse_args(&__RULES, argc, argv, __BUFFER);
		if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
			output_help();
	}
	fetch_bus_data(__BUFFER, envp);
	len = strlen(__BUFFER);
	if (len < 31)
		(__RULES.__ARG_EMPTY_NOTIFICATION == NULL) ? output("(label :class \"no_notification_label\" :text \"No notification\")\n") : (output(__RULES.__ARG_EMPTY_NOTIFICATION) && output("\n"));
	else
	{
		char	*__PTR_BUFFER = __BUFFER;
		e_err	__CODE_ERROR;
		ssize_t	iteration = 0;
	
		__PTR_BUFFER += 12;
		parse_data(__PTR_BUFFER, __NOTIFICATION_OBJECTS__, &__PARSED_DATA, __RULES.__ARG_MAX_NOTIF);
		if (__RULES.__ARG_TEMPLATE != NULL)
		{
			while (iteration < __PARSED_DATA)
			{
				output_notifications(__RULES.__ARG_TEMPLATE, &__NOTIFICATION_OBJECTS__[iteration]);
				iteration++;
				output("\n");
			}
		}
		else
		{
			__CODE_ERROR = fetch_template(__TEMPLATE_BUFFER, __RULES.__ARG_FILE_TEMPLATE);
			if (__CODE_ERROR == __OK__)
			{
				while (iteration < __PARSED_DATA)
				{
					output_notifications(__TEMPLATE_BUFFER, &__NOTIFICATION_OBJECTS__[iteration]);
					iteration++;
				}
				output("\n");
			}
		}
	}
	return (EXIT_SUCCESS);
}
