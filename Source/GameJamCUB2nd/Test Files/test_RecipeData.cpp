// test_RecipeData.cpp — compile with: g++ -std=c++17 test_RecipeData.cpp -o test && ./test

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
};

struct MockRecipeData
{
    std::vector<MockRecipeStep> Steps;

    bool IsValidCraft(const std::vector<MockItemData*>& IngredientsInOrder) const
    {
        if (IngredientsInOrder.size() != Steps.size())
            return false;

        std::vector<MockRecipeStep> SortedSteps = Steps;
        std::sort(SortedSteps.begin(), SortedSteps.end(),
            [](const MockRecipeStep& A, const MockRecipeStep& B)
            { return A.OrderIndex < B.OrderIndex; });

        for (int i = 0; i < (int)SortedSteps.size(); i++)
            if (SortedSteps[i].Ingredient != IngredientsInOrder[i])
                return false;

        return true;
    }

    int GetStepCount() const { return (int)Steps.size(); }
};

void RunTest(const std::string& TestName, bool Result, bool Expected)
{
    std::string status = (Result == Expected) ? "PASS" : "FAIL";
    std::cout << "[" << status << "] " << TestName
              << " (got " << Result << ", expect " << Expected << ")\n";
}

int main()
{
    MockItemData Herbs("Herbs");
    MockItemData Water("Water");
    MockItemData Crystal("Crystal");

    MockRecipeData Recipe;
    Recipe.Steps = {
        { &Herbs,   1 },
        { &Water,   2 },
        { &Crystal, 3 }
    };

    std::cout << "-- IsValidCraft --\n";
    RunTest("Correct order",        Recipe.IsValidCraft({ &Herbs, &Water, &Crystal }), true);
    RunTest("Wrong order",          Recipe.IsValidCraft({ &Water, &Herbs, &Crystal }), false);
    RunTest("Too few ingredients",  Recipe.IsValidCraft({ &Herbs, &Water }), false);
    RunTest("Too many ingredients", Recipe.IsValidCraft({ &Herbs, &Water, &Crystal, &Herbs }), false);
    RunTest("Wrong ingredients",    Recipe.IsValidCraft({ &Crystal, &Crystal, &Crystal }), false);
    RunTest("Empty input",          Recipe.IsValidCraft({}), false);

    std::cout << "\n-- GetStepCount --\n";
    std::cout << "Step count: " << Recipe.GetStepCount() << " (expect 3)\n";

    std::cout << "\n-- Designer enters steps out of order --\n";
    MockRecipeData ShuffledRecipe;
    ShuffledRecipe.Steps = {
        { &Crystal, 3 },
        { &Herbs,   1 },
        { &Water,   2 }
    };

    RunTest("Out-of-order steps, correct craft",
        ShuffledRecipe.IsValidCraft({ &Herbs, &Water, &Crystal }), true);
    RunTest("Out-of-order steps, wrong craft",
        ShuffledRecipe.IsValidCraft({ &Crystal, &Water, &Herbs }), false);

    return 0;
}