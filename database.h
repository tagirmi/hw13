#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

namespace hw13 {

class Database
{
public:
    using Result = std::vector<std::string>;

    Database() = default;
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database& instance()
    {
        static Database db;
        return db;
    }

    bool insert(const std::string& table, const std::tuple<int, std::string>& row, std::string& error);
    bool truncate(const std::string& table, std::string& error);
    bool intersection(Result& result, std::string& error);
    bool symmetric_difference(Result& result, std::string& error);

private:
    using Table = std::unordered_map<int, std::string>;

    Table m_tableA{};
    Table m_tableB{};
};

} // hw13