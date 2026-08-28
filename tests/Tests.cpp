#include <iostream>
#include <cassert>
#include <chrono>
#include "Weapon.h"
#include "Player.h"
#include "Terrorist.h"
#include "CT.h"
#include "GameMap.h"
#include "GameManager.h"

using namespace CounterStrike;
using namespace std;
void testWeaponBasic() {

    Weapon w(1, 30, 3000, 50, WeaponType::AK47);
    assert(w.getAmmo() == 30);
    assert(w.getPrice() == 3000);
    assert(w.getDamage() == 50);
    assert(w.getType() == WeaponType::AK47);
    cout << "testWeaponBasic passed!\n";
}

void testWeaponEdgeCases() {
    
    try {
        Weapon w(1, -5, 3000, 50, WeaponType::AK47); 
        assert(false); 
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Ammo cannot be negative");
    }

    try {
        Weapon w(1, 30, -100, 50, WeaponType::AK47); 
        assert(false); 
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Price cannot be negative");
    }

    try {
        Weapon w(1, 30, 3000, -10, WeaponType::AK47);
        assert(false); 
    } catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Damage cannot be negative");
    }

    cout << "testWeaponEdgeCases passed!\n";
}

void testPlayerBasic() {

    Player p("Ali", PlayerType::HUMAN, 1000);
    assert(p.getName() == "Ali");
    assert(p.getType() == PlayerType::HUMAN);
    assert(p.getMoney() == 1000);
    assert(p.getHealth() == 100);
    cout << "testPlayerBasic passed!\n";
}

void testPlayerEdgeCases() {
    
    Player p;
    try {
        p.setHealth(150);
        assert(false);
    } catch (std::invalid_argument&) {}

    try {
        p.setArmor(200);
        assert(false);
    } catch (std::invalid_argument&) {}

    try {
        p.setMoney(-100);
        assert(false);
    } catch (std::invalid_argument&) {}

    cout << "testPlayerEdgeCases passed!\n";
}

void testGameMapBasic() {
    
    GameMap map("Dust2", "Valve", MapStatus::DAY);
    assert(map.getMapName() == "Dust2");
    assert(map.getMapDesigner() == "Valve");
    assert(map.getMapStatus() == MapStatus::DAY);
    cout << "testGameMapBasic passed!\n";
}

void testGameManagerSingleton() {

    GameManager* gm1 = GameManager::getInstance();
    GameManager* gm2 = GameManager::getInstance();
    assert(gm1 == gm2);
    cout << "testGameManagerSingleton passed!\n";
}

void testIntegrationScenario() {
    
    auto gm = GameManager::getInstance();
    gm->create("Dust2", "Ongoing", GameMap("Dust2", "Valve", MapStatus::DAY));

    auto t1 = std::make_shared<Terrorist>("Terrorist1", PlayerType::AI, 1000);
    auto ct1 = std::make_shared<CT>("CT1", PlayerType::AI, 1000);

    gm->addPlayerToTerroristTeam(t1);
    gm->addPlayerToCTTeam(ct1);

    t1->setHealth(100);
    ct1->setHealth(90);

    gm->setGameResult("Terrorist wins!");

    assert(gm->getGameResult() == "Terrorist wins!");
    cout << "testIntegrationScenario passed!\n";
}

void testPerformance() {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();

    auto gm = GameManager::getInstance();
    for (int i = 0; i < 1000; ++i) {
        gm->addPlayerToTerroristTeam(std::make_shared<Terrorist>("Terrorist_" + std::to_string(i), PlayerType::AI, 1000));
        gm->addPlayerToCTTeam(std::make_shared<CT>("CT_" + std::to_string(i), PlayerType::AI, 1000));
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Performance Test: Adding 1000 players took " << duration.count() << " ms.\n";
}