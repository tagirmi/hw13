#include "database.h"

bool hw13::Database::insert(const std::string& table, const std::tuple<int, std::string>& row, std::string& error)
{
    if (table != "A" && table != "B") {
        error = "";
        return false;
    }


    return true;
}

bool hw13::Database::truncate(const std::string& table, std::string& error)
{
    return false;
}

bool hw13::Database::intersection(Result& result, std::string& error)
{
    return false;
}

bool hw13::Database::symmetric_difference(Result& result, std::string& error)
{
    return false;
}