// test_GameLoop.cpp — compile with: g++ -std=c++17 test_GameLoop.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct MockItemData
{
    std::string Name;
    MockItemData(std::string n) : Name(n) {}
};

enum class EItemQuality { Poor, Normal, Fine, Perfect };

struct MockRecipeData
{
    MockItemData* ProducedItem = nullptr;
};

struct FFeastOrder
{
    MockItemData* RequestedItem = nullptr;
    EItemQuality MinimumQuality = EItemQuality::Normal;
    bool bFulfilled = false;
};

struct MockFeastManager
{
    int FeastOrderCount = 3;
    std::vector<MockRecipeData*> KnownRecipes;
    std::vector<FFeastOrder> CurrentOrders;
    bool bFeastActive = false;

    void UnlockRecipe(MockRecipeData* Recipe)
    {
        if (!Recipe) return;
        for (auto* R : KnownRecipes)
            if (R == Recipe) return;
        KnownRecipes.push_back(Recipe);
    }

    void BeginFeast()
    {
        if (KnownRecipes.empty()) return;
        CurrentOrders.clear();
        GenerateOrders();
        bFeastActive = true;
    }

    void GenerateOrders()
    {
        std::vector<MockRecipeData*> Shuffled = KnownRecipes;
        for (int i = (int)Shuffled.size() - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            std::swap(Shuffled[i], Shuffled[j]);
        }
        int OrdersToGenerate = std::min(FeastOrderCount, (int)Shuffled.size());
        for (int i = 0; i < OrdersToGenerate; i++)
        {
            FFeastOrder Order;
            Order.RequestedItem  = Shuffled[i]->ProducedItem;
            Order.MinimumQuality = EItemQuality::Normal;
            Order.bFulfilled     = false;
            CurrentOrders.push_back(Order);
        }
    }

    bool SubmitItem(MockItemData* Item, EItemQuality Quality)
    {
        if (!Item || !bFeastActive) return false;
        for (FFeastOrder& Order : CurrentOrders)
        {
            if (Order.bFulfilled) continue;
            if (Order.RequestedItem != Item) continue;
            if (Quality < Order.MinimumQuality) return false;
            Order.bFulfilled = true;
            return true;
        }
        return false;
    }

    int EvaluateFeast()
    {
        int Failures = 0;
        for (const FFeastOrder& Order : CurrentOrders)
            if (!Order.bFulfilled) Failures++;
        bFeastActive = false;
        return Failures;
    }
};

enum class EDayPhase { NotStarted, WorkDay, FeastDay, EndOfDay, GameOver };

struct MockDayManager
{
    float DayDuration = 600.0f;
    int MinCustomersPerDay = 3;
    float ExtraCustomerTimeThreshold = 120.0f;
    int ReputationPenaltyPerFailure = 10;
    int ExileReputationThreshold = 0;
    int CurrentDay = 1;
    float DayElapsed = 0.0f;
    EDayPhase DayPhase = EDayPhase::NotStarted;
    int Gold = 0;
    int Reputation = 100;
    int CustomersSpawnedToday = 0;
    MockFeastManager* FeastManager = nullptr;

    bool IsFeastDay() const { return CurrentDay % 7 == 0; }
    float GetTimeRemaining() const { return std::max(0.0f, DayDuration - DayElapsed); }

    void StartDay()
    {
        DayElapsed = 0.0f;
        CustomersSpawnedToday = 0;
        DayPhase = IsFeastDay() ? EDayPhase::FeastDay : EDayPhase::WorkDay;
        for (int i = 0; i < MinCustomersPerDay; i++) TrySpawnCustomer();
        if (IsFeastDay() && FeastManager) FeastManager->BeginFeast();
    }

    void EndDay()
    {
        DayPhase = EDayPhase::EndOfDay;
        if (IsFeastDay() && FeastManager)
        {
            int Failures = FeastManager->EvaluateFeast();
            ModifyReputation(-(Failures * ReputationPenaltyPerFailure));
        }
        if (Reputation <= ExileReputationThreshold) { TriggerGameOver(); return; }
        AdvanceDay();
    }

