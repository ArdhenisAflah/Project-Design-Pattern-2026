# Project: Balatro-Inspired Poker Game (C++)

A C++17 poker-based deck-building roguelike inspired by Balatro, featuring upgradeable hands, unique Joker effects, and a dynamic blind system.

## Project Overview

*   **Language:** C++17
*   **Architecture:** Heavily driven by Design Patterns for modularity and extensibility.
*   **Key Mechanics:**
    *   **Scoring:** Uses a "Chips x Mult" formula. Hand ranks have base stats that can be permanently upgraded via Planet Cards.
    *   **Blind System:** Players progress through Small, Big, and Boss Blinds across multiple Antes.
    *   **Jokers:** Unique cards providing passive bonuses. Managed by a unique deck to prevent duplicates.
    *   **Shop:** Appears after clearing blinds, offering Jokers, Planet Cards (upgrades), and rerolls.
    *   **Skip Blind:** Players can skip Small/Big blinds to receive "Skip Tags" (delayed rewards).

## Design Patterns

*   **State Pattern (`BlindSystem`):** Manages transitions between Small Blind, Big Blind, and various Boss types (The Hook, The Wall, The Wheel).
*   **Chain of Responsibility (`PokerHandChecker`):** A sequence of checkers detects the highest possible poker hand rank in a set of cards.
*   **Factory Pattern (`JokerFactory`):** Uses a registry (Map of Creators) to instantiate Joker objects by name efficiently without long if-else chains.
*   **Command Pattern (`RewardCommand`):** Encapsulates rewards (like Skip Tags) as objects that can be queued and executed later.
*   **Interface Pattern:** Uses `IJokerCard` for card effects and `IHandUpgrade` for hand level increments.

## 1. Class Diagram (Balatro C++ Architecture)

Semua komponen saling terhubung melalui `GameManager` sebagai orchestrator utama. Relasi antar pattern (State, Command, Factory, CoR) digambarkan di bawah ini:

```text
+---------------------------------------------------------------------------------------------------+
|                                          GameManager                                              |
|     (Central Hub: Manages playerMoney, bonusHands, and executes the RewardCommand queue)          |
+-------+---------------+---------------+---------------+---------------+---------------+-----------+
        |               |               |               |               |               |
+-------v-------+ +-----v-----+ +-------v-------+ +-----v-----+ +-------v-------+ +-----v-------+
| HandGenerator | | HandPlayer| |  BlindSystem  | |    Shop   | |  ScoringRule  | |  RewardRule |
+-------+-------+ +-----+-----+ +-------+-------+ +-----+-----+ +-------+-------+ +-------------+
| - deck|       |       |       | - currentState| | - items   | | - statsMap    | |- earnMoney()|
+-------+-------+       |       +-------+-------+ | - planets | +-------+-------+ +-------------+
        |               |               |         +-----+-----+         |
        | deals         | selects       | manages       |               | implements
        |               |               |               | uses          | IHandUpgrade
+-------v---------------v---------------v---------------v---------------v---------------------------+
|                                             Hand                                                  |
|                        (Core Data: Struct containing vector of Cards)                             |
+---------------------------------------+-----------------------------------------------------------+
                                        |
        +-------------------------------+---------------------------------------+
        |                               |                                       |
+-------v-------+      +----------------v-----------------+           +---------v---------+
|  IBlindState  |      |           ScoringRule            |           |    PlanetCard     |
+---------------+      +----------------+-----------------+           +-------------------+
| (Small, Big,  |      | - jokerManager | - checkers (CoR)|<----------| - targetHand      |
| Boss States)  |      +--------+-------+--------+--------+           | + use(Upgrade)    |
+-------+-------+               |                |                    +---------+---------+
        |                       | owns           | uses                         |
        | creates               |                |                              | updates
        |                       |                |                              |
+-------v-------+      +--------v-------+  +-----v------------+        +--------v---------+
| RewardCommand |      |  JokerManager  |  | PokerHandChecker |        |   IHandUpgrade   |
+---------------+      +--------+-------+  +------------------+        +------------------+
| (Skip Tags)   |      | - ownedJokers  |  | (Pair, Flush,etc)|        | + upgrade(rank)  |
+-------+-------+      +--------+-------+  +------------------+        +---------^--------+
        |                       |                                                |
        | queued in             | holds polymorphic objects                      | (is-a)
        |                       |                                                |
+-------v-------+      +--------v-------+          +-------------------+         |
|  GameManager  |      |   IJokerCard   |<---------|    JokerFactory   |         |
+---------------+      +--------+-------+          +-------------------+         |
                       | Red, Blue, etc |          | (Registry-based)  |         |
                       +--------+-------+          +---------+---------+         |
                                |                            |                   |
                                | draws from                 | registers         |
                       +--------v-------+          +---------v---------+         |
                       |    JokerDeck   |          |  Concrete Jokers  |---------+
                       +----------------+          +-------------------+
                       | - available    |
                       +----------------+
```

