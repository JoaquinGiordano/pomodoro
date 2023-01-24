
#include <iostream>
#include <string>

std::string getTime(int seconds)
{
    std::string result;

    result.append(std::to_string(seconds / 60));
    result.append("m ");
    result.append(std::to_string(seconds % 60));
    result.append("s");

    return result;
}