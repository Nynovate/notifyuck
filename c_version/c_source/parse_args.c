#include "../include/notifyuck.hpp"

bool	parse_args(s_rules *__RULES, int argc, char *argv[])
{
	int	pos = 1;

	while (pos < argc)
	{
		if (!strncmp(argv[pos], "-u", 3) || !strncmp(argv[pos], "--usage", 8))
			output_usage();
		else if (!strncmp(argv[pos], "-h", 3) || !strncmp(argv[pos], "--help", 7))
			output_help();
		else if (!strncmp(argv[pos], "-ts", 4) || !strncmp(argv[pos], "--template-string", 18))
		{
			if (pos == argc - 1 || argv[pos + 1][0] == '-')
			{
				error("The user didn't give any string to process for the template string [OPTIONS].\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			__RULES->__ARG_TEMPLATE = argv[pos + 1];
			pos++;
		}
		else if (!strncmp(argv[pos], "-te", 4) || !strncmp(argv[pos], "--template-empty", 17))
		{
			if (pos == argc - 1 || argv[pos + 1][0] == '-')
			{
				error("The user didn't give a string template for the template empty [OPTIONS].\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			__RULES->__ARG_EMPTY_NOTIFICATION = argv[pos + 1];
			pos++;
		}
		else if (!strncmp(argv[pos], "-mn", 4) || !strncmp(argv[pos], "--max-notifications", 20))
		{
			if (pos == argc - 1)
			{
				error("The max notifications [OPTIONS] only take positive digit.\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			else if (argv[pos + 1][0] == '-')
			{
				error("The user didn't give any data for the max notifications [OPTIONS].\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			__RULES->__ARG_MAX_NOTIF = atoi(argv[pos + 1]);
			if (__RULES->__ARG_MAX_NOTIF < 0)
			{
				error("The max notifications [OPTIONS] only take positive digit.\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			else if (__RULES->__ARG_MAX_NOTIF < 3)
			{
				error("Having less than 3 notifications seems meaningless for a notification center.\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			else if (__RULES->__ARG_MAX_NOTIF > 40)
			{
				error("For performance reason, having more than 30 notifications is not recommended.\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", __ERROR_FAILURE__);
				exit(0);
			}
			pos++;
		}
		else
		{
			error("Unknown options: ", __ERROR_FAILURE__);
			write(STDERR_FILENO, argv[pos], strlen(argv[pos]));
			write(STDERR_FILENO, "\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", 128);
			exit(0);
		}
		pos++;
	}
	output("\n");
	exit(0);
	return (true);
}
