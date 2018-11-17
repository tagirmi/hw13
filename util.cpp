#include <algorithm>

#include "util.h"

std::vector<std::string> util::split(const std::string &str, char d)
{
    std::vector<std::string> r;
    r.reserve(std::count(str.cbegin(), str.cend(), d) + 1);

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}