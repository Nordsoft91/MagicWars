#pragma once

#include <string>

bool isIntegerNumber(const std::string& i_str, int& o_res);

bool isIntegerNumber(const std::string& i_str);

bool isFloatNumber(const std::string& i_str, double& o_res);

bool isFloatNumber(const std::string& i_str);

size_t packStringByWords(const std::string& i_str, size_t i_limit, size_t i_begin = 0, char i_sep = ' ');