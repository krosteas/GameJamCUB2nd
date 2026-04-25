// test_ItemData.cpp — compile with: g++ -std=c++17 test_ItemData.cpp -o test && ./test

#include <iostream>
#include <vector>
#include <string>

enum class EItemQuality { Poor, Normal, Fine, Perfect };

struct MockItemData
{
    int32_t BaseGoldValue = 10;
    std::vector<std::string> ItemTags;

    int32_t GetValueForQuality(EItemQuality Quality) const
    {
        switch (Quality)
        {
            case EItemQuality::Poor:    return (int)(BaseGoldValue * 0.5f);
            case EItemQuality::Normal:  return BaseGoldValue;
            case EItemQuality::Fine:    return (int)(BaseGoldValue * 1.5f);
            case EItemQuality::Perfect: return (int)(BaseGoldValue * 2.5f);
            default:                    return BaseGoldValue;
        }
    }

    bool HasTag(const std::string& Tag) const
    {
        for (const auto& T : ItemTags)
            if (T == Tag) return true;
        return false;
    }
};

int main()
{
    MockItemData Item;
    Item.BaseGoldValue = 10;
    Item.ItemTags = {"healing", "exotic"};

    std::cout << "Poor:    " << Item.GetValueForQuality(EItemQuality::Poor)    << " (expect 5)\n";
    std::cout << "Normal:  " << Item.GetValueForQuality(EItemQuality::Normal)  << " (expect 10)\n";
    std::cout << "Fine:    " << Item.GetValueForQuality(EItemQuality::Fine)    << " (expect 15)\n";
    std::cout << "Perfect: " << Item.GetValueForQuality(EItemQuality::Perfect) << " (expect 25)\n";
    std::cout << "HasTag healing: " << Item.HasTag("healing") << " (expect 1)\n";
    std::cout << "HasTag cursed:  " << Item.HasTag("cursed")  << " (expect 0)\n";

    return 0;
}