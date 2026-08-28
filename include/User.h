#ifndef USER_H
#define USER_H
#include <string>

namespace CounterStrike {

    class User {
    private:
        std::string username;
        std::string nickname;
        int wins;
        std::string hashedPassword;

        std::string hashPassword(const std::string& password) const;

    public:
    
        User(const std::string& username, const std::string& nickname, const std::string& password);

        void saveToFile() const;
        static User loadFromFile(const std::string& username);
        static bool usernameExists(const std::string& username);
        bool verifyPassword(const std::string& password) const;
        void incrementWins();

        std::string getUsername() const;
        std::string getNickname() const;
        int getWins() const;
    };

}

#endif 