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

std::string	fetch_template_source(void)
{
	std::array<char, 4096>	Buffer;
	FILE					*TemplateFile;
	std::string				temp;

	TemplateFile = fopen("template.yuck", "r");
	if (TemplateFile == NULL)
	{
		std::cerr << "Cannot open template file.\n";
		return ("");
	}
	while (fgets(Buffer.data(), Buffer.size(), TemplateFile) != nullptr)
		temp += Buffer.data();
	fclose(TemplateFile);
	return (temp);
}

void	write_output(NotifObj &Data, std::string Template)
{
	ReplaceAllOccurence(Template, "{{ Body }}", Data.getBody());
	ReplaceAllOccurence(Template, "{{ Message }}", Data.getMessage());
	ReplaceAllOccurence(Template, "{{ Summary }}", Data.getSummary());
	ReplaceAllOccurence(Template, "{{ Appname }}", Data.getAppname());
	ReplaceAllOccurence(Template, "{{ Category }}", Data.getCategory());
	ReplaceAllOccurence(Template, "{{ DefaultActionName }}", Data.getDefaultActionName());
	ReplaceAllOccurence(Template, "{{ IconPath }}", Data.getIconPath());
	ReplaceAllOccurence(Template, "{{ Id }}", Data.getId());
	ReplaceAllOccurence(Template, "{{ TimeStamp }}", Data.getTimeStamp());
	ReplaceAllOccurence(Template, "{{ TimeOut }}", Data.getTimeOut());
	ReplaceAllOccurence(Template, "{{ Progress }}", Data.getProgress());
	ReplaceAllOccurence(Template, "{{ Urgency }}", Data.getUrgency());
	ReplaceAllOccurence(Template, "{{ StackTag }}", Data.getStackTag());
	ReplaceAllOccurence(Template, "{{ Urls }}", Data.getUrls());
	std::cout << Template;
}

int	main(void)
{
	std::string				result;
	std::vector<NotifObj>	NotifData;
	NotifObj				Tmp;

	try
	{
		result = exec_and_get_output("dunstctl history");
	}
	catch (std::exception &e)
	{
		std::cerr << "\033[31mERROR:\033[0m notifyuck: can't execute dunstctl. Make sure that you have dunst installed on your computer using the command 'which dunst', if nothing appears, you didn't have it installed on your system.\n";
		exit (-1);
	}
	RemoveChars(result, "{}:[]	");
	ReplaceAllOccurence(result, "\n\"type\"", "");
	ReplaceAllOccurence(result, "\"s\",\n\"data\"", "=");
	ReplaceAllOccurence(result, "\"i\",\n\"data\"", "=");
	ReplaceAllOccurence(result, "\"x\",\n\"data\"", "=");
	ReplaceAllOccurence(result, "    =  ", "=");
	ReplaceAllOccurence(result, ",\n", "");

	std::istringstream			Streamer(result);
	std::string					words;
	size_t						Pos;
	/*std::vector<std::string>	Splitted;*/

	getline(Streamer, words);
	while (getline(Streamer, words))
	{
		if (words.empty() || words[0] == '\n')
			continue ;
		Pos = words.find("=");
		Tmp.setBody(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setMessage(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setSummary(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setAppname(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setCategory(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setDefaultActionName(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setIconPath(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setId(words.substr(Pos + 1));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setTimeStamp(words.substr(Pos + 1));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setTimeOut(words.substr(Pos + 1));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setProgress(words.substr(Pos + 1));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setUrgency(words.substr(Pos + 2, words.size() - Pos - 3));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setStackTag(words.substr(Pos + 1));

		getline(Streamer, words);
		Pos = words.find("=");
		Tmp.setUrls(words.substr(Pos + 2, words.size() - Pos - 3));
		NotifData.push_back(Tmp);
		/*Splitted.push_back(words);*/

	}

	std::string	Template;

	Template = fetch_template_source();
	if (Template.empty())
		return (-2);
	std::cout << "(box	:class \"box\"" << std::endl;
	std::cout << "	:orientation \"v\"" << std::endl;
	std::cout << "	:space-evenly false" << std::endl;
	for (std::vector<NotifObj>::iterator It = NotifData.begin(); It != NotifData.end(); It++)
	{
		write_output(*It, Template);
	}
	std::cout << ")" << std::endl;
	std::cout << std::endl;

	return (0);
}