    void AdvanceDay() { CurrentDay++; StartDay(); }

    void AddGold(int Amount) { Gold += Amount; }

    void ModifyReputation(int Amount)
    {
        Reputation = std::max(0, std::min(100, Reputation + Amount));
    }

    void OnCustomerServed(int GoldEarned, int ReputationChange)
    {
        AddGold(GoldEarned);
        ModifyReputation(ReputationChange);
    }

    void SimulateTick(float DeltaTime)
    {
        if (DayPhase != EDayPhase::WorkDay && DayPhase != EDayPhase::FeastDay) return;
        DayElapsed += DeltaTime;
        TrySpawnCustomer();
        if (DayElapsed >= DayDuration) EndDay();
    }

    void TrySpawnCustomer()
    {
        bool bBelowMinimum = CustomersSpawnedToday < MinCustomersPerDay;
        bool bTimeForExtra = GetTimeRemaining() > ExtraCustomerTimeThreshold;
        if (!bBelowMinimum && !bTimeForExtra) return;
        CustomersSpawnedToday++;
    }

    void TriggerGameOver() { DayPhase = EDayPhase::GameOver; }
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
    MockItemData StrangeBrew("Strange Brew");

    MockRecipeData RecipePotion;  RecipePotion.ProducedItem  = &HealingPotion;
    MockRecipeData RecipeWine;    RecipeWine.ProducedItem    = &RoyalWine;
    MockRecipeData RecipeMeal;    RecipeMeal.ProducedItem    = &ExoticMeal;
    MockRecipeData RecipeBrew;    RecipeBrew.ProducedItem    = &StrangeBrew;

