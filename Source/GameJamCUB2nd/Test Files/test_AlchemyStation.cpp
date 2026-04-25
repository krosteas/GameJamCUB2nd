// test_AlchemyStation.cpp — compile with: g++ -std=c++17 test_AlchemyStation.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct MockItemData
{
    std::string Name;
    MockItemData(std::string n) : Name(n) {}
};

struct MockRecipeStep
{
    MockItemData* Ingredient = nullptr;
    int OrderIndex = 1;
    bool bRequiresGrinding = false;
};

struct MockRecipeData
{
    MockItemData* RequiredBase = nullptr;
    std::vector<MockRecipeStep> Steps;
    int RequiredHeatTurns = 2;
    MockItemData* ProducedItem = nullptr;

    int GetStepCount() const { return (int)Steps.size(); }
};

enum class EItemQuality { Poor, Normal, Fine, Perfect };
enum class ECraftingState { Idle, WaitingForBase, AddingIngredients, Heating, Distilling, Finished };

struct MockCraftingComponent
{
    ECraftingState CraftingState = ECraftingState::Idle;
    MockRecipeData* ActiveRecipe = nullptr;
    MockItemData* PlacedBase = nullptr;
    std::vector<MockItemData*> AddedIngredients;
    std::vector<bool> IngredientWasGround;
    int HeatTurnsCompleted = 0;
    bool bDistillationDone = false;
    bool bIsHeating = false;

    void StartCrafting(MockRecipeData* Recipe)
    {
        if (!Recipe) return;
        ResetCrafting();
        ActiveRecipe = Recipe;
        CraftingState = ECraftingState::WaitingForBase;
    }

    bool PlaceBase(MockItemData* Base)
    {
        if (!Base || !ActiveRecipe) return false;
        if (CraftingState != ECraftingState::WaitingForBase) return false;
        if (ActiveRecipe->RequiredBase != Base) return false;
        PlacedBase = Base;
        CraftingState = ECraftingState::AddingIngredients;
        return true;
    }

    bool AddIngredient(MockItemData* Ingredient, bool bWasGround)
    {
        if (!Ingredient || !ActiveRecipe) return false;
        if (CraftingState != ECraftingState::AddingIngredients) return false;
        if ((int)AddedIngredients.size() >= ActiveRecipe->GetStepCount()) return false;
        AddedIngredients.push_back(Ingredient);
        IngredientWasGround.push_back(bWasGround);
        return true;
    }

    void ToggleHeat()
    {
        if (CraftingState != ECraftingState::AddingIngredients &&
            CraftingState != ECraftingState::Heating) return;
        bIsHeating = !bIsHeating;
        CraftingState = bIsHeating ? ECraftingState::Heating
                                   : ECraftingState::AddingIngredients;
    }

    void CompleteHeatTurn()
    {
        if (CraftingState != ECraftingState::Heating) return;
        if (!bIsHeating) return;
        HeatTurnsCompleted++;
    }

    bool Distill()
    {
        if (!ActiveRecipe) return false;
        if ((int)AddedIngredients.size() != ActiveRecipe->GetStepCount()) return false;
        bDistillationDone = true;
        CraftingState = ECraftingState::Finished;
        return true;
    }

    void ResetCrafting()
    {
        ActiveRecipe = nullptr;
        PlacedBase = nullptr;
        AddedIngredients.clear();
        IngredientWasGround.clear();
        HeatTurnsCompleted = 0;
        bDistillationDone = false;
        bIsHeating = false;
        CraftingState = ECraftingState::Idle;
    }

    int CountMistakes() const
    {
        int Mistakes = 0;
        if (!ActiveRecipe) return Mistakes;

        std::vector<MockRecipeStep> SortedSteps = ActiveRecipe->Steps;
        std::sort(SortedSteps.begin(), SortedSteps.end(),
            [](const MockRecipeStep& A, const MockRecipeStep& B)
            { return A.OrderIndex < B.OrderIndex; });

        for (int i = 0; i < (int)SortedSteps.size(); i++)
        {
            if (i >= (int)AddedIngredients.size()) { Mistakes++; continue; }
            if (SortedSteps[i].Ingredient != AddedIngredients[i]) Mistakes++;
            if (SortedSteps[i].bRequiresGrinding && !IngredientWasGround[i]) Mistakes++;
        }

        if (HeatTurnsCompleted != ActiveRecipe->RequiredHeatTurns) Mistakes++;
        return Mistakes;
    }

    EItemQuality CalculateQuality() const
    {
        if (!ActiveRecipe || CraftingState != ECraftingState::Finished)
            return EItemQuality::Poor;
        int Mistakes = CountMistakes();
        if (Mistakes == 0) return EItemQuality::Perfect;
        if (Mistakes == 1) return EItemQuality::Fine;
        if (Mistakes == 2) return EItemQuality::Normal;
        return EItemQuality::Poor;
    }
};

struct MockAlchemyStation
{
    MockCraftingComponent CraftingComp;
    MockRecipeData* ActiveRecipe = nullptr;
    float HeatTurnDuration = 10.0f;
    float CurrentHeatElapsed = 0.0f;
    bool bHourglassActive = false;
    MockItemData* LastCraftedItem = nullptr;
    EItemQuality LastCraftedQuality = EItemQuality::Poor;

    void StartCrafting()
    {
        if (!ActiveRecipe) return;
        CraftingComp.StartCrafting(ActiveRecipe);
    }

    void OnPlaceBase(MockItemData* Base)       { CraftingComp.PlaceBase(Base); }
    void OnAddIngredient(MockItemData* Ingredient, bool bWasGround)
                                               { CraftingComp.AddIngredient(Ingredient, bWasGround); }

