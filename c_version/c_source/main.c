#include "../include/notifyuck.hpp"

int	main(int argc, char *argv[], char *envp[])
{
	s_rules	__RULES = {0};
	char	__BUFFER[__INTERNAL_BUFF__] = {0};
	char	__TEMPLATE_BUFFER[__INTERNAL_BUFF__] = {0};
	s_notif	__NOTIFICATION_OBJECTS__[__MAX_NOTIF__] = {0};
	size_t	len;
	size_t	__PARSED_DATA;

	if (argc != 1)
	{
		parse_args(&__RULES, argc, argv);
		if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
			output_help();
	}
	else
	{
		fetch_bus_data(__BUFFER, envp);
		len = strlen(__BUFFER);
		if (len < 31)
			output("(label :class \"label\" :text \"No Notifications\")\n");
		else
		{
			char	*__PTR_BUFFER = __BUFFER;
			e_err	__CODE_ERROR;
		
			__PTR_BUFFER += 12;
			parse_data(__PTR_BUFFER, __NOTIFICATION_OBJECTS__, &__PARSED_DATA);
			__CODE_ERROR = fetch_template(__TEMPLATE_BUFFER);
			if (__CODE_ERROR == __OK__)
			{
				size_t	iteration = 0;
		
				output("(box :class \"box\" :orientation \"v\" :space-evenly false\n");
				while (iteration < __PARSED_DATA)
				{
					output_notifications(__TEMPLATE_BUFFER, &__NOTIFICATION_OBJECTS__[iteration]);
					iteration++;
				}
				output(")\n");
			}
		}
	}
	return (EXIT_SUCCESS);
}
