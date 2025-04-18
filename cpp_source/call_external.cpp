#include "../include/notifyuck.hpp"

std::string exec_and_get_output(const std::string& cmd)
{
	std::array<char, 4096>	buffer;
	std::string				result;
	FILE*					pipe;

	pipe = popen(cmd.c_str(), "r");
	if (!pipe)
		throw (std::runtime_error("popen() failed!"));
	while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
		result += buffer.data();
	if (pclose(pipe) != 0)
		throw (std::runtime_error("Command failed with non-zero return"));
	return result;
}
