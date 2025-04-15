#include <iostream>
#include <vector>

typedef struct s_notif
{
	std::string	Body;
	std::string	Message;
	std::string	Summary;
	std::string	Appname;
	std::string	Category;
	std::string	DefaultActionName;
	std::string	IconPath;
	std::string	Id;
	std::string	TimeStamp;
	std::string	Timeout;
	std::string	Progress;
	std::string	Urgency;
	std::string	Stack_tag;
	std::string	Urls;
}				Notif;

void	createNotification(std::string &Line)
{
	Notif			Data;
	std::string		*PtrData[14] = {&Data.Body,
								&Data.Message,
								&Data.Summary,
								&Data.Appname,
								&Data.Category,
								&Data.DefaultActionName,
								&Data.IconPath,
								&Data.Id,
								&Data.TimeStamp,
								&Data.Timeout,
								&Data.Progress,
								&Data.Urgency,
								&Data.Stack_tag,
								&Data.Urls,
	};
	unsigned int	Pos(0);

	while (Pos < 13)
	{
		*PtrData[Pos] = Line.substr(Line.find_first_of("=") + 1);
		Pos++;
		getline(std::cin, Line);
	}

	if (Data.Urgency == "CRITICAL")
		std::cout << "(box	:class \"notif_box_critical\"" << std::endl;
	else
		std::cout << "	(box	:class \"notif_box\"" << std::endl;
	std::cout << "			:orientation \"h\"" << std::endl;
	std::cout << "			:space-evenly false" << std::endl;
	std::cout << "			(box	:class \"box\"" << std::endl;
	std::cout << "					:orientation \"h\"" << std::endl;
	std::cout << "					:space-evenly false" << std::endl;
	std::cout << "					:width 550" << std::endl;

	if (Data.IconPath.empty())
	{
		std::cout << "					(label	:class \"notif_label\"" << std::endl;
		std::cout << "							:halign \"start\"" << std::endl;
		std::cout << "							:text \" \"" << std::endl;
		std::cout << "							:style \"font-size: 40px; margin: 7px;\"" << std::endl;
		std::cout << "					)" << std::endl;
	}
	else
	{
		std::cout << "					(box	:class \"icon_notification\"" << std::endl;
		std::cout << "							:halign \"center\"" << std::endl;
		std::cout << "							:valign \"center\"" << std::endl;
		std::cout << "							:style \"background-image: url(\'" << Data.IconPath << "\');\"" << std::endl;
		std::cout << "					)" << std::endl;
	}

	std::cout << "					(box	:class \"box\"" << std::endl;
	std::cout << "							:orientation \"v\"" << std::endl;
	std::cout << "							:space-evenly false" << std::endl;
	std::cout << "							(label	:class \"notif_label\"" << std::endl;
	std::cout << "									:halign \"start\"" << std::endl;

	std::cout << "									:text \"" << Data.Summary << " from " << Data.Appname << "\"" << std::endl;

	std::cout << "									:style \"font-size: 16px; font-weight: bold; padding-top: 12px;\"" << std::endl;
	std::cout << "							)" << std::endl;
	std::cout << "							(label	:class \"notif_label\"" << std::endl;
	std::cout << "									:halign \"start\"" << std::endl;

	if (Data.Body.empty())
		std::cout << "							:text \"Send a notification\"" << std::endl;
	else
		std::cout << "							:text \"" << Data.Body << "\"" << std::endl;

	std::cout << "							:style \"font-size: 12px; padding-top: 4px;\"" << std::endl;
	std::cout << "					)" << std::endl;
	std::cout << "			)" << std::endl;
	std::cout << "		)" << std::endl;
	std::cout << "		(button	:class \"notif_button_label\"" << std::endl;
	std::cout << "		 			:onclick \"dunstctl history-rm " << Data.Id << "\"" << std::endl;
	std::cout << "		 			:halign \"end\"" << std::endl;
	std::cout << "		 			\"X\"" << std::endl;
	std::cout << "		)" << std::endl;
	std::cout << "	)" << std::endl;
}

int	main(int argc, char *argv[])
{
	std::string			Line;

	if (argc == 2)
	{
		std::string	args = argv[1];

		std::cout << "(label :class \"label\" :text \"No Notifications\" :halign \"center\" :valign \"center\" :style \"padding-top: 120px;\")\n";
		exit(0);
	}
	std::cout << "(box	:class \"box\"" << std::endl;
	std::cout << "	:orientation \"v\"" << std::endl;
	std::cout << "	:space-evenly false" << std::endl;
	while (getline(std::cin, Line))
	{
		if (Line.empty())
			continue ;
		createNotification(Line);
	}
	std::cout << ")" << std::endl;
	return (0);
}
