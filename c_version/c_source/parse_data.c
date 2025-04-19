#include "../include/notifyuck.hpp"

static void	assign_ptr(char *__PTR, char *__PATTERN, char **__TARGET, char **__BUFFER, size_t bytes_to_move)
{
	if (__PTR == NULL)
	{
		char	*ptr;

		ptr = strnstr(*__BUFFER, __PATTERN, 256);
		*__TARGET = ptr + strlen(__PATTERN);
		*__BUFFER = *__TARGET;
	}
	else
	{
		*__TARGET = __PTR + bytes_to_move;
		*__BUFFER = *__TARGET;
	}
}

static size_t	end_value(char *__DATA)
{
	size_t	pos = 0;

	while (pos < 256)
	{
		if (__DATA[pos] == '\\' && __DATA[pos + 1] == '\"')
		{
			pos += 2;
			continue ;
		}
		else if (__DATA[pos] == '\"')
			break ;
		pos++;
	}
	return (pos);
}

void	print_value(char *__DATA)
{
	if (*__DATA == '\"' && *(__DATA + 1) == '\"')
	{
	}
	else if (*__DATA == '\"')
		write(STDOUT_FILENO, __DATA + 1, end_value(__DATA + 1));
	else
		write(STDOUT_FILENO, __DATA, ((long)strchr(__DATA, '}') - (long)__DATA));
}

void	parse_data(char *__BUFFER, s_notif *__OBJS, size_t *__PARSED_DATA)
{
	int		index;
	char	*ptr;

	index = 0;
	while (true)
	{
		ptr = strnstr(__BUFFER, "\"body\":{\"type\":\"s\",\"data\":", 256);
		if (!ptr)
			break ;
		__OBJS[index].__VALID_SLOT = true;
		assign_ptr(ptr, NULL, &__OBJS[index].__BODY, &__BUFFER, 26);
		assign_ptr(NULL, "\"message\":{\"type\":\"s\",\"data\":", &__OBJS[index].__MESSAGE, &__BUFFER, -1);
		assign_ptr(NULL, "\"summary\":{\"type\":\"s\",\"data\":", &__OBJS[index].__SUMMARY, &__BUFFER, -1);
		assign_ptr(NULL, "\"appname\":{\"type\":\"s\",\"data\":", &__OBJS[index].__APPNAME, &__BUFFER, -1);
		assign_ptr(NULL, "\"category\":{\"type\":\"s\",\"data\":", &__OBJS[index].__CATEGORY, &__BUFFER, -1);
		assign_ptr(NULL, "\"default_action_name\":{\"type\":\"s\",\"data\":", &__OBJS[index].__DEFAULT_ACTION_NAME, &__BUFFER, -1);
		assign_ptr(NULL, "\"icon_path\":{\"type\":\"s\",\"data\":", &__OBJS[index].__ICON_PATH, &__BUFFER, -1);
		assign_ptr(NULL, "\"id\":{\"type\":\"i\",\"data\":", &__OBJS[index].__ID, &__BUFFER, 7);
		assign_ptr(NULL, "\"timestamp\":{\"type\":\"x\",\"data\":", &__OBJS[index].__TIMESTAMP, &__BUFFER, -1);
		assign_ptr(NULL, "\"timeout\":{\"type\":\"x\",\"data\":", &__OBJS[index].__TIMEOUT, &__BUFFER, -1);
		assign_ptr(NULL, "\"progress\":{\"type\":\"i\",\"data\":", &__OBJS[index].__PROGRESS, &__BUFFER, -1);
		assign_ptr(NULL, "\"urgency\":{\"type\":\"s\",\"data\":", &__OBJS[index].__URGENCY, &__BUFFER, -1);
		assign_ptr(NULL, "\"stack_tag\":{\"type\":\"s\",\"data\":", &__OBJS[index].__STACK_TAG, &__BUFFER, -1);
		assign_ptr(NULL, "\"urls\":{\"type\":\"s\",\"data\":", &__OBJS[index].__URLS, &__BUFFER, -1);
		(*__PARSED_DATA)++;
		index++;
	}
}
