// test_CustomerNPC.cpp — compile with: g++ -std=c++17 test_CustomerNPC.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct MockItemData
{
    std::string Name;
    MockItemData(std::string n) : Name(n) {}

    int GetValueForQuality(int Quality) const
    {
        switch (Quality)
        {
            case 0: return 5;
            case 1: return 10;
            case 2: return 15;
            case 3: return 25;
            default: return 10;
        }
    }
};

enum class EItemQuality { Poor, Normal, Fine, Perfect };
enum class ECustomerArchetype { Peasant, Noble, Witch, Knight, Merchant, King };
enum class ECustomerState { Entering, Waiting, BeingServed, Leaving };

struct MockDayManager
{
    int Gold = 0;
    int Reputation = 100;

    void OnCustomerServed(int GoldEarned, int ReputationChange)
    {
        Gold += GoldEarned;
        Reputation = std::max(0, std::min(100, Reputation + ReputationChange));
    }
};

struct MockOrderComponent
{
    MockItemData* RequestedItem = nullptr;
    EItemQuality MinQuality = EItemQuality::Normal;

    bool EvaluateOffer(MockItemData* Item, EItemQuality Quality) const
    {
        if (Item != RequestedItem) return false;
        if ((int)Quality < (int)MinQuality) return false;
        return true;
    }

    int GetReputationReward()  const { return 5; }
    int GetReputationPenalty() const { return -10; }
};

struct MockCustomerNPC
{
    ECustomerArchetype Archetype = ECustomerArchetype::Peasant;
    ECustomerState CustomerState = ECustomerState::Entering;
    float Patience = 60.0f;
    float WaitElapsed = 0.0f;
    bool bDestroyed = false;

    MockOrderComponent* OrderComponent = nullptr;
    MockDayManager* DayManager = nullptr;

    void ApplyArchetypeSettings()
    {
        switch (Archetype)
        {
            case ECustomerArchetype::Peasant:  Patience = 90.0f;  break;
            case ECustomerArchetype::Noble:    Patience = 30.0f;  break;
            case ECustomerArchetype::Witch:    Patience = 60.0f;  break;
            case ECustomerArchetype::Knight:   Patience = 45.0f;  break;
            case ECustomerArchetype::Merchant: Patience = 75.0f;  break;
            case ECustomerArchetype::King:     Patience = 20.0f;  break;
            default:                           Patience = 60.0f;  break;
        }
    }

    void StartWaiting()
    {
        WaitElapsed = 0.0f;
        CustomerState = ECustomerState::Waiting;
    }

    bool Serve(MockItemData* Item, EItemQuality Quality)
    {
        if (!Item || !OrderComponent) return false;
        if (CustomerState != ECustomerState::Waiting) return false;

        CustomerState = ECustomerState::BeingServed;
        bool bAccepted = OrderComponent->EvaluateOffer(Item, Quality);

        if (bAccepted)
        {
            if (DayManager)
            {
                int GoldEarned = Item->GetValueForQuality((int)Quality);
                DayManager->OnCustomerServed(GoldEarned, OrderComponent->GetReputationReward());
            }
        }
        else
        {
            if (DayManager)
                DayManager->OnCustomerServed(0, OrderComponent->GetReputationPenalty());
        }

        Leave(bAccepted);
        return bAccepted;
    }

    void Leave(bool bWasServed)
    {
        CustomerState = ECustomerState::Leaving;
        bDestroyed = true;
    }

    float GetPatienceFraction() const
    {
        if (Patience <= 0.0f) return 0.0f;
        return std::max(0.0f, std::min(1.0f, 1.0f - (WaitElapsed / Patience)));
    }

    void SimulateTick(float DeltaTime)
    {
        if (CustomerState != ECustomerState::Waiting) return;
        WaitElapsed += DeltaTime;
        if (WaitElapsed >= Patience)
            Leave(false);
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

void RunFloatTest(const std::string& TestName, float Result, float Expected)
{
    bool pass = fabsf(Result - Expected) < 0.01f;
    std::string status = pass ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << Result << ", expect " << Expected << ")\n";
}

int main()
{
    MockItemData HealingPotion("Healing Potion");
    MockItemData RoyalWine("Royal Wine");

    MockOrderComponent Order;
    Order.RequestedItem = &HealingPotion;
    Order.MinQuality = EItemQuality::Normal;

    std::cout << "-- Archetype patience settings --\n";
    {
        auto TestArchetype = [](ECustomerArchetype A, float Expected, const std::string& Name)
        {
            MockCustomerNPC C;
            C.Archetype = A;
            C.ApplyArchetypeSettings();
            bool pass = fabsf(C.Patience - Expected) < 0.01f;
            std::cout << "[" << (pass ? "PASS" : "FAIL") << "] "
                      << Name << " patience = " << C.Patience
                      << " (expect " << Expected << ")\n";
        };

        TestArchetype(ECustomerArchetype::Peasant,  90.0f, "Peasant");
        TestArchetype(ECustomerArchetype::Noble,    30.0f, "Noble");
        TestArchetype(ECustomerArchetype::Witch,    60.0f, "Witch");
        TestArchetype(ECustomerArchetype::Knight,   45.0f, "Knight");
        TestArchetype(ECustomerArchetype::Merchant, 75.0f, "Merchant");
        TestArchetype(ECustomerArchetype::King,     20.0f, "King");
    }

    std::cout << "\n-- Patience timer --\n";
    {
        MockCustomerNPC C;
        C.Archetype = ECustomerArchetype::Noble;
        C.ApplyArchetypeSettings();
        C.StartWaiting();

        RunFloatTest("Patience fraction is 1.0 at start",
            C.GetPatienceFraction(), 1.0f);
        for (int i = 0; i < 15; i++) C.SimulateTick(1.0f);
        RunFloatTest("Patience fraction is 0.5 at halfway",
            C.GetPatienceFraction(), 0.5f);
        for (int i = 0; i < 14; i++) C.SimulateTick(1.0f);
        RunTest("Still waiting at 29s",
            C.CustomerState == ECustomerState::Waiting, true);
        C.SimulateTick(1.0f);
        RunTest("Leaves after patience runs out",
            C.CustomerState == ECustomerState::Leaving, true);
        RunTest("Destroyed after leaving", C.bDestroyed, true);
    }

    std::cout << "\n-- Serve: correct item --\n";
    {
        MockDayManager DM;
        MockCustomerNPC C;
        C.OrderComponent = &Order;
        C.DayManager = &DM;
        C.StartWaiting();

        RunTest("Correct item accepted",
            C.Serve(&HealingPotion, EItemQuality::Normal), true);
        RunTest("Customer leaves after being served",
            C.CustomerState == ECustomerState::Leaving, true);
        RunIntTest("Gold earned from sale", DM.Gold, 10);
        RunIntTest("Reputation increased", DM.Reputation, 100);
    }

    std::cout << "\n-- Serve: wrong item --\n";
    {
        MockDayManager DM;
        MockCustomerNPC C;
        C.OrderComponent = &Order;
        C.DayManager = &DM;
        C.StartWaiting();

        RunTest("Wrong item rejected",
            C.Serve(&RoyalWine, EItemQuality::Normal), false);
        RunIntTest("No gold earned for wrong item", DM.Gold, 0);
        RunIntTest("Reputation penalised for wrong item", DM.Reputation, 90);
    }

    std::cout << "\n-- Serve: quality too low --\n";
    {
        MockDayManager DM;
        MockCustomerNPC C;
        C.OrderComponent = &Order;
        C.DayManager = &DM;
        C.StartWaiting();

        RunTest("Item with too low quality rejected",
            C.Serve(&HealingPotion, EItemQuality::Poor), false);
        RunIntTest("No gold for low quality", DM.Gold, 0);
        RunIntTest("Reputation penalised for low quality", DM.Reputation, 90);
    }

    std::cout << "\n-- Serve: wrong state --\n";
    {
        MockCustomerNPC C;
        C.OrderComponent = &Order;
        C.CustomerState = ECustomerState::Entering;

        RunTest("Cannot serve customer who is still entering",
            C.Serve(&HealingPotion, EItemQuality::Normal), false);
    }

    return 0;
}