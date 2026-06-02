#pragma once
#include <memory>
#include <string>
#include <map>
#include <functional>
#include "Jokers/IJokerCard.h"
#include "Jokers/RedJoker.h"
#include "Jokers/BlueJoker.h"

class JokerFactory
{
public:
    using CreatorFunc = std::function<std::unique_ptr<IJokerCard>()>;

    static JokerFactory& getInstance()
    {
        static JokerFactory instance;
        return instance;
    }

    void registerJoker(const std::string& name, CreatorFunc creator)
    {
        registry[name] = creator;
    }

    std::unique_ptr<IJokerCard> createJoker(const std::string& name)
    {
        // Handle exact matches or search for keywords
        for (auto const& [key, creator] : registry)
        {
            if (name.find(key) != std::string::npos)
            {
                return creator();
            }
        }
        return nullptr;
    }

private:
    JokerFactory()
    {
        // Register initial Jokers
        registerJoker("Red Joker", []() { return std::make_unique<RedJoker>(); });
        registerJoker("Blue Joker", []() { return std::make_unique<BlueJoker>(); });
        // Easy to add more later:
        // registerJoker("Jolly Joker", []() { return std::make_unique<JollyJoker>(); });
    }
    
    std::map<std::string, CreatorFunc> registry;
};