#include "../include/notifyuck.hpp"

void	RemoveChars(std::string &input, const std::string &to_remove)
{
	std::unordered_set<char> removal_set(to_remove.begin(), to_remove.end());

	input.erase(
			std::remove_if(
				input.begin(),
				input.end(),
				[&](char c)
				{
					return (removal_set.count(c));
				}
			),
			input.end()
	);
}

void	ReplaceAllOccurence(std::string &str, const std::string &from, const std::string &to)
{
	if (from.empty())
		return;

	size_t start_pos = 0;
	size_t from_len = from.length();
	size_t to_len = to.length();

	if (to_len > from_len)
	{
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
	std::string				result;
	std::vector<NotifObj>	NotifData;

	result = exec_and_get_output("dunstctl history");
	RemoveChars(result, "{}:[]\"	");
	ReplaceAllOccurence(result, "\ntype", "");
	ReplaceAllOccurence(result, "s,\ndata", "=");
	ReplaceAllOccurence(result, "i,\ndata", "=");
	ReplaceAllOccurence(result, "x,\ndata", "=");
	ReplaceAllOccurence(result, "    =  ", "=");
	ReplaceAllOccurence(result, ",\n", "");

	std::istringstream			Streamer(result);
	std::string					words;
	std::vector<std::string>	Splitted;

	while (getline(Streamer, words))
		Splitted.push_back(words);

	Splitted.erase(Splitted.begin());
	Splitted.erase(
			std::remove_if(
				Splitted.begin(),
				Splitted.end(),
				[&] (std::string str)
				{
					return (str.empty());
				}
			),
			Splitted.end()
	);

	for (std::vector<std::string>::iterator It = Splitted.begin(); It != Splitted.end(); It++)
		std::cout << *It << std::endl;
	std::cout << std::endl;

	return (0);
}