## 2. Runtime Walkthrough (1 Ante Example)

**Ante 1 Start**
- `BlindSystem` generates Tags: Small (Investment), Big (Bonus Hand).

**Small Blind Phase**
```text
=== Ante 1 - Small Blind ===
Skip Tag for this Blind: Investment Tag ($25)
1. Play Blind
2. Skip Blind (Get Tag)
Choice: 2
Blind skipped! Tag collected.
```

**Big Blind Phase**
```text
=== Ante 1 - Big Blind ===
[Tag Executed] Received $25
Target Score: 30 | Hands: 4
... Player plays hand, earns $4 reward ...
Success! Target reached.
... Shop opens ...
```

**Boss Blind Phase**
```text
=== Ante 1 - Boss Blind - The Hook ===
[Effect] Discards 2 random cards after every played hand
Target Score: 60 | Hands: 4
... Player wins ...
Success! Target reached.
... Shop opens ...
... Increment Ante to 2 ...
```

## 3. Data Lifecycle Analysis

| Variable | Scope | Lifecycle | Reset/Update Logic |
| :--- | :--- | :--- | :--- |
| `playerMoney` | `GameManager` | Persistent (Run) | Increased by `RewardRule` or `MoneySkipReward`. Decreased in `Shop`. |
| `currentAnte` | `BlindSystem` | Persistent (Run) | Incremented after Boss Blind is cleared or skipped. |
| `BASE_ATTEMPTS` | `GameManager` | Constant | Default value (4) used as base for `maxAttempts`. |
| `attemptsUsed` | `GameManager` | Local (Blind) | Resets to 0 at the start of every Played Blind. |
| `bonusHands` | `GameManager` | Temporary (Next Blind) | Set by `BonusHandCommand`. Resets to 0 after one Played Blind. |
| `pendingCommands`| `GameManager` | Transitory | Commands added selama `HandleSkip`. Dieksekusi/dikosongkan di awal blind berikutnya. |
| `handStatsMap` | `ScoringRule` | Persistent (Run) | Melacak (Chips, Mult, Level) per rank. Level naik melalui `PlanetCard`. |
| `ownedJokers` | `JokerManager`| Persistent (Run) | Ditambah via `Shop` -> `JokerFactory`. Persisten sampai akhir run (max 5). |
| `currentState` | `BlindSystem` | Dynamic | Berubah dari Small -> Big -> Boss -> Small (next Ante). |

## 4. Key Mechanics Summary

*   **Scoring:** Formula: `(Base Chips + (Level-1)*10) * (Base Mult + (Level-1)*2)`.
*   **Jokers:** Unique instances, O(1) creation melalui Factory Map Registry.
*   **Tags:** Di-generate per Ante, dipetakan secara unik ke Small dan Big Blind.
*   **Chain of Responsibility:** Digunakan oleh `ScoringRule` untuk mengecek rank kartu secara sekuensial dari yang tertinggi.

## 5. Building and Running

### Build Command
The project uses a batch script to compile all `.cpp` files in the directory:
```batch
.\build.bat
```

### Execution
```batch
.\poker.exe
```

## Core Components

*   **`GameManager`**: The central orchestrator for the game loop, money, and command execution.
*   **`ScoringRule`**: Handles the logic for `HandRank` scoring and level-based upgrades (+10 chips, +2 mult per level).
*   **`JokerDeck`**: Manages the pool of available Jokers to ensure uniqueness across the shop and player inventory.
*   **`HandGenerator`**: Manages the physical deck of playing cards, shuffling, and dealing.
*   **`HandPlayer`**: Handles user input for selecting cards via 0-based indexing.

## Development Conventions

*   **Smart Pointers:** Prefer `std::unique_ptr` for ownership of polymorphic objects (Jokers, Commands, Blind States).
*   **Indexing:** Use 0-based indexing for card selection as displayed in `CardUtils::PrintCards`.
*   **Extensibility:** 
    *   To add a new Joker: Create a class inheriting from `IJokerCard` and register it in `JokerFactory`.
    *   To add a new Skip Tag: Inherit from `RewardCommand` and update the random pool in `BlindSystem`.