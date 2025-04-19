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
