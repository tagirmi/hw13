#pragma once

#include <string>
#include <vector>
#include <tuple>

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

    bool insert(const std::string& table, const std::tuple<int, std::string>& row);
    bool truncate(const std::string& table);
    bool intersection();
    bool symmetric_difference();

    std::string getError();
    const Result& getResult();

private:
    std::string m_error{};
    Result m_result{};
};

} // hw13