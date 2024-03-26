#include "Animation.h"

void Animation::AddFrame(int TextureID, int X, int Y, int Width, int Height, float FrameTime)
{
    Frames.emplace_back(
        TextureID, X, Y, Width, Height, FrameTime
    );
}

void Animation::AddFrame(int TextureID, const Rectangle& SourceRect, float FrameTime)
{
    Frames.emplace_back(
        TextureID, SourceRect, FrameTime
    );
}

void Animation::AddFrame(const FrameData& Frame)
{
    Frames.push_back(Frame);
}

const FrameData* Animation::GetCurrentFrame() const
{
    if (Frames.empty()) return nullptr;
    return &Frames[CurrentFrameIndex];
}

bool Animation::UpdateFrame(float DeltaTime)
{
    if (Frames.empty()) return false;

    CurrentFrameTime += DeltaTime;
    if (CurrentFrameTime < GetCurrentFrame()->DisplayTimeSeconds) return false;

    CurrentFrameTime = 0.0f;
    IncrementFrame();
    return true;
}

void Animation::Reset()
{
    CurrentFrameIndex = 0;
    CurrentFrameTime = 0.0f;
}

void Animation::IncrementFrame()
{
    CurrentFrameIndex = (CurrentFrameIndex + 1) % Frames.size();
}
