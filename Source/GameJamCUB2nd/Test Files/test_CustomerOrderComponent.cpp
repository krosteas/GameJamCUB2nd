// test_CustomerOrderComponent.cpp — compile with: g++ -std=c++17 test_CustomerOrderComponent.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct MockItemData
{
    std::string Name;
    MockItemData(std::string n) : Name(n) {}
};

enum class EItemQuality { Poor, Normal, Fine, Perfect };

struct MockCustomerOrderComponent
{
    MockItemData* RequestedItem = nullptr;
    EItemQuality MinimumQuality = EItemQuality::Normal;
    bool bFulfilled = false;
    int ReputationReward = 5;
    int ReputationPenalty = -10;

    bool EvaluateOffer(MockItemData* Item, EItemQuality Quality)
    {
        if (!Item || !RequestedItem) return false;
        if (bFulfilled) return false;
        if (Item != RequestedItem) return false;
        if ((int)Quality < (int)MinimumQuality) return false;
        bFulfilled = true;
        return true;
    }

    int GetReputationReward()  const { return ReputationReward; }
    int GetReputationPenalty() const { return ReputationPenalty; }

    void GenerateOrder(const std::vector<MockItemData*>& AvailableItems, EItemQuality MinQuality)
    {
        if (AvailableItems.empty()) return;
        int index = rand() % AvailableItems.size();
        RequestedItem = AvailableItems[index];
        MinimumQuality = MinQuality;
        bFulfilled = false;
    }
};

void RunTest(const std::string& TestName, bool Result, bool Expected)
{
    std::string status = (Result == Expected) ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << Result << ", expect " << Expected << ")\n";
}

void RunIntTest(const std::string& TestName, int Result, int Expected)
{
    std::string status = (Result == Expected) ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << Result << ", expect " << Expected << ")\n";
}

int main()
{
    srand(42);

    MockItemData HealingPotion("Healing Potion");
    MockItemData RoyalWine("Royal Wine");
    MockItemData ExoticMeal("Exotic Meal");

    std::cout << "-- EvaluateOffer: correct --\n";
    {
        MockCustomerOrderComponent OC;
        OC.RequestedItem = &HealingPotion;
        OC.MinimumQuality = EItemQuality::Normal;
        RunTest("Correct item at exact min quality accepted",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Normal), true);
        RunTest("Order marked fulfilled after accept", OC.bFulfilled, true);

        MockCustomerOrderComponent OC2;
        OC2.RequestedItem = &HealingPotion;
        OC2.MinimumQuality = EItemQuality::Normal;
        RunTest("Correct item at Fine quality accepted",
            OC2.EvaluateOffer(&HealingPotion, EItemQuality::Fine), true);

        MockCustomerOrderComponent OC3;
        OC3.RequestedItem = &HealingPotion;
        OC3.MinimumQuality = EItemQuality::Normal;
        RunTest("Correct item at Perfect quality accepted",
            OC3.EvaluateOffer(&HealingPotion, EItemQuality::Perfect), true);
    }

    std::cout << "\n-- EvaluateOffer: wrong item --\n";
    {
        MockCustomerOrderComponent OC;
        OC.RequestedItem = &HealingPotion;
        OC.MinimumQuality = EItemQuality::Normal;
        RunTest("Wrong item rejected",
            OC.EvaluateOffer(&RoyalWine, EItemQuality::Perfect), false);
        RunTest("Order not fulfilled after rejection", OC.bFulfilled, false);
    }

    std::cout << "\n-- EvaluateOffer: quality too low --\n";
    {
        MockCustomerOrderComponent OC;
        OC.RequestedItem = &HealingPotion;
        OC.MinimumQuality = EItemQuality::Fine;
        RunTest("Correct item at Poor quality rejected",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Poor), false);
        RunTest("Correct item at Normal quality rejected when min is Fine",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Normal), false);
        RunTest("Correct item at Fine quality accepted",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Fine), true);
    }

    std::cout << "\n-- EvaluateOffer: already fulfilled --\n";
    {
        MockCustomerOrderComponent OC;
        OC.RequestedItem = &HealingPotion;
        OC.MinimumQuality = EItemQuality::Normal;
        OC.EvaluateOffer(&HealingPotion, EItemQuality::Normal);
        RunTest("Cannot fulfill same order twice",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Normal), false);
    }

    std::cout << "\n-- EvaluateOffer: null safety --\n";
    {
        MockCustomerOrderComponent OC;
        OC.RequestedItem = nullptr;
        RunTest("Null requested item returns false",
            OC.EvaluateOffer(&HealingPotion, EItemQuality::Normal), false);

        MockCustomerOrderComponent OC2;
        OC2.RequestedItem = &HealingPotion;
        RunTest("Null offered item returns false",
            OC2.EvaluateOffer(nullptr, EItemQuality::Normal), false);
    }

    std::cout << "\n-- Rewards and penalties --\n";
    {
        MockCustomerOrderComponent OC;
        RunIntTest("Default reputation reward is 5",   OC.GetReputationReward(), 5);
        RunIntTest("Default reputation penalty is -10", OC.GetReputationPenalty(), -10);
        OC.ReputationReward = 15;
        OC.ReputationPenalty = -20;
        RunIntTest("Custom reward returns correctly",  OC.GetReputationReward(), 15);
        RunIntTest("Custom penalty returns correctly", OC.GetReputationPenalty(), -20);
    }

    std::cout << "\n-- GenerateOrder --\n";
    {
        std::vector<MockItemData*> Pool = { &HealingPotion, &RoyalWine, &ExoticMeal };
        MockCustomerOrderComponent OC;
        OC.GenerateOrder(Pool, EItemQuality::Normal);
        RunTest("Item is set after generate", OC.RequestedItem != nullptr, true);
        RunTest("Item is from the pool",
            OC.RequestedItem == &HealingPotion ||
            OC.RequestedItem == &RoyalWine ||
            OC.RequestedItem == &ExoticMeal, true);
        RunTest("Min quality set correctly",
            OC.MinimumQuality == EItemQuality::Normal, true);
        RunTest("Not fulfilled after generate", OC.bFulfilled, false);
    }
    {
        std::vector<MockItemData*> EmptyPool;
        MockCustomerOrderComponent OC;
        OC.GenerateOrder(EmptyPool, EItemQuality::Normal);
        RunTest("Empty pool leaves item as null", OC.RequestedItem == nullptr, true);
    }

    return 0;
}