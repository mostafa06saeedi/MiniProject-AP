#include "MenuManager.h"
#include "Weapon.h" 
#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>
#include <limits>
#include "Terrorist.h"
#include "CT.h"
#include <vector>
#include <random>

using namespace CounterStrike;
using namespace std;
class Player {
    
private:
    std::vector<Weapon> weapons; 

public:
    const std::vector<Weapon>& getWeapons() const; 
};

using namespace CounterStrike;
using namespace std;

MenuManager::MenuManager() : isGameConfigured(false) {
    availableMaps = GameMap::createDefaultMaps();
    gameManager = GameManager::getInstance();
}

void MenuManager::clearScreen() {
    system("cls");
}

void MenuManager::setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void MenuManager::resetConsoleColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void MenuManager::showMainMenu() {
    int choice;
    do {
        clearScreen();
        cout << "===== Counter Strike Menu =====" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Settings" << endl;
        cout << "3. View History" << endl;
        cout << "4. User Stats" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            if (!isGameConfigured) {
                cout << "Please configure settings first!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
            } else {
                startGame();
            }
            break;
        case 2:
            showSettings();
            break;
        case 3:
            showHistory();
            break;
        case 4:
            showUserStats();
            break;
        case 5:
            logout();
            return; 
        default:
            cout << "Invalid choice!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
}

void MenuManager::showLoginRegisterMenu() {
    int choice;
    do {
        clearScreen();
        cout << "===== Login/Register Menu =====" << endl;
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            if (currentUser) {
                showMainMenu(); 
            }
            break;
        case 3:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
}

void MenuManager::registerUser() {
    string username, nickname, password;
    cout << "Enter username: ";
    cin >> username;

    if (User::usernameExists(username)) {
        cout << "Username already exists!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return;
    }

    cout << "Enter nickname: ";
    cin >> nickname;
    cout << "Enter password: ";
    cin >> password;

    User newUser(username, nickname, password);
    newUser.saveToFile();
    cout << "Registration successful!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void MenuManager::loginUser() {
    string username, password;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    try {
        User user = User::loadFromFile(username);
        if (user.verifyPassword(password)) {
            currentUser = make_shared<User>(user);
            cout << "Login successful! Welcome " << user.getNickname() << endl;
            this_thread::sleep_for(chrono::seconds(2));
        } else {
            cout << "Invalid password!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    } catch (const std::exception& e) {
        cout << "User not found!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void MenuManager::logout() {
    currentUser.reset();
    cout << "Logged out successfully!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
}
    
void MenuManager::showSettings() {
    clearScreen();
    cout << "Available Maps:" << endl;
    for (size_t i = 0; i < availableMaps.size(); ++i) {
        cout << i + 1 << ". " << availableMaps[i].getMapName() << endl;
    }
    int mapChoice;
    cout << "Select a map (1-" << availableMaps.size() << "): ";
    while (!(cin >> mapChoice) || mapChoice < 1 || mapChoice > availableMaps.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Select a valid map number: ";
    }
    GameMap selectedMap = availableMaps[mapChoice - 1];

    int terrorists, cts;
    float ratio;
    do {
        cout << "Enter number of Terrorists (min 1): ";
        while (!(cin >> terrorists) || terrorists < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a positive number: ";
        }
        cout << "Enter number of CTs (min 1): ";
        while (!(cin >> cts) || cts < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Enter a positive number: ";
        }
        ratio = static_cast<float>(terrorists) / cts;
        if (ratio < 0.95f || ratio > 1.05f) {
            cout << "Team ratio must be between 0.95 and 1.05!" << endl;
        }
    } while (ratio < 0.95f || ratio > 1.05f);

    int terroristMoney, ctMoney;
    cout << "Enter starting money for Terrorists: ";
    while (!(cin >> terroristMoney) || terroristMoney < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter a non-negative number: ";
    }

    cout << "Enter starting money for CTs: ";
    while (!(cin >> ctMoney) || ctMoney < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Enter a non-negative number: ";
    }

    gameManager->create(selectedMap.getMapName(), "Ongoing", selectedMap);

    for (int i = 0; i < terrorists; ++i) {
        auto terrorist = make_shared<Terrorist>("Terrorist_" + to_string(i), PlayerType::AI, terroristMoney);
        gameManager->addPlayerToTerroristTeam(terrorist);
    }
    for (int i = 0; i < cts; ++i) {
        auto ct = make_shared<CT>("CT_" + to_string(i), PlayerType::AI, ctMoney);
        gameManager->addPlayerToCTTeam(ct);
    }
    isGameConfigured = true;
    cout << "Settings applied!" << endl;
    this_thread::sleep_for(chrono::seconds(2));
}

void MenuManager::startGame() {
    auto& terrorists = gameManager->getTerroristTeam();
    auto& cts = gameManager->getCTTeam();
    int tPointer = 0, ctPointer = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    
    std::vector<Weapon> weapons = {
        Weapon(1, 30, 300, 50, WeaponType::AK47),
        Weapon(2, 20, 250, 40, WeaponType::M4A1),
        Weapon(3, 10, 475, 90, WeaponType::AWP),
        Weapon(4, 7, 70, 70, WeaponType::DEAGLE),
        Weapon(5, 35, 150, 30, WeaponType::UMP45)
    };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, weapons.size() - 1);

    for (auto& player : terrorists) {
        bool weaponAssigned = false;
        while (!weaponAssigned) {
            int randomIndex = dist(gen);
            const Weapon& selectedWeapon = weapons[randomIndex];
            if (player->getMoney() >= selectedWeapon.getPrice()) {
                player->addWeapon(selectedWeapon);
                player->setMoney(player->getMoney() - selectedWeapon.getPrice());
                weaponAssigned = true;
            }
        }
    }

    for (auto& player : cts) {
        bool weaponAssigned = false;
        while (!weaponAssigned) {
            int randomIndex = dist(gen);
            const Weapon& selectedWeapon = weapons[randomIndex];
            if (player->getMoney() >= selectedWeapon.getPrice()) {
                player->addWeapon(selectedWeapon);
                player->setMoney(player->getMoney() - selectedWeapon.getPrice());
                weaponAssigned = true;
            }
        }
    }

    while (!terrorists.empty() && !cts.empty()) {
        if (tPointer >= terrorists.size()) tPointer = 0;
        if (ctPointer >= cts.size()) ctPointer = 0;

        auto& tPlayer = terrorists[tPointer];
        auto& ctPlayer = cts[ctPointer];

        int tPower = tPlayer->getMoney();
        for (const auto& weapon : tPlayer->getWeapons()) {
            tPower += weapon.getAmmo() * weapon.getDamage();
        }

        int ctPower = ctPlayer->getMoney();
        for (const auto& weapon : ctPlayer->getWeapons()) {
            ctPower += weapon.getAmmo() * weapon.getDamage();
        }

        if (tPower > ctPower) {
            SetConsoleTextAttribute(hConsole, 12); 
            cout << "[Terrorist] " << tPlayer->getName() << " damaged [CT] " << ctPlayer->getName() << endl;
            ctPlayer->setHealth(max(0, ctPlayer->getHealth() - (tPower - ctPower)));
            if (ctPlayer->getHealth() <= 0) {
                cout << "[CT] " << ctPlayer->getName() << " defeated!" << endl;
                cts.erase(cts.begin() + ctPointer);
            } else {
                ctPointer++;
            }
        } else if (ctPower > tPower) {
            SetConsoleTextAttribute(hConsole, 9); 
            cout << "[CT] " << ctPlayer->getName() << " damaged [Terrorist] " << tPlayer->getName() << endl;
            tPlayer->setHealth(max(0, tPlayer->getHealth() - (ctPower - tPower)));
            if (tPlayer->getHealth() <= 0) {
                cout << "[Terrorist] " << tPlayer->getName() << " defeated!" << endl;
                terrorists.erase(terrorists.begin() + tPointer);
            } else {
                tPointer++;
            }
        } else {
            SetConsoleTextAttribute(hConsole, 12); 
            cout << "[Terrorist] " << tPlayer->getName() << " and ";
            SetConsoleTextAttribute(hConsole, 9); 
            cout << "[CT] " << ctPlayer->getName() << " both damaged!" << endl;

            tPlayer->setHealth(tPlayer->getHealth() - 10);
            ctPlayer->setHealth(ctPlayer->getHealth() - 10);

            if (tPlayer->getHealth() <= 0) {
                SetConsoleTextAttribute(hConsole, 12); 
                cout << "[Terrorist] " << tPlayer->getName() << " defeated!" << endl;
                terrorists.erase(terrorists.begin() + tPointer);
            } else {
                tPointer++;
            }

            if (ctPlayer->getHealth() <= 0) {
                SetConsoleTextAttribute(hConsole, 9);
                cout << "[CT] " << ctPlayer->getName() << " defeated!" << endl;
                cts.erase(cts.begin() + ctPointer);
            } else {
                ctPointer++;
            }
        }

        SetConsoleTextAttribute(hConsole, 7);
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    string winner;
    if (terrorists.empty() && cts.empty()) {
        winner = "Draw";
    } else if (terrorists.empty()) {
        winner = "CT";
    } else {
        winner = "Terrorist";
    }
    
    gameManager->setGameResult(winner + " wins!");
    cout << "Game Over! Winner: " << winner << endl;
    
    if (currentUser) {
        ofstream history(currentUser->getUsername() + "_history.txt", ios::app);
        if (winner == "CT") {
            history << "0" << endl;
        } else if (winner == "Terrorist") {
            history << "1" << endl;
        } else {
            history << "2" << endl;
        }
        history.close();
    } else {
    
        ofstream history("history.txt", ios::app);
        if (winner == "CT") {
            history << "0" << endl;
        } else if (winner == "Terrorist") {
            history << "1" << endl;
        } else {
            history << "2" << endl;
        }
        history.close();
    }
    
    system("pause");
}    

void MenuManager::showHistory() {
    clearScreen();

    if (!currentUser) {
        cout << "No user logged in!" << endl;
        system("pause");
        return;
    }

    ifstream history(currentUser->getUsername() + "_history.txt");
    if (!history.is_open()) {
        cout << "No history found for this user!" << endl;
        system("pause");
        return;
    }

    int round = 1;
    int result;
    cout << "===== Match History for " << currentUser->getUsername() << " =====" << endl;
    while (history >> result) {
        cout << "Round " << round++ << ": ";
        if (result == 0) {
            cout << "Winner: CT" << endl;
        } else if (result == 1) {
            cout << "Winner: Terrorist" << endl;
        } else {
            cout << "Draw" << endl;
        }
    }
    history.close();
    system("pause");
}

void MenuManager::showUserStats() {
    clearScreen();

    if (!currentUser) {
        cout << "No user logged in!" << endl;
        system("pause");
        return;
    }

    ifstream history(currentUser->getUsername() + "_history.txt");
    if (!history.is_open()) {
        cout << "No stats available for this user!" << endl;
        system("pause");
        return;
    }

    int ctWins = 0, terroristWins = 0, draws = 0;
    int result;
    while (history >> result) {
        if (result == 0) {
            ctWins++;
        } else if (result == 1) {
            terroristWins++;
        } else {
            draws++;
        }
    }

    cout << "===== User Stats =====" << endl;
    cout << "Username: " << currentUser->getUsername() << endl; 
    cout << "CT Wins: " << ctWins << endl;
    cout << "Terrorist Wins: " << terroristWins << endl;
    cout << "Draws: " << draws << endl;
    history.close();
    system("pause");
}

void MenuManager::run() {
    showLoginRegisterMenu(); 
    if (currentUser) {   
        showMainMenu();      
    }
}