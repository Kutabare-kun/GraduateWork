#pragma once
#include <raylib.h>
#include <vector>

struct FrameData
{
    FrameData(int NewId, int NewX, int NewY, int NewWidth, int NewHeight, float NewDisplayTimeSeconds)
        : Id(NewId), X(NewX), Y(NewY), Width(NewWidth), Height(NewHeight), DisplayTimeSeconds(NewDisplayTimeSeconds)
    {
    }

    FrameData(int NewId, const Rectangle& NewRect, float NewDisplayTimeSeconds)
        : Id(NewId), X(static_cast<int>(NewRect.x)), Y(static_cast<int>(NewRect.y)),
          Width(static_cast<int>(NewRect.width)), Height(static_cast<int>(NewRect.height)),
          DisplayTimeSeconds(NewDisplayTimeSeconds)
    {
    }

    int Id; // Texture id (retrieved from our texture allocator).
    int X; // x position of sprite in the texture.
    int Y; // y position of sprite in the texture.
    int Width; // Width of sprite.
    int Height; // Height of sprite.
    float DisplayTimeSeconds; // How long to display the frame.

    Rectangle GetRect() const
    {
        return {static_cast<float>(X), static_cast<float>(Y), static_cast<float>(Width), static_cast<float>(Height)};
    }
};

class Animation
{
public:
    Animation();

    void AddFrame(int TextureID, int X, int Y, int Width, int Height, float FrameTime);
    void AddFrame(int TextureID, const Rectangle& SourceRect, float FrameTime);
    void AddFrame(const FrameData& Frame);

    const FrameData* GetCurrentFrame() const;

    bool UpdateFrame(float DeltaTime);

    void Reset();

private:
    void IncrementFrame();

    // Stores all frames for our animation.
    std::vector<FrameData> Frames;

    // Current frame.
    int CurrentFrameIndex;

    // We use this to decide when to transition to the next frame.
    float CurrentFrameTime;
};
