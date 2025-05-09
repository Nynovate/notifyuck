#include "../include/notifyuck.hpp"

size_t	output(const char *str)
{
	if (!str)
		return (0);
	return (write(STDOUT_FILENO, str, strlen(str)));
}

void	args_error(const char *str)
{
	if (!str)
		return ;
	if (*str != '\0')
	{
		write(STDERR_FILENO, "\033[31mERROR: \033[0mnotifyuck: ", 28);
		write(STDERR_FILENO, str, strlen(str));
	}
	write(STDERR_FILENO, "\n\nFor more information, try \033[1m\"-h\"\033[0m or \033[1m\"--help\"\033[0m.\nFor detailed explanation, try \033[1m\"-u\"\033[0m or \033[1m\"--usage\"\033[0m.\n", 128);
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
	output("EASY NOTIFICATION CENTER!!!\n");
	output("\033[1mUsage:\033[0m notifyuck [OPTIONS] [VALUE] ...\n");
	output("\nAvalaible options:\n");
	output("\033[1m-h,  --help:\033[0m			Print this information text.\n");
	output("\033[1m-u,  --usage:\033[0m			Print a clear description about all the feature of this program.\n");
	output("\033[1m-v,  --version:\033[0m			Print the version of the program and quit.\n");
	output("\033[1m-ft, --file-template:\033[0m		Use the next argument as template file instead of fetching template.yuck.\n");
	output("\033[1m-ts, --template-string:\033[0m		Use the next argument as template string instead of fetching template.yuck.\n");
	output("\033[1m-te, --template-empty:\033[0m		Use the next argument as template string if there is no notifications.\n");
	output("\033[1m-so, --show-only:\033[0m		Generate only a N maximum of yuck object.\n");
	output("\033[1m-gl, --gen-inline:\033[0m		Translate the template.yuck file into a correct inline Eww object.\n");
	exit(0);
}

void	output_version(void)
{
	output("notifyuck v0.1.0\n");
	exit(0);
}

void	output_usage(void)
{
	output("\033[1mWhat the hell is notifyuck?\033[0m\n\
	It is a C program that work with dunst to easily create a notification center\n\
	with Eww(Elkowar's Wicky Widgets).\n\n\
\033[1mHow it works?\033[0m\n\
	notifyuck will call and store the output of busctl, parse the data of all\n\
	notification, output the notification based on the given template.\n\
	In simple term, it just does simple substitution with the data of all notification.\n\n\
\033[1mWhen to use it?\033[0m\n\
	Well, if you have seen a cool ricing that implement a cool notification center\n\
	but have no clue on how to do it. Also, most of times, notification center\n\
	are quite hard to do, there is a lot of stuff to do with script and quickly\n\
	become overwhelming for non-programmers.\n\n\
\033[1mMy goal?\033[0m\n\
	Make an easy tool to use for everybody, ricing should be accessible to everyone!\n\
	Doing it in a script are less performant than using notifyuck, notifyuck was build\n\
	to be fast. I get a pretty decent result on my potato pc!\n\n\
\033[1mWhat is a template?\033[0m\n\
	A template is a file that contains the yuck object that will be used as\n\
	blueprint to generate all the notification.\n\n\
\033[1mHow to use it?\033[0m\n\
	If you call notifyuck without any arguments, it will look for template.yuck\n\
	in the folder where the program is located. You can also pass a file with\n\
	the options -pt or --path-template. It is important to note than when\n\
	calling the program from Eww, \033[4mtemplate.yuck have to be located at the root\n\
	of your eww configs folder instead of where the program is located!\033[0m\n\n\
	Let's have some simple example:\n\
	This will be in our template.yuck -> (label :class \"notification\" :markup \"{0}\")\n\
	notifyuck will take this template and apply the same template for each\n\
	notification inside the notifications history. There will be a loop\n\
	that print that template with each one them substitued by the notification data!\n\n\
	We will get an output like this if there is 3 notifications in the history:\n\
			(label :class \"notification\" :markup \"A normal notification\")\n\
			(label :class \"notification\" :markup \"Another notification\")\n\
			(label :class \"notification\" :markup \"Maybe a urgent notification\")\n\n\
	It was easy peasy no? We can also add more complexity by setting a custom\n\
	class depending on the type of notifications like this:\n\
		(label :class \"notification_{11}\" :markup \"{0}\")\n\n\
	We will get an output like this with the previous example:\n\
			(label :class \"notification_LOW\" :markup \"A normal notification\")\n\
			(label :class \"notification_NORMAL\" :markup \"Another notification\")\n\
			(label :class \"notification_CRITICAL\" :markup \"Maybe a urgent notification\")\n\n\
\033[4mExample of a more complex template:\033[0m\n\
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
\n\nThe character in \033[33myellow\033[0m are the character that will be substitued\n\
by the value of the notification data.\n\
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
	- It is possible to escape the substitution by just escaping '{' with the\n\
	ANSI Escape character '\\', \"\\{0}\" will print literally {0}.\n\
	- notifyuck doesn't check for any error inside the given template for\n\
	performance reason, you should always make sure to test that your template\n\
	work directly with Eww.\n\n\
\033[1m\033[4mnotifyuck options:\033[0m\n\
\033[1m\033[33m -ts, --template-string:\033[0m\n\
	You can directly pass an inline yuck to the program for better performance.\n\
	In normal case, the template string are read from the DISK, and sending data\n\
	from the DISK to the RAM is extremely slow! Using this options can help to\n\
	reduce the overhead. The best workflow I found, is to first make a working\n\
	notification mockup and test it directly in Eww. From then, I would copy that\n\
	Eww objects and paste it inside template.yuck. When I'm happy with the final\n\
	result, I will directly create an inline of that same template.yuck with the\n\
	built-in feature --gen-inline that will be directly just pasted to Eww.\n\n\
	\033[31m\033[4m\033[1mNote:\033[0m\n\
	It is important to note that the template string should be sent as a one big\n\
	argument to the program!\n\
	Example:\n\n\
	This is the inline of the previous template used in my Eww Config:\n\n\
(defpoll NotificationData	:interval \"10s\"\n\
            './scripts/notif/c_version/notifyuck -ts \\\"(box :class \\\\\"notif_box\\\\\" :orientation \\\\\"h\\\\\" :space-evenly false(box :class \\\\\"box\\\\\" :orientation \\\\\"h\\\\\" :space-evenly false :width 550 (box :class \\\\\"icon_notification\\\\\" :halign \\\\\"center\\\\\" :valign \\\\\"center\\\\\" :style \\\\\"background-image: url(\'{6}\');\\\\\") (box :class \\\\\"box\\\\\" :orientation \\\\\"v\\\\\" :space-evenly false (label :class \\\\\"notif_label\\\\\" :halign \\\\\"start\\\\\" :text \\\\\"{2} from {3}\\\\\" :style \\\\\"font-size: 16px; font-weight: bold; padding-top: 12px;\\\\\") (label :class \\\\\"notif_label\\\\\" :halign \\\\\"start\\\\\" :text \\\\\"{0}\\\\\" :style \\\\\"font-size: 12px; padding-top: 4px;\\\\\"))) (button :class \\\\\"notif_button_label\\\\\" :onclick \\\\\"dunstctl history-rm {7}\\\\\" :halign \\\\\"end\\\\\" \\\\\"X\\\\\"))\\\"'\n\
)\n\n\
	You may wonder why there is so much ANSI Escape character, since the program\n\
	wait for the template string to be entirely in one argument\n\
	it become really tricky to write it in the correct way in Eww and Sh.\n\
	No need to say that manually writing this will be painful!\n\n\
\033[1m\033[33m -ft, --file-template:\033[0m\n\
	Use this file as template instead of template.yuck.\n\n\
	\033[31m\033[4m\033[1mNote:\033[0m\n\
	If it is called from eww, prefer using absolute path than relative path!\n\
	It can become really tricky to know where the file is located because eww\n\
	always search inside the root of your eww configs.\n\n\
\033[1m\033[33m -te, --template-empty:\033[0m\n\
	If there is no notifications in the history, make notifyuck output this yuck string.\n\
	The default one used is:\n\
		'(label :class \"no_notification_label\" :text \"No notification\")'\n\n\
\033[1m\033[33m -so, --show-only:\033[0m\n\
	Output only N Yuck objects.\n\
	This makes notifyuck output only the N most recent objects.\n\n\
\033[1m\033[33m -gl, --gen-inline:\033[0m\n\
	Translate the template.yuck into an inline yuck that SHOULD directly\n\
	just be pasted into your (defpoll variable). Why? Because it directly\n\
	take into account the PAINFUL Escaping of '\"' character.\n\
	This only works if it the only argument sent to notifyuck like\n\
	./notifyuck [-gl|--generate-inline]\n\n\
	\033[31m\033[4m\033[1mNote:\033[0m\n\
	It is only necessary if you want to directly call notifyuck in defpoll\n\
	instead of wrapping it around a script.\n\n\
\033[1mAUTHOR:\033[0m\n\
	Written by RAKOTOARIVONY Razanajohary Ny Hasina\n\n\
\033[1mCOPYRIGHTS:\033[0m\n\
	MIT License\n\n\
	Copyright (c) 2025 RAKOTOARIVONY Razanajohary Ny Hasina\n\
	Permission is hereby granted, free of charge, to any person obtaining a copy\n\
	of this software and associated documentation files (the \"Software\"), to deal\n\
	in the Software without restriction, including without limitation the rights\n\
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
	copies of the Software, and to permit persons to whom the Software is\n\
	furnished to do so, subject to the following conditions:\n\
	The above copyright notice and this permission notice shall be included in all\n\
	copies or substantial portions of the Software.\n\
	THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n\
	SOFTWARE.\n\
");
	exit(0);
}
