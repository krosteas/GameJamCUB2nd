// test_CraftingComponent.cpp — compile with: g++ -std=c++17 test_CraftingComponent.cpp -o test && ./test

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
    int RequiredHeatTurns = 1;

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
    MockItemData WrongBase("Wine");

    MockRecipeData Recipe;
    Recipe.RequiredBase = &Water;
    Recipe.RequiredHeatTurns = 2;
    Recipe.Steps = {
        { &Herbs,   1, true  },
        { &Crystal, 2, false }
    };

    std::cout << "-- State transitions --\n";
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        RunTest("State is WaitingForBase after start",
            C.CraftingState == ECraftingState::WaitingForBase, true);
        RunTest("Wrong base rejected",   C.PlaceBase(&WrongBase), false);
        RunTest("Correct base accepted", C.PlaceBase(&Water), true);
        RunTest("State is AddingIngredients after base",
            C.CraftingState == ECraftingState::AddingIngredients, true);
        C.ToggleHeat();
        RunTest("State is Heating after toggle",
            C.CraftingState == ECraftingState::Heating, true);
        C.ToggleHeat();
        RunTest("State back to AddingIngredients after toggle off",
            C.CraftingState == ECraftingState::AddingIngredients, true);
    }

    std::cout << "\n-- Distill guards --\n";
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        RunTest("Distill fails with no ingredients", C.Distill(), false);
        C.AddIngredient(&Herbs, true);
        C.AddIngredient(&Crystal, false);
        RunTest("Distill succeeds even with insufficient heat turns (quality penalty instead)",
            C.Distill(), true);
        RunTest("State is Finished after distill",
            C.CraftingState == ECraftingState::Finished, true);
    }

    std::cout << "\n-- Quality calculation --\n";
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        C.AddIngredient(&Herbs, true);
        C.AddIngredient(&Crystal, false);
        C.ToggleHeat();
        C.CompleteHeatTurn();
        C.CompleteHeatTurn();
        C.Distill();
        RunQualityTest("Perfect craft", C.CalculateQuality(), EItemQuality::Perfect);
    }
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        C.AddIngredient(&Herbs, false);
        C.AddIngredient(&Crystal, false);
        C.ToggleHeat();
        C.CompleteHeatTurn();
        C.CompleteHeatTurn();
        C.Distill();
        RunQualityTest("Fine craft (missed grind)", C.CalculateQuality(), EItemQuality::Fine);
    }
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        C.AddIngredient(&Herbs, false);
        C.AddIngredient(&Crystal, false);
        C.ToggleHeat();
        C.CompleteHeatTurn();
        C.Distill();
        RunQualityTest("Normal craft (missed grind + wrong heat)",
            C.CalculateQuality(), EItemQuality::Normal);
    }
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        C.AddIngredient(&Crystal, false);
        C.AddIngredient(&Herbs, false);
        C.ToggleHeat();
        C.CompleteHeatTurn();
        C.Distill();
        RunQualityTest("Poor craft (wrong order + missed grind + wrong heat)",
            C.CalculateQuality(), EItemQuality::Poor);
    }

    std::cout << "\n-- Reset --\n";
    {
        MockCraftingComponent C;
        C.StartCrafting(&Recipe);
        C.PlaceBase(&Water);
        C.AddIngredient(&Herbs, true);
        C.ResetCrafting();
        RunTest("State is Idle after reset",
            C.CraftingState == ECraftingState::Idle, true);
        RunTest("Ingredients cleared after reset", C.AddedIngredients.empty(), true);
        RunTest("Heat turns cleared after reset",  C.HeatTurnsCompleted == 0, true);
    }

    return 0;
}