#include "StringUtils.h"

bool isIntegerNumber(const std::string& i_str, int& o_res)
{
	o_res = atoi(i_str.c_str());
	bool minus = false;
	for (char i : i_str)
	{
		if (i == '-')
		{
			if (i_str[0] == '-' && minus == false)
				minus = true;
			else
				return false;
		}

		if (i != '-' && (i<'0' || i>'9'))
			return false;
	}
	return true;
}

bool isIntegerNumber(const std::string& i_str)
{
	int a = 0;
	return isIntegerNumber(i_str, a);
}

bool isFloatNumber(const std::string& i_str, double& o_res)
{
	o_res = atof(i_str.c_str());
	size_t point = i_str.find('.');
	if (point == std::string::npos && isIntegerNumber(i_str))
		return true;

	int after = 0;
	if (isIntegerNumber(i_str.substr(0, point)) && isIntegerNumber(i_str.substr(point), after) && after >= 0)
		return true;
	return false;
}

bool isFloatNumber(const std::string& i_str)
{
	double a = 0;
	return isFloatNumber(i_str, a);
}

size_t packStringByWords(const std::string& i_str, size_t i_limit, size_t i_begin, char i_sep)
{
	const size_t length = i_str.length();
	if (i_begin > length)
		throw std::exception("Begin symbol is outide of array");

	if ((length - i_begin) <= i_limit)
		return length;

	size_t current = i_begin;
	while (--i_limit)
	{
		++i_begin;
		if (i_str[i_begin] == i_sep)
			current = i_begin;
	}
	return current;
}