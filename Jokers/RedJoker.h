class RedJoker : public IJokerCard
{
private:
    int power;

public:
    RedJoker(int p = 5) : power(p) {}

    // Implement interface methods
    std::string getName() override
    {
        return "Red Joker";
    }

    void execute() override
    {
    }
};