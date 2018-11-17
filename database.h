#pragma once

#include <string>
#include <vector>

namespace hw13 {

class Database
{
public:
    using Result = std::vector<std::string>;

    enum class Table {
        A,
        B
    };

    Database() = default;
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database& instance()
    {
        static Database db;
        return db;
    }

    bool insert(Table, int id, const std::string& name);
    bool truncate(Table);
    bool intersection();
    bool symmetric_difference();

    std::string getError();
    const Result& getResult();
};

} // hw13