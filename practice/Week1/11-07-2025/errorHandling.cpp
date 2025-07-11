#include <iostream>
#include <stdexcept>
#include <string>

// custom error
class DatabaseError : public std::runtime_error
{
    int errorCode;

public:
    explicit DatabaseError(const std::string &message, int code)
        : std::runtime_error(message), errorCode(code) {}

    int code() const noexcept { return errorCode; }
};

class Database
{
public:
    Database()
    {
        std::cout << "Connecting to database...\n";
    }

    ~Database()
    {
        std::cout << "Disconnecting from database...\n";
    }

    std::string getUserById(int id)
    {
        if (id <= 0)
        {
            throw std::invalid_argument("Invalid user ID");
        }
        else if (id == 124)
        {
            throw DatabaseError("User not found", 404);
        }
        else
        {
            throw std::runtime_error("some other error");
        }
        return "User#" + std::to_string(id);
    }
};

void fetchUser(int id)
{
    Database db;
    std::string user = db.getUserById(id);
    std::cout << "Fetched user: " << user << "\n";
}

int main()
{
    try
    {
        fetchUser(124);
    }
    catch (const DatabaseError &e)
    {
        std::cerr << "Caught Database error:" << e.what() << " " << e.code() << "\n";
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Caught invalid argument: " << e.what() << "\n";
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Caught runtime error: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception\n";
    }
    return 0;
}
