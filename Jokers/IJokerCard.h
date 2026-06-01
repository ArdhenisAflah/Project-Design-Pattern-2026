#pragma once
#include <vector>
#include <memory>
#include <string>
class IJokerCard
{
public:
    virtual ~IJokerCard() = default;
    int priority;
    virtual std::string getName() = 0;
    virtual void execute() = 0; // Pure virtual function
};