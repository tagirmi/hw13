#include "database.h"

bool hw13::Database::insert(const std::string &table, const std::tuple<int, std::string> &row)
{
    return false;
}

bool hw13::Database::truncate(const std::string &table)
{
    return false;
}

bool hw13::Database::intersection()
{
    return false;
}

bool hw13::Database::symmetric_difference()
{
    return false;
}

std::string hw13::Database::getError()
{
    return m_error;
}

const hw13::Database::Result &hw13::Database::getResult()
{
    return m_result;
}
