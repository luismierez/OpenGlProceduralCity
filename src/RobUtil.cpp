#include "RobUtil.h"

list<string> splitStr(string input, string delimiter)
{
	list<string> returnList = list<string>();
	size_t lastPos = 0;
	size_t foundPos = 0;
	while((foundPos = input.find(delimiter, lastPos)) != string::npos)
	{
		returnList.push_back(input.substr(lastPos, foundPos-lastPos));
		lastPos = foundPos+1;
	}
	if(returnList.empty())
	{
		returnList.push_back(input);
	}
	else if( (input.length() - lastPos) != 0)
	{
		returnList.push_back(input.substr(lastPos, input.length() - lastPos));
	}
	return returnList;
}