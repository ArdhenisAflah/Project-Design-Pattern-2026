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

## Building and Running

### Build Command
The project uses a batch script to compile all `.cpp` files in the directory:
```batch
.\build.bat
```
*Note: Ensure `poker.exe` is closed before rebuilding to avoid "Permission Denied" errors.*

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
