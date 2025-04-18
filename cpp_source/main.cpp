#include "../include/notifyuck.hpp"

void remove_chars(std::string &input, const std::string &to_remove)
{
	std::unordered_set<char> removal_set(to_remove.begin(), to_remove.end());

	input.erase(
		std::remove_if(input.begin(), input.end(),
			[&](char c) { return removal_set.count(c); }),
		input.end()
	);
}

void replace_all_fast(std::string &str, const std::string &from, const std::string &to)
{
	if (from.empty())
		return;

	size_t start_pos = 0;
	size_t from_len = from.length();
	size_t to_len = to.length();

	// Reserve extra space if growing to minimize reallocations
	if (to_len > from_len) {
		size_t count = 0;
		for (size_t pos = str.find(from); pos != std::string::npos; pos = str.find(from, pos + from_len))
			++count;
		str.reserve(str.size() + (to_len - from_len) * count);
	}

	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from_len, to);
		start_pos += to_len;
	}
}

int	main(void)
{
	std::string	result;

	result = exec_and_get_output("dunstctl history");
	remove_chars(result, "{} :[]");
	std::cout << result << std::endl;
	return (0);
}
