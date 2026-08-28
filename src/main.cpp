#include <iostream>
#include <memory>
#include <thread> // برای استفاده از sleep_for
#include <chrono> // برای تعریف مدت زمان
#include "MenuManager.h"
#include "GameManager.h"
#include "Terrorist.h"
#include "CT.h"
#include "GameMap.h"
#include "../tests/Tests.cpp"
using namespace CounterStrike;
using namespace std;
int main() {
    
    testWeaponBasic();
    testWeaponEdgeCases();
    testPlayerBasic();
    testPlayerEdgeCases();
    testGameMapBasic();
    testGameManagerSingleton();
    testIntegrationScenario();
    testPerformance();
    cout << "\nAll tests passed successfully!\n";

    std::this_thread::sleep_for(std::chrono::seconds(7));

    MenuManager menuManager;
    menuManager.run();

    return 0;
}