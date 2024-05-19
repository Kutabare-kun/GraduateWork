#include "AttributeData.h"

#include <raymath.h>

AttributeData::AttributeData(float IncreaseByLevel, float BaseValue, float BuffByPercent)
    : IncreaseByLevel(IncreaseByLevel), BaseValue(BaseValue), BuffByPercent(BuffByPercent)
{
    CurrentValue = BaseValue * BuffByPercent;
}

void AttributeData::Initialize(float ClampMaxPercent, float ClampMinPercent)
{
    this->ClampMaxPercent = ClampMaxPercent;
    this->ClampMinPercent = Clamp(ClampMinPercent, 0.0f, ClampMaxPercent);

    this->ClampMinValue = 0.0f;
}

float AttributeData::ApplyChangingBuff(float Percent)
{
    if (fabsf(Percent) <= FLT_EPSILON) return 0.0f;

    const float OldBuff = BuffByPercent;
    const float NewBuff = BuffByPercent + Percent;

    BuffByPercent = Clamp(NewBuff, ClampMinPercent, ClampMaxPercent);

    return BuffByPercent - OldBuff;
}

float AttributeData::ApplyChangingValue(float Delta)
{
    if (fabsf(Delta) <= FLT_EPSILON) return 0.0f;

    const float OldValue = CurrentValue;
    const float NewValue = CurrentValue + Delta;

    CurrentValue = Clamp(NewValue, ClampMinValue, Parent ? Parent->GetCurrentValue() : BaseValue * BuffByPercent);

    return CurrentValue - OldValue;
}

void AttributeData::LevelUp()
{
    BaseValue += IncreaseByLevel;
}