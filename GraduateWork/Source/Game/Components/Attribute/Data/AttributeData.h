#pragma once
#include <float.h>
#include <memory>

class AttributeData
{
public:
    AttributeData(float IncreaseByLevel, float BaseValue, float BuffByPercent = 1.0f);

    void Initialize(float ClampMaxPercent = 2.0f, float ClampMinPercent = 0.0f);
    /*
     * ApplyChangingBuff: Apply the changing buff to the attribute
     * @Percent: The percent of the buff
     * @return: The changing value of the buff
     */
    float ApplyChangingBuff(float Percent);
    float ApplyChangingValue(float Delta);

    void SetParent(std::shared_ptr<AttributeData> Parent) { this->Parent = Parent; }

    void LevelUp();

    const float& GetBaseValue() const { return BaseValue; }
    const float& GetCurrentValue() const { return CurrentValue; }
    const float& GetBuffByPercent() const { return BuffByPercent; }

    const float* GetCurrentValuePtr() const { return &CurrentValue; }

private:
    float IncreaseByLevel;

    float BaseValue;
    float CurrentValue;
    float BuffByPercent;

    float ClampMinPercent = 0.0f;
    float ClampMaxPercent = 0.0f;
    float ClampMinValue = 0.0f;

    std::shared_ptr<AttributeData> Parent = nullptr;
};
