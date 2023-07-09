#include "advancedCalculator.hpp"

std::map<char, std::function<double(const double&, const double&)>> m = {
    {'+', [](double a, double b) -> double { return a + b; }},
    {'*', [](double a, double b) -> double { return a * b; }},
    {'/', [](double a, double b) -> double { return a / b; }},
    {'-', [](double a, double b) -> double { return a - b; }},
    {'%', [](double a, double b) -> double { return std::fmod(a, b); }},
    {'!', [](double a, double b) -> double { if (a < 0.f) { double o = a; o*=(-1); return -(std::tgamma(o + 1.f));} return std::tgamma(a + 1.f); }},
    {'^', [](double a, double b) -> double { return std::pow(a, b); }},
    {'$', [](double a, double b) -> double { return std::pow(a, 1.f / b); }}};
bool isMinusSign(const std::string& input, size_t index) {
    char prevChar = input[index - 1];
    char nextChar = input[index + 1];
    if ((std::isdigit(prevChar) && std::isdigit(nextChar)) || std::isdigit(prevChar) && nextChar == '-') {
        return true;
    }
    return false;
}
bool isNumeric(const std::string& str) {
    try {
        double value = std::stod(str);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    }
}
ErrorCode process(std::string input, double* out) {
    char type;
    std::string aS;
    std::string bS;
    double a;
    double b;
    input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());
    auto findedSign = input.find_first_of("+*/-%!^$", 1);
    if (findedSign != std::string::npos) {
        if (input[findedSign] == '-' && !isMinusSign(input, findedSign)) {
            return ErrorCode::BadFormat;
        }
        type = input[findedSign];
        aS = input.substr(0, findedSign);
        bS = input.substr(findedSign + 1, input.size());

        try {
            a = std::stod(aS);
            if (type != '!') {
                b = std::stod(bS);
            }

        } catch (std::invalid_argument) {
            return ErrorCode::BadFormat;
        }
    } else {
        return ErrorCode::BadCharacter;
    }
    switch (type) {
    case '/':
        if (b == 0) {
            return ErrorCode::DivideBy0;
        }
        break;
    case '%':
        if (std::floor(a) != a || std::floor(b) != b) {
            return ErrorCode::ModuleOfNonIntegerValue;
        }
        break;
    case '$':
        if (a < 0) {
            return ErrorCode::SqrtOfNegativeNumber;
        }
        break;
    }

    auto it = m.find(type);
    if (it != m.end()) {
        *out = it->second(a, b);
    }

    return ErrorCode::OK;
}

std::string errorCodeToString(ErrorCode code) {
    switch (code) {
    case ErrorCode::OK:
        return "OK";
    case ErrorCode::BadCharacter:
        return "BadCharacter";
    case ErrorCode::BadFormat:
        return "BadFormat";
    case ErrorCode::DivideBy0:
        return "DivideBy0";
    case ErrorCode::SqrtOfNegativeNumber:
        return "SqrtOfNegativeNumber";
    case ErrorCode::ModuleOfNonIntegerValue:
        return "ModuleOfNonIntegerValue";
    default:
        return "UnknownErrorCode";
    }
}