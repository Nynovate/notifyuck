#include "../include/notifyuck.hpp"

size_t	output(const char *str)
{
	if (!str)
		return (0);
	return (write(STDOUT_FILENO, str, strlen(str)));
}

e_err	error(const char *str, e_err __ERROR_CODE)
{
	if (!str)
		return (0);
	write(STDERR_FILENO, "\033[31mERROR: \033[0mnotifyuck: ", 28);
	write(STDERR_FILENO, str, strlen(str));
	return (__ERROR_CODE);
}

static size_t	block_size(char *__TEMPLATE_BUFFER, size_t *__MOVE, ssize_t *__INDEX)
{
	size_t	count = 0;

	*__INDEX = -1;
	*__MOVE = 0;
	while (*__TEMPLATE_BUFFER)
	{
		if (!strncmp(__TEMPLATE_BUFFER, "{{ ", 3))
		{
			if (!strncmp(__TEMPLATE_BUFFER + 3, "Body }}", 7))
			{
				*__MOVE = 10;
				*__INDEX = 0;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Message }}", 10))
			{
				*__MOVE = 13;
				*__INDEX = 1;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Summary }}", 10))
			{
				*__MOVE = 13;
				*__INDEX = 2;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Appname }}", 10))
			{
				*__MOVE = 13;
				*__INDEX = 3;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Category }}", 11))
			{
				*__MOVE = 14;
				*__INDEX = 4;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "DefaultActionName }}", 20))
			{
				*__MOVE = 23;
				*__INDEX = 5;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "IconPath }}", 11))
			{
				*__MOVE = 14;
				*__INDEX = 6;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Id }}", 5))
			{
				*__MOVE = 8;
				*__INDEX = 7;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Timestamp }}", 12))
			{
				*__MOVE = 15;
				*__INDEX = 8;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Timeout }}", 10))
			{
				*__MOVE = 13;
				*__INDEX = 9;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Progress }}", 11))
			{
				*__MOVE = 14;
				*__INDEX = 10;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Urgency }}", 10))
			{
				*__MOVE = 13;
				*__INDEX = 11;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "StackTag }}", 11))
			{
				*__MOVE = 14;
				*__INDEX = 12;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 3, "Urls }}", 7))
			{
				*__MOVE = 10;
				*__INDEX = 13;
				break ;
			}
		}
		count++;
		__TEMPLATE_BUFFER++;
	}
	return (count);
}

void	output_notifications(char *__TEMPLATE_BUFFER, s_notif *__OBJS)
{
	size_t	__MOVE_COUNT;
	size_t	__BLOCK;
	ssize_t	__INDEX = -1;
	char	*__CONTAINERS[14] = {
				__OBJS->__BODY,
				__OBJS->__MESSAGE,
				__OBJS->__SUMMARY,
				__OBJS->__APPNAME,
				__OBJS->__CATEGORY,
				__OBJS->__DEFAULT_ACTION_NAME,
				__OBJS->__ICON_PATH,
				__OBJS->__ID,
				__OBJS->__TIMESTAMP,
				__OBJS->__TIMEOUT,
				__OBJS->__PROGRESS,
				__OBJS->__URGENCY,
				__OBJS->__STACK_TAG,
				__OBJS->__URLS
	};

	while (*__TEMPLATE_BUFFER)
	{
		__BLOCK = block_size(__TEMPLATE_BUFFER, &__MOVE_COUNT, &__INDEX);
		write(STDOUT_FILENO, __TEMPLATE_BUFFER, __BLOCK);
		__TEMPLATE_BUFFER += __BLOCK + __MOVE_COUNT;
		if (__INDEX != -1)
			print_value(__CONTAINERS[__INDEX]);
	}
}

void	output_help(void)
{
	output("EASY EWW NOTIFICATION CENTER!!!\n");
	output("\033[1mUsage:\033[0m notifyuck [OPTIONS]\n");
	output("\nAvalaible options:\n");
	output("\033[1m-h,  --help:\033[0m			Print this information text.\n");
	output("\033[1m-u,  --usage:\033[0m			Print a clear description about all the feature of this program.\n");
	output("\033[1m-ts, --template-string:\033[0m		Use the next argument as template string instead of fetching template.yuck.\n");
	output("\033[1m-te, --template-empty:\033[0m		Use the next argument as template string if there is no notifications.\n");
	output("\033[1m-mn, --max-notifications:\033[0m	Generate only a N maximum of yuck object.\n");
	exit(0);
}

void	output_usage(void)
{
	output("\033[1mWhat the hell is notifyuck?\033[0m\n\
It is a C program that can transform all notifications in dunstctl history into a yuck object that can be used with Eww(Elkowar's Wicky Widgets)\n\n\
\033[1mHow it works?\033[0m\n\
notifyuck will call and store the output of busctl, parse the data of all notification, output a yuck object based on the given template. All of those operations are done on the stack, no dynamic allocation are done during the entire process.\n\n\
\033[1mWhat is a template?\033[0m\n\
A template is a file that contains the yuck object that will be used as 'template' to generate all the notification.\n\n\
\033[4mExample of a template:\033[0m\n\
			(box	:class \"notif_box\"\n\
				:orientation \"h\"\n\
				:space-evenly false\n\
				(box:class \"box\"\n\
					:orientation \"h\"\n\
					:space-evenly false\n\
					:width 550\n\
					(box:class \"icon_notification\"\n\
						:halign \"center\"\n\
						:valign \"center\"\n\
						:style \"background-image: url('\033[33m{6}\033[0m');\"\n\
						)\n\
					(box:class \"box\"\n\
						:orientation \"v\"\n\
						:space-evenly false\n\
						(label:class \"notif_label\"\n\
							:halign \"start\"\n\
							:text \"\033[33m{2}\033[0m from \033[33m{3}\033[0m\"\n\
							:style \"font-size: 16px; font-weight: bold; padding-top: 12px;\"\n\
							)\n\
						(label:class \"notif_label\"\n\
							:halign \"start\"\n\
							:text \"\033[33m{0}\033[0m\"\n\
							:style \"font-size: 12px; padding-top: 4px;\"\n\
							)\n\
						)\n\
					)\n\
					(button:class \"notif_button_label\"\n\
							:onclick \"dunstctl history-rm \033[33m{7}\033[0m\"\n\
							:halign \"end\"\n\
							\"X\"\n\
					)\n\
			)\
\n\nThe character in \033[33myellow\033[0m are the character that will be substitued by the value of the notification data.\n\
\033[1mList of possible substitution:\033[0m\n\
 {0} -> BODY;\n\
 {1} -> MESSAGE;\n\
 {2} -> SUMMARY;\n\
 {3} -> APPNAME;\n\
 {4} -> CATEGORY;\n\
 {5} -> DEFAULT_ACTION_NAME;\n\
 {6} -> ICON_PATH;\n\
 {7} -> ID;\n\
 {8} -> TIMESTAMP;\n\
 {9} -> TIMEOUT;\n\
 {10} -> PROGRESS;\n\
 {11} -> URGENCY;\n\
 {12} -> STACK_TAG;\n\
 {13} -> URLS;\n\n\
\033[31m\033[1m\033[4mNote:\033[0m\n\
  - It is possible to escape the substitution by just escaping '{' with the ANSI Escape character '\\', \"\\{0}\" will print literally \\{0}.\n\
  - notifyuck doesn't check for any error inside the given template for performance reason, you should always make sure to test that your template work directly with Eww.\n\n\
\033[1mnotifyuck Features:\033[0m\n");
	exit(0);
}
