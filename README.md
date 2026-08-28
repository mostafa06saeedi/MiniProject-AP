# 🎮 Counter-Strike Simulation

A simplified C++ simulation of the classic Counter-Strike game, featuring team management, weapon systems, user authentication, and round-based gameplay — all backed by smart pointers and a solid test suite.

---

## ✨ Features

### 👤 User Management
- User registration and login
- Password hashing for secure authentication
- Per-user match history and statistics

### 🎯 Gameplay Mechanics
- Team creation and management (Terrorists vs. Counter-Terrorists)
- Budget-based weapon assignment for players
- Round simulation with automatic winner determination

### 🔫 Weapons
- Multiple weapon types (AK47, M4A1, AWP, and more)
- Configurable ammo count, price, and damage

### 📜 Match History
- Round-by-round result logging
- Match history and per-user stats viewer

### 🧠 Smart Pointers
- Used throughout the codebase for safer, leak-free memory management

### ✅ Testing
- Unit tests for individual components
- Integration tests for full gameplay scenarios
- Performance tests under heavy load

---

## 📂 Project Structure

```
.
├── include/          # Header files (.h)
├── src/              # Core source files (.cpp) and main.cpp
├── tests/            # Unit, integration, and performance tests
├── data/             # Data files (match history)
├── CMakeLists.txt    # Build configuration
└── .gitignore
```

---

## 🚀 Getting Started

### Option 1 — Build with CMake (recommended)
```bash
mkdir build && cd build
cmake ..
cmake --build .
./CounterStrikeSimulation
```

### Option 2 — Compile directly with g++
```bash
g++ -std=c++17 -Iinclude src/*.cpp -o CounterStrikeSimulation -lpthread
./CounterStrikeSimulation
```

> ⚠️ **Note:** `src/MenuManager.cpp` currently includes `<windows.h>` and only compiles on Windows. To build on Linux/macOS, replace that section (typically used for clearing the console or adding color) with a cross-platform equivalent.

### Using the App
1. Register or log in as a user
2. Configure your game settings and start playing
3. View match history and your personal stats

---

## 🧪 Code & Test Structure

The project includes comprehensive tests to verify correctness and performance:

| Type | Description |
|------|-------------|
| **Unit Tests** | Test individual components like `Weapon`, `Player`, and `GameManager` |
| **Integration Tests** | Simulate a full gameplay scenario with teams and rounds |
| **Performance Tests** | Measure execution time for heavy operations, e.g. adding 1000 players |

---

## 👨‍💻 Contributors
- **Mostafa** — Lead developer and sole contributor. Responsible for all stages of design, development, testing, and execution of this project.
