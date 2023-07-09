#pragma once
#include <algorithm>
#include <bitset>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include <iomanip>
#include <vector>
extern std::map<char, std::function<double(const double&, const double&)>> m;

enum class ErrorCode {
    OK,
    BadCharacter,
    BadFormat,
    DivideBy0,
    SqrtOfNegativeNumber,
    ModuleOfNonIntegerValue
};
ErrorCode process(std::string str, double* out);
bool isMinusSign(const std::string& input, size_t index);
bool isNumeric(const std::string& str);