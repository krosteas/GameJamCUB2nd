// test_ShopKeeper.cpp — compile with: g++ -std=c++17 test_ShopKeeper.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>

struct MockItemData
{
    std::string Name;
    MockItemData(std::string n) : Name(n) {}
};

enum class EItemQuality { Poor, Normal, Fine, Perfect };

struct FInventorySlot
{
    MockItemData* Item = nullptr;
    EItemQuality Quality = EItemQuality::Normal;
    int Quantity = 1;
};

struct MockShopKeeper
{
    std::vector<FInventorySlot> Inventory;

    void AddItem(MockItemData* Item, EItemQuality Quality, int Quantity = 1)
    {
        if (!Item || Quantity <= 0) return;
        for (FInventorySlot& Slot : Inventory)
        {
            if (Slot.Item == Item && Slot.Quality == Quality)
            {
                Slot.Quantity += Quantity;
                return;
            }
        }
        FInventorySlot NewSlot;
        NewSlot.Item     = Item;
        NewSlot.Quality  = Quality;
        NewSlot.Quantity = Quantity;
        Inventory.push_back(NewSlot);
    }

    bool RemoveItem(MockItemData* Item, EItemQuality Quality, int Quantity = 1)
    {
        if (!Item || Quantity <= 0) return false;
        for (int i = 0; i < (int)Inventory.size(); i++)
        {
            FInventorySlot& Slot = Inventory[i];
            if (Slot.Item != Item || Slot.Quality != Quality) continue;
            if (Slot.Quantity < Quantity) return false;
            Slot.Quantity -= Quantity;
            if (Slot.Quantity == 0) Inventory.erase(Inventory.begin() + i);
            return true;
        }
        return false;
    }

    bool HasItem(MockItemData* Item, EItemQuality Quality) const
    {
        return GetItemQuantity(Item, Quality) > 0;
    }

    int GetItemQuantity(MockItemData* Item, EItemQuality Quality) const
    {
        if (!Item) return 0;
        for (const FInventorySlot& Slot : Inventory)
            if (Slot.Item == Item && Slot.Quality == Quality)
                return Slot.Quantity;
        return 0;
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
    MockItemData HealingPotion("Healing Potion");
    MockItemData RoyalWine("Royal Wine");

    std::cout << "-- Adding items --\n";
    {
        MockShopKeeper SK;
        SK.AddItem(&HealingPotion, EItemQuality::Normal);
        RunIntTest("One potion added",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Normal), 1);
        SK.AddItem(&HealingPotion, EItemQuality::Normal);
        RunIntTest("Same item+quality stacks to 2",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Normal), 2);
        SK.AddItem(&HealingPotion, EItemQuality::Perfect);
        RunIntTest("Different quality is separate slot",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Perfect), 1);
        RunIntTest("Normal quality slot unchanged",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Normal), 2);
        SK.AddItem(&RoyalWine, EItemQuality::Normal);
        RunIntTest("Different item added separately",
            SK.GetItemQuantity(&RoyalWine, EItemQuality::Normal), 1);
        RunIntTest("Inventory has 3 slots total", (int)SK.Inventory.size(), 3);
    }

    std::cout << "\n-- Adding with quantity --\n";
    {
        MockShopKeeper SK;
        SK.AddItem(&HealingPotion, EItemQuality::Fine, 5);
        RunIntTest("Added 5 at once",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Fine), 5);
        SK.AddItem(&HealingPotion, EItemQuality::Fine, 3);
        RunIntTest("Stacked 3 more to make 8",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Fine), 8);
        SK.AddItem(&HealingPotion, EItemQuality::Fine, 0);
        RunIntTest("Zero quantity ignored",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Fine), 8);
    }

    std::cout << "\n-- Removing items --\n";
    {
        MockShopKeeper SK;
        SK.AddItem(&HealingPotion, EItemQuality::Normal, 3);
        RunTest("Remove 1 succeeds",
            SK.RemoveItem(&HealingPotion, EItemQuality::Normal, 1), true);
        RunIntTest("2 remaining after remove",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Normal), 2);
        RunTest("Remove more than available fails",
            SK.RemoveItem(&HealingPotion, EItemQuality::Normal, 5), false);
        RunIntTest("Quantity unchanged after failed remove",
            SK.GetItemQuantity(&HealingPotion, EItemQuality::Normal), 2);
        RunTest("Remove remaining 2 succeeds",
            SK.RemoveItem(&HealingPotion, EItemQuality::Normal, 2), true);
        RunIntTest("Inventory empty after removing all", (int)SK.Inventory.size(), 0);
    }

    std::cout << "\n-- HasItem --\n";
    {
        MockShopKeeper SK;
        SK.AddItem(&HealingPotion, EItemQuality::Normal);
        RunTest("HasItem true for existing item",
            SK.HasItem(&HealingPotion, EItemQuality::Normal), true);
        RunTest("HasItem false for wrong quality",
            SK.HasItem(&HealingPotion, EItemQuality::Perfect), false);
        RunTest("HasItem false for missing item",
            SK.HasItem(&RoyalWine, EItemQuality::Normal), false);
        SK.RemoveItem(&HealingPotion, EItemQuality::Normal);
        RunTest("HasItem false after removing last one",
            SK.HasItem(&HealingPotion, EItemQuality::Normal), false);
    }

    std::cout << "\n-- Null safety --\n";
    {
        MockShopKeeper SK;
        SK.AddItem(nullptr, EItemQuality::Normal);
        RunIntTest("Null item not added", (int)SK.Inventory.size(), 0);
        RunTest("Remove null item returns false",
            SK.RemoveItem(nullptr, EItemQuality::Normal), false);
        RunIntTest("GetItemQuantity with null returns 0",
            SK.GetItemQuantity(nullptr, EItemQuality::Normal), 0);
    }

    return 0;
}