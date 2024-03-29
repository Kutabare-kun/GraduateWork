#include "Animation.h"

Animation::Animation()
    : Frames(0), 
    CurrentFrameIndex(0),
    CurrentFrameTime(0.0f),
    ReleaseFirstFrame(true)
{}

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

void Animation::AddFrameAction(unsigned FrameIndex, AnimationAction Action)
{
    if (FrameIndex > Frames.size()) return;

    auto ActionKey = FrameActions.find(FrameIndex);
    if (ActionKey == FrameActions.end())
    {
        FramesWithActions.SetBit(FrameIndex);
        FrameActions.insert(std::make_pair(FrameIndex, std::vector<AnimationAction>{Action}));
    }
    else
    {
        ActionKey->second.emplace_back(Action);
    }
        
}

bool Animation::UpdateFrame(float DeltaTime)
{
    if (Frames.size() <= 1) return false;
    if (ReleaseFirstFrame)
    {
        RunActionForCurrentFrame();
        ReleaseFirstFrame = false;
        return true;
    }

    CurrentFrameTime += DeltaTime;
    if (CurrentFrameTime < GetCurrentFrame()->DisplayTimeSeconds) return false;

    CurrentFrameTime = 0.0f;
    IncrementFrame();
    RunActionForCurrentFrame();
    return true;
}

void Animation::Reset()
{
    CurrentFrameIndex = 0;
    CurrentFrameTime = 0.0f;
    ReleaseFirstFrame = true;
}

void Animation::IncrementFrame()
{
    CurrentFrameIndex = (CurrentFrameIndex + 1) % Frames.size();
}

void Animation::RunActionForCurrentFrame()
{
    if (FrameActions.empty()) return;
    if (!FramesWithActions.GetBit(CurrentFrameIndex)) return;

    auto ActionKey = FrameActions.find(CurrentFrameIndex);
    if (ActionKey == FrameActions.end()) return;

    for (auto& Action : ActionKey->second)
    {
        Action();
    }
}
