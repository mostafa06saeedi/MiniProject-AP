#include "User.h"
#include <functional> 
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdexcept>

namespace CounterStrike {
using namespace std;

    User::User(const std::string& username, const std::string& nickname, const std::string& password)
        : username(username), nickname(nickname), wins(0), hashedPassword(hashPassword(password)) {}

    std::string User::hashPassword(const std::string& password) const {
        std::hash<std::string> hasher;
        size_t hashedValue = hasher(password);

        std::ostringstream oss;
        oss << std::hex << std::setw(16) << std::setfill('0') << hashedValue;

        return oss.str();
    }

    void User::saveToFile() const {
        std::ofstream file("users.dat", std::ios::app);
        if (!file) throw std::runtime_error("Failed to open file for writing");

        file << username << " " << nickname << " " << hashedPassword << " " << wins << "\n";
        file.close();
    }

    User User::loadFromFile(const std::string& username) {
        std::ifstream file("users.dat");
        if (!file) throw std::runtime_error("Failed to open file for reading");

        std::string fileUsername, fileNickname, fileHashedPassword;
        int fileWins;

        while (file >> fileUsername >> fileNickname >> fileHashedPassword >> fileWins) {
            if (fileUsername == username) {
                file.close();
                User user(fileUsername, fileNickname, "");
                user.hashedPassword = fileHashedPassword;
                user.wins = fileWins;
                return user;
            }
        }

        file.close();
        throw std::runtime_error("User not found");
    }

    bool User::usernameExists(const std::string& username) {
        std::ifstream file("users.dat");
        if (!file.is_open()) return false;

        std::string fileUsername, fileNickname, fileHashedPassword;
        int fileWins;

        while (file >> fileUsername >> fileNickname >> fileHashedPassword >> fileWins) {
            if (fileUsername == username) {
                file.close();
                return true; 
            }
        }

        file.close();
        return false;
    }

    bool User::verifyPassword(const std::string& password) const {
        return hashPassword(password) == hashedPassword;
    }

    void User::incrementWins() {
        wins++;
    }

    std::string User::getUsername() const {
        return username;
    }

    std::string User::getNickname() const {
        return nickname;
    }

    int User::getWins() const {
        return wins;
    }
}