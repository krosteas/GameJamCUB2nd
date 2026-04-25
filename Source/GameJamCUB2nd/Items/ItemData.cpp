// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemData.h"

int32 UItemData::GetValueForQuality(EItemQuality Quality) const
{
	switch (Quality)
	{
		case EItemQuality::Poor:    return FMath::RoundToInt(BaseGoldValue * 0.5f);
		case EItemQuality::Normal:  return BaseGoldValue;
		case EItemQuality::Fine:    return FMath::RoundToInt(BaseGoldValue * 1.5f);
		case EItemQuality::Perfect: return FMath::RoundToInt(BaseGoldValue * 2.5f);
		default:                    return BaseGoldValue;
	}
}

bool UItemData::HasTag(FName Tag) const
{
	return ItemTags.Contains(Tag);
}