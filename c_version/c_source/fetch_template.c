#include "../include/notifyuck.hpp"

static void	read_template(char *__TEMPLATE_BUFFER, int __TEMPLATE)
{
	ssize_t	nread;

	nread = read(__TEMPLATE, __TEMPLATE_BUFFER, __INTERNAL_BUFF__);
	if (nread == __ERROR_FAILURE__)
		exit(error("An error occured during the read of the template file\n", __ERROR_READ_TEMPLATE__));
}

void	fetch_template(char *__TEMPLATE_BUFFER)
{
	char	*__PATH;
	int		__TEMPLATE;

	__PATH = getenv("NOTIFYUCK_PATH_TEMPLATE");
	if (!__PATH)
	{
		__TEMPLATE = open("template.yuck", O_RDONLY);
		if (__TEMPLATE == __ERROR_FAILURE__)
		{
			output("(label :class \"label\" :text \"Can't open template.yuck. Try running notifyuck to look for the error\")\n");
			/*exit(error("The program can't open the template.yuck file. Make sure it located at the root of your custom eww folders, by default it is located at /home/$USER/.config/eww/\n", __ERROR_OPEN_TEMPLATE__));*/
			exit(__ERROR_OPEN_TEMPLATE__);
		}
		read_template(__TEMPLATE_BUFFER, __TEMPLATE);
	}
	else
	{
		__TEMPLATE = open(__PATH, O_RDONLY);
		if (__TEMPLATE == __ERROR_FAILURE__)
		{
			output("(label :class \"label\" :text \"Can't open user custom template. Try running notifyuck to look for the error\")\n");
			/*exit(error("The program can't open the user custom template file\n", __ERROR_OPEN_TEMPLATE__));*/
			exit(__ERROR_OPEN_TEMPLATE__);
		}
		read_template(__TEMPLATE_BUFFER, __TEMPLATE);
	}
}
