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

static size_t	block_size(char *__TEMPLATE_BUFFER, ssize_t *__MOVE, ssize_t *__INDEX)
{
	size_t	count = 0;

	*__INDEX = -1;
	*__MOVE = 0;
	while (*__TEMPLATE_BUFFER)
	{
		if (*__TEMPLATE_BUFFER == '\\')
		{
			*__MOVE = -1;
			break ;
		}
		if (!strncmp(__TEMPLATE_BUFFER, "{", 1))
		{
			if (!strncmp(__TEMPLATE_BUFFER + 1, "0}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 0;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "1}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 1;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "2}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 2;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "3}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 3;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "4}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 4;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "5}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 5;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "6}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 6;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "7}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 7;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "8}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 8;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "9}", 2))
			{
				*__MOVE = 3;
				*__INDEX = 9;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "10}", 3))
			{
				*__MOVE = 4;
				*__INDEX = 10;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "11}", 3))
			{
				*__MOVE = 4;
				*__INDEX = 11;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "12}", 3))
			{
				*__MOVE = 4;
				*__INDEX = 12;
				break ;
			}
			else if (!strncmp(__TEMPLATE_BUFFER + 1, "13}", 3))
			{
				*__MOVE = 4;
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
	ssize_t	__MOVE_COUNT;
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
		if (__MOVE_COUNT == -1)
		{
			__TEMPLATE_BUFFER += __BLOCK + 1;
			write(STDOUT_FILENO, __TEMPLATE_BUFFER, 1);
			__TEMPLATE_BUFFER++;
			continue ;
		}
		else
			__TEMPLATE_BUFFER += __BLOCK + __MOVE_COUNT;
		if (__INDEX != -1)
			print_value(__CONTAINERS[__INDEX]);
	}
}

void	output_help(void)
{
	output("EASY EWW NOTIFICATION CENTER!!!\n");
	output("\033[1mUsage:\033[0m notifyuck [OPTIONS] [VALUE] ...\n");
	output("\nAvalaible options:\n");
	output("\033[1m-h,  --help:\033[0m			Print this information text.\n");
	output("\033[1m-u,  --usage:\033[0m			Print a clear description about all the feature of this program.\n");
	output("\033[1m-ts, --template-string:\033[0m		Use the next argument as template string instead of fetching template.yuck.\n");
	output("\033[1m-te, --template-empty:\033[0m		Use the next argument as template string if there is no notifications.\n");
	output("\033[1m-mn, --max-notifications:\033[0m	Generate only a N maximum of yuck object.\n");
	output("\033[1m-gl, --gen-inline:\033[0m		Translate the template.yuck file into a correct inline Eww object.\n");
	exit(0);
}

void	output_usage(void)
{
	output("\033[1mWhat the hell is notifyuck?\033[0m\n\
It is a C program that can transform all notifications in dunstctl history into a yuck object that can be used with Eww(Elkowar's Wicky Widgets)\n\n\
\033[1mHow it works?\033[0m\n\
notifyuck will call and store the output of busctl, parse the data of all notification, output a yuck object based on the given template.\n\
All of those operations are done on the stack, no dynamic allocation are done during the entire process.\n\n\
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
 {0}  -> BODY;\n\
 {1}  -> MESSAGE;\n\
 {2}  -> SUMMARY;\n\
 {3}  -> APPNAME;\n\
 {4}  -> CATEGORY;\n\
 {5}  -> DEFAULT_ACTION_NAME;\n\
 {6}  -> ICON_PATH;\n\
 {7}  -> ID;\n\
 {8}  -> TIMESTAMP;\n\
 {9}  -> TIMEOUT;\n\
 {10} -> PROGRESS;\n\
 {11} -> URGENCY;\n\
 {12} -> STACK_TAG;\n\
 {13} -> URLS;\n\n\
\033[31m\033[1m\033[4mNote:\033[0m\n\
  - It is possible to escape the substitution by just escaping '{' with the ANSI Escape character '\\', \"\\{0}\" will print literally \\{0}.\n\
  - notifyuck doesn't check for any error inside the given template for performance reason, you should always make sure to test that your template work directly with Eww.\n\n\
\033[1m\033[4mnotifyuck options:\033[0m\n\
\033[1m\033[33m -ts, --template-string:\033[0m you can directly pass an inline yuck to the program for better performance.\n\
In normal case, the template string are read from the DISK, and sending data from the DISK to the RAM is extremely slow!\n\
Using this options can help to reduce the overhead. The best workflow I found, is to first\n\
make a working notification mockup and test it directly in Eww. Then I copy that Eww objects and paste it inside\n\
template.yuck. When I'm happy with the final result, I will directly create an inline of that same template.yuck with the\n\
built-in feature --gen-inline that will be directly just pasted to Eww.\n\n\
\033[31mNote: \033[0m It is important to note that the template string should be sent as a one big argument to the program!.\n\
Example:\n\n\
This is the inline of the previous template used in my Eww Config:\n\n\
(defpoll NotificationData	:interval \"10s\"\n\
            './scripts/notif/c_version/notifyuck -ts \\\"(box :class \\\\\"notif_box\\\\\" :orientation \\\\\"h\\\\\" :space-evenly false(box :class \\\\\"box\\\\\" :orientation \\\\\"h\\\\\" :space-evenly false :width 550 (box :class \\\\\"icon_notification\\\\\" :halign \\\\\"center\\\\\" :valign \\\\\"center\\\\\" :style \\\\\"background-image: url(\'{6}\');\\\\\") (box :class \\\\\"box\\\\\" :orientation \\\\\"v\\\\\" :space-evenly false (label :class \\\\\"notif_label\\\\\" :halign \\\\\"start\\\\\" :text \\\\\"{2} from {3}\\\\\" :style \\\\\"font-size: 16px; font-weight: bold; padding-top: 12px;\\\\\") (label :class \\\\\"notif_label\\\\\" :halign \\\\\"start\\\\\" :text \\\\\"{0}\\\\\" :style \\\\\"font-size: 12px; padding-top: 4px;\\\\\"))) (button :class \\\\\"notif_button_label\\\\\" :onclick \\\\\"dunstctl history-rm {7}\\\\\" :halign \\\\\"end\\\\\" \\\\\"X\\\\\"))\\\"'\n\
)\n\n\
You may wonder why there is so much ANSI Escape character, since the program wait for the template string to be entirely in one argument\n\
it become really tricky to write it in the correct way in Eww and Sh.\n\
No need to say that manually writing this will be painful!\n\n\
\033[1m\033[33m -te, --template-empty:\033[0m If there is no notifications in the history, make notifyuck output this yuck string.\n\
Example: '(label :class \"label\" :text \"No notifications\")'\n\n\
\033[1m\033[33m -mn, --max-notifications:\033[0m Output only N Yuck objects, you can also directly limit the number of\n\
notifications in dunst directly. This makes notifyuck output only the N most recent objects.\n\n\
\033[1m\033[33m -gl, --gen-inline:\033[0m Translate the template.yuck into an inline yuck that SHOULD directly\n\
just be pasted into your (defpoll variable). Why? Because it directly take into account the PAINFUL Escaping of '\"' character.\n\n\
\033[31mNote: \033[0mIt is only valid if you want to directly call notifyuck in defpoll instead of wrapping it to a scripts.\n\
");
	exit(0);
}
