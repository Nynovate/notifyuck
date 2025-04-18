#pragma once
# include <iostream>

class NotifObj
{
private:
	std::string	Body;
	std::string	Message;
	std::string	Summary;
	std::string	Appname;
	std::string	Category;
	std::string	DefaultActionName;
	std::string	IconPath;
	std::string	Id;
	std::string	TimeStamp;
	std::string	TimeOut;
	std::string	Progress;
	std::string	Urgency;
	std::string	StackTag;
	std::string	Urls;

public:
	NotifObj(void) {};
	
	NotifObj(const NotifObj &other)
	{
	   if (this != &other)
	   {
	   	setBody(other.getBody());
	   	setMessage(other.getMessage());
	   	setSummary(other.getSummary());
	   	setAppname(other.getAppname());
	   	setCategory(other.getCategory());
	   	setDefaultActionName(other.getDefaultActionName());
	   	setIconPath(other.getIconPath());
	   	setId(other.getId());
	   	setTimeStamp(other.getTimeStamp());
	   	setTimeOut(other.getTimeOut());
	   	setProgress(other.getProgress());
	   	setUrgency(other.getUrgency());
	   	setStackTag(other.getStackTag());
	   	setUrls(other.getUrls());
	   }
	};
	
	NotifObj	&operator=(const NotifObj &other)
	{
	   if (this != &other)
	   {
			setBody(other.getBody());
			setMessage(other.getMessage());
			setSummary(other.getSummary());
			setAppname(other.getAppname());
			setCategory(other.getCategory());
			setDefaultActionName(other.getDefaultActionName());
			setIconPath(other.getIconPath());
			setId(other.getId());
			setTimeStamp(other.getTimeStamp());
			setTimeOut(other.getTimeOut());
			setProgress(other.getProgress());
			setUrgency(other.getUrgency());
			setStackTag(other.getStackTag());
			setUrls(other.getUrls());
	   }
	   return (*this);
	};
	
	~NotifObj(void) {};
	
	const std::string	&getBody(void) const { return (Body); };
	const std::string	&getMessage(void) const { return (Message); };
	const std::string	&getSummary(void) const { return (Summary); };
	const std::string	&getAppname(void) const { return (Appname); };
	const std::string	&getCategory(void) const { return (Category); };
	const std::string	&getDefaultActionName(void) const { return (DefaultActionName); };
	const std::string	&getIconPath(void) const { return (IconPath); };
	const std::string	&getId(void) const { return (Id); };
	const std::string	&getTimeStamp(void) const { return (TimeStamp); };
	const std::string	&getTimeOut(void) const { return (TimeOut); };
	const std::string	&getProgress(void) const { return (Progress); };
	const std::string	&getUrgency(void) const { return (Urgency); };
	const std::string	&getStackTag(void) const { return (StackTag); };
	const std::string	&getUrls(void) const { return (Urls); };
	
	void	setBody(const std::string newValue) { Body = newValue; };
	void	setMessage(const std::string newValue) { Message = newValue; };
	void	setSummary(const std::string newValue) { Summary = newValue; };
	void	setAppname(const std::string newValue) { Appname = newValue; };
	void	setCategory(const std::string newValue) { Category = newValue; };
	void	setDefaultActionName(const std::string newValue) { DefaultActionName = newValue; };
	void	setIconPath(const std::string newValue) { IconPath = newValue; };
	void	setId(const std::string newValue) { Id = newValue; };
	void	setTimeStamp(const std::string newValue) { TimeStamp = newValue; };
	void	setTimeOut(const std::string newValue) { TimeOut = newValue; };
	void	setProgress(const std::string newValue) { Progress = newValue; };
	void	setUrgency(const std::string newValue) { Urgency = newValue; };
	void	setStackTag(const std::string newValue) { StackTag = newValue; };
	void	setUrls(const std::string newValue) { Urls = newValue; };
};