    void OnToggleHeat()
    {
        CraftingComp.ToggleHeat();
        if (CraftingComp.bIsHeating) StartHourglass();
        else                         StopHourglass();
    }

    void OnDistill()
    {
        bool bSuccess = CraftingComp.Distill();
        if (bSuccess) OnCraftingFinished();
    }

    void OnReset()
    {
        StopHourglass();
        CraftingComp.ResetCrafting();
    }

    void SimulateTick(float DeltaTime)
    {
        if (!bHourglassActive) return;
        CurrentHeatElapsed += DeltaTime;
        if (CurrentHeatElapsed >= HeatTurnDuration)
        {
            CurrentHeatElapsed = 0.0f;
            OnHeatTurnComplete();
        }
    }

private:

    void StartHourglass() { CurrentHeatElapsed = 0.0f; bHourglassActive = true; }
    void StopHourglass()  { CurrentHeatElapsed = 0.0f; bHourglassActive = false; }

    void OnHeatTurnComplete()
    {
        CraftingComp.CompleteHeatTurn();
        if (!CraftingComp.bIsHeating) StopHourglass();
    }

    void OnCraftingFinished()
    {
        LastCraftedQuality = CraftingComp.CalculateQuality();
        LastCraftedItem    = CraftingComp.ActiveRecipe->ProducedItem;
        StopHourglass();
        CraftingComp.ResetCrafting();
    }
};

void RunTest(const std::string& TestName, bool Result, bool Expected)
{
    std::string status = (Result == Expected) ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << Result << ", expect " << Expected << ")\n";
}

std::string QualityToString(EItemQuality Q)
{
    switch (Q)
    {
        case EItemQuality::Poor:    return "Poor";
        case EItemQuality::Normal:  return "Normal";
        case EItemQuality::Fine:    return "Fine";
        case EItemQuality::Perfect: return "Perfect";
        default:                    return "Unknown";
    }
}

void RunQualityTest(const std::string& TestName, EItemQuality Result, EItemQuality Expected)
{
    std::string status = (Result == Expected) ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << QualityToString(Result)
              << ", expect " << QualityToString(Expected) << ")\n";
}

int main()
{
    MockItemData Water("Water");
    MockItemData Herbs("Herbs");
    MockItemData Crystal("Crystal");
    MockItemData HealingPotion("Healing Potion");

    MockRecipeData Recipe;
    Recipe.RequiredBase     = &Water;
    Recipe.RequiredHeatTurns = 2;
    Recipe.ProducedItem     = &HealingPotion;
    Recipe.Steps = {
        { &Herbs,   1, true  },
        { &Crystal, 2, false }
    };

    std::cout << "-- Hourglass timer --\n";
    {
        MockAlchemyStation Station;
        Station.ActiveRecipe = &Recipe;
        Station.StartCrafting();
        Station.OnPlaceBase(&Water);
        Station.OnAddIngredient(&Herbs, true);
        Station.OnAddIngredient(&Crystal, false);
        Station.OnToggleHeat();

        RunTest("Hourglass active after toggling heat on", Station.bHourglassActive, true);

        Station.SimulateTick(9.0f);
        RunTest("No heat turn after 9s", Station.CraftingComp.HeatTurnsCompleted == 0, true);

        Station.SimulateTick(1.0f);
        RunTest("One heat turn after 10s", Station.CraftingComp.HeatTurnsCompleted == 1, true);

        Station.SimulateTick(10.0f);
        RunTest("Two heat turns after 20s", Station.CraftingComp.HeatTurnsCompleted == 2, true);

        Station.OnToggleHeat();
        RunTest("Hourglass stops after toggling heat off", Station.bHourglassActive, false);

        Station.SimulateTick(10.0f);
        RunTest("No extra turns after heat off", Station.CraftingComp.HeatTurnsCompleted == 2, true);
    }

    std::cout << "\n-- Full perfect craft --\n";
    {
        MockAlchemyStation Station;
        Station.ActiveRecipe = &Recipe;
        Station.StartCrafting();
        Station.OnPlaceBase(&Water);
        Station.OnAddIngredient(&Herbs, true);
        Station.OnAddIngredient(&Crystal, false);
        Station.OnToggleHeat();
        for (int i = 0; i < 20; i++) Station.SimulateTick(1.0f);
        Station.OnDistill();

        RunTest("Item produced after distill",
            Station.LastCraftedItem == &HealingPotion, true);
        RunQualityTest("Perfect quality on perfect craft",
            Station.LastCraftedQuality, EItemQuality::Perfect);
        RunTest("Station resets after craft",
            Station.CraftingComp.CraftingState == ECraftingState::Idle, true);
        RunTest("Hourglass stops after craft", Station.bHourglassActive, false);
    }

    std::cout << "\n-- Reset mid craft --\n";
    {
        MockAlchemyStation Station;
        Station.ActiveRecipe = &Recipe;
        Station.StartCrafting();
        Station.OnPlaceBase(&Water);
        Station.OnAddIngredient(&Herbs, true);
        Station.OnToggleHeat();
        Station.SimulateTick(5.0f);
        Station.OnReset();

        RunTest("State is Idle after reset",
            Station.CraftingComp.CraftingState == ECraftingState::Idle, true);
        RunTest("Hourglass stops after reset", Station.bHourglassActive, false);
        RunTest("Heat elapsed resets", Station.CurrentHeatElapsed == 0.0f, true);
    }

    return 0;
}