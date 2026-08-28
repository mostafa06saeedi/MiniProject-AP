#ifndef MENUMANAGER_H
#define MENUMANAGER_H

#include <vector>
#include <memory>
#include "GameManager.h"
#include "GameMap.h"
#include "User.h"

namespace CounterStrike {

    class MenuManager {
    private:
        std::shared_ptr<User> currentUser; 
        bool isGameConfigured;           
        std::vector<GameMap> availableMaps; 
        GameManager* gameManager;         

        void clearScreen();
        void setConsoleColor(int color);
        void resetConsoleColor();
        void showMessage(const std::string& message, int color = 7); 

        
        void showLoginRegisterMenu(); 
        void registerUser();          
        void loginUser();            
        void logout();                

        
        void showSettings();          
        void startGame();        
        void showHistory();         
        void showUserStats();        

    public:
        MenuManager();
        void showMainMenu();          
        void run();                  
    };

}

#endif