    std::cout << "-- FeastManager: recipe unlocking --\n";
    {
        MockFeastManager FM;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);
        RunIntTest("Two recipes unlocked", (int)FM.KnownRecipes.size(), 2);
        FM.UnlockRecipe(&RecipePotion);
        RunIntTest("Duplicate unlock ignored", (int)FM.KnownRecipes.size(), 2);
    }

    std::cout << "\n-- FeastManager: order generation --\n";
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 3;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);
        FM.UnlockRecipe(&RecipeMeal);
        FM.UnlockRecipe(&RecipeBrew);
        FM.BeginFeast();
        RunIntTest("3 orders generated from 4 recipes", (int)FM.CurrentOrders.size(), 3);
        RunTest("Feast is active after begin", FM.bFeastActive, true);
    }
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 3;
        FM.UnlockRecipe(&RecipePotion);
        FM.BeginFeast();
        RunIntTest("Only 1 order when only 1 recipe known", (int)FM.CurrentOrders.size(), 1);
    }
    {
        MockFeastManager FM;
        FM.BeginFeast();
        RunTest("Feast does not start with no recipes", FM.bFeastActive, false);
    }

    std::cout << "\n-- FeastManager: submitting items --\n";
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 2;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);
        FM.BeginFeast();
        MockItemData* FirstItem  = FM.CurrentOrders[0].RequestedItem;
        MockItemData* SecondItem = FM.CurrentOrders[1].RequestedItem;
        RunTest("Correct item at Normal quality accepted",
            FM.SubmitItem(FirstItem, EItemQuality::Normal), true);
        RunTest("Same order cannot be fulfilled twice",
            FM.SubmitItem(FirstItem, EItemQuality::Perfect), false);
        RunTest("Item with too low quality rejected",
            FM.SubmitItem(SecondItem, EItemQuality::Poor), false);
        RunTest("Item not in orders rejected",
            FM.SubmitItem(&StrangeBrew, EItemQuality::Perfect), false);
        RunTest("Correct item at Fine quality accepted",
            FM.SubmitItem(SecondItem, EItemQuality::Fine), true);
    }

    std::cout << "\n-- FeastManager: evaluation --\n";
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 2;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);
        FM.BeginFeast();
        MockItemData* FirstItem = FM.CurrentOrders[0].RequestedItem;
        FM.SubmitItem(FirstItem, EItemQuality::Normal);
        RunIntTest("1 failure when 1 order unfulfilled", FM.EvaluateFeast(), 1);
        RunTest("Feast inactive after evaluation", FM.bFeastActive, false);
    }
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 2;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);
        FM.BeginFeast();
        for (auto& Order : FM.CurrentOrders)
            FM.SubmitItem(Order.RequestedItem, EItemQuality::Perfect);
        RunIntTest("0 failures when all orders fulfilled", FM.EvaluateFeast(), 0);
    }

    std::cout << "\n-- DayManager: feast day detection --\n";
    {
        MockDayManager DM;
        DM.CurrentDay = 1;  RunTest("Day 1 is not feast day",  DM.IsFeastDay(), false);
        DM.CurrentDay = 6;  RunTest("Day 6 is not feast day",  DM.IsFeastDay(), false);
        DM.CurrentDay = 7;  RunTest("Day 7 is feast day",      DM.IsFeastDay(), true);
        DM.CurrentDay = 14; RunTest("Day 14 is feast day",     DM.IsFeastDay(), true);
        DM.CurrentDay = 8;  RunTest("Day 8 is not feast day",  DM.IsFeastDay(), false);
    }

    std::cout << "\n-- DayManager: gold and reputation --\n";
    {
        MockDayManager DM;
        DM.AddGold(50);
        RunIntTest("Gold added correctly", DM.Gold, 50);
        DM.ModifyReputation(-30);
        RunIntTest("Reputation reduced correctly", DM.Reputation, 70);
        DM.ModifyReputation(50);
        RunIntTest("Reputation clamped at 100", DM.Reputation, 100);
        DM.ModifyReputation(-200);
        RunIntTest("Reputation clamped at 0", DM.Reputation, 0);
    }

    std::cout << "\n-- DayManager: customer spawning --\n";
    {
        MockDayManager DM;
        DM.StartDay();
        RunIntTest("3 customers spawned at start of day", DM.CustomersSpawnedToday, 3);
        DM.SimulateTick(1.0f);
        RunIntTest("Extra customer spawned while time remains", DM.CustomersSpawnedToday, 4);
        DM.DayElapsed = 490.0f;
        DM.SimulateTick(1.0f);
        RunIntTest("No extra customer when time running out", DM.CustomersSpawnedToday, 4);
    }

    std::cout << "\n-- DayManager: day advance --\n";
    {
        MockDayManager DM;
        DM.StartDay();
        RunIntTest("Starts on day 1", DM.CurrentDay, 1);
        for (int i = 0; i < 600; i++) DM.SimulateTick(1.0f);
        RunIntTest("Advances to day 2 after full day", DM.CurrentDay, 2);
    }

    std::cout << "\n-- DayManager: game over on exile --\n";
    {
        MockDayManager DM;
        DM.Reputation = 10;
        DM.ModifyReputation(-10);
        RunIntTest("Reputation at 0", DM.Reputation, 0);
        DM.StartDay();
        for (int i = 0; i < 600; i++) DM.SimulateTick(1.0f);
        RunTest("Game over triggered when reputation hits 0",
            DM.DayPhase == EDayPhase::GameOver, true);
    }

    std::cout << "\n-- Full week simulation --\n";
    {
        MockFeastManager FM;
        FM.FeastOrderCount = 2;
        FM.UnlockRecipe(&RecipePotion);
        FM.UnlockRecipe(&RecipeWine);

        MockDayManager DM;
        DM.FeastManager = &FM;

        for (int day = 1; day <= 6; day++)
        {
            DM.StartDay();
            for (int i = 0; i < 600; i++) DM.SimulateTick(1.0f);
        }

        RunIntTest("On day 7 after 6 days", DM.CurrentDay, 7);
        RunTest("Day 7 is feast day", DM.IsFeastDay(), true);
        RunTest("Feast active on day 7", FM.bFeastActive, true);

        for (auto& Order : FM.CurrentOrders)
            FM.SubmitItem(Order.RequestedItem, EItemQuality::Perfect);

        for (int i = 0; i < 600; i++) DM.SimulateTick(1.0f);

        RunIntTest("Reputation unchanged after perfect feast", DM.Reputation, 100);
        RunTest("Advances to day 8 after feast", DM.CurrentDay == 8, true);
    }

    return 0;
}