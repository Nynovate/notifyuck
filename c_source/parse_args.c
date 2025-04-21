#include "../include/notifyuck.hpp"

void	parse_args(s_rules *__RULES, int argc, char *argv[], char *__BUFFER)
{
	int	pos = 1;

	if ((argc == 2 || argc == 3) && (!strncmp(argv[1], "-gl", 4) || !strncmp(argv[1], "--gen-inline", 13)))
		translate_inline(__BUFFER, argc, argv);
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
				args_error("The user didn't give any string to process for the template string [OPTIONS].");
				exit(0);
			}
			__RULES->__ARG_TEMPLATE = argv[pos + 1];
			pos++;
		}
		else if (!strncmp(argv[pos], "-v", 3) || !strncmp(argv[pos], "--version", 10))
			output_version();
		else if (!strncmp(argv[pos], "-ft", 4) || !strncmp(argv[pos], "--file-template", 16))
		{
			if (pos == argc - 1 || argv[pos + 1][0] == '-')
			{
				args_error("The user didn't give any file to file template [OPTIONS].");
				exit(0);
			}
			__RULES->__ARG_FILE_TEMPLATE = argv[pos + 1];
			pos++;
		}
		else if (!strncmp(argv[pos], "-te", 4) || !strncmp(argv[pos], "--template-empty", 17))
		{
			if (pos == argc - 1 || argv[pos + 1][0] == '-')
			{
				args_error("The user didn't give a string template for the template empty [OPTIONS].");
				exit(0);
			}
			__RULES->__ARG_EMPTY_NOTIFICATION = argv[pos + 1];
			pos++;
		}
		else if (!strncmp(argv[pos], "-so", 4) || !strncmp(argv[pos], "--show-only", 20))
		{
			if (pos == argc - 1)
			{
				args_error("The show only N notifications [OPTIONS] only take positive digit.");
				exit(0);
			}
			else if (argv[pos + 1][0] == '-')
			{
				args_error("The user didn't give any data for the show only N notifications [OPTIONS].");
				exit(0);
			}
			__RULES->__ARG_MAX_NOTIF = atoi(argv[pos + 1]);
			if (__RULES->__ARG_MAX_NOTIF < 0)
			{
				args_error("The show only N notifications [OPTIONS] only take positive digit.");
				exit(0);
			}
			else if (__RULES->__ARG_MAX_NOTIF < 3)
			{
				args_error("Having less than 3 notifications seems meaningless for a notification center.");
				exit(0);
			}
			else if (__RULES->__ARG_MAX_NOTIF >= 20)
			{
				args_error("notifyuck is limited to 20 to show notifications at maximum.");
				exit(0);
			}
			pos++;
		}
		else
		{
			error("Unknown options: ", __ERROR_FAILURE__);
			write(STDERR_FILENO, argv[pos], strlen(argv[pos]));
			args_error("");
			exit(0);
		}
		pos++;
	}
}
