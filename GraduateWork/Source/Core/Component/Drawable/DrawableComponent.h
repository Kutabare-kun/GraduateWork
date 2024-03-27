#pragma once

class DrawableComponent
{
public:
    DrawableComponent();
    virtual ~DrawableComponent();

    virtual void Draw() = 0;

    void SetSortOrder(int NewSortOrder);
    int GetSortOrder() const;

private:
    int SortOrder;
};
