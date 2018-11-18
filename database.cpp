#include "database.h"

bool hw13::Database::insert(const std::string& table, const Row& row, std::string& error)
{
    if (!checkTable(table, error))
        return false;

    return insert(m_db[table], row, error);
}

bool hw13::Database::truncate(const std::string& table, std::string& error)
{
    if (!checkTable(table, error))
        return false;

    m_db[table].clear();

    return true;
}

bool hw13::Database::intersection(Result& result, std::string& error)
{

    return false;
}

bool hw13::Database::symmetric_difference(Result& result, std::string& error)
{
    return false;
}

bool hw13::Database::checkTable(const std::string &table, std::string &error)
{
    if (m_db.find(table) == m_db.end()) {
        error = "Неизвестная таблица '" + table + "'";
        return false;
    }

    return true;
}

bool hw13::Database::insert(Table& table, const Row &row, std::string& error)
{
    if (table.find(std::get<0>(row)) == table.end()) {
        error = "Дублирование " + std::to_string(std::get<0>(row));
        return false;
    }
    table.insert(row);

    return true;
}
