#include "AnimationController.h"
#include <DxLib.h>
#include "../../Manager/Generic/SceneManager.h"

AnimationController::AnimationController(int modelHandleId)
{
    const int INVALID_ID = -1;

    modelHandleId_ = modelHandleId;
    playingType_ = INVALID_ID;
    isLoop_ = true;
}

AnimationController::~AnimationController(void)
{
    Release();
}

void AnimationController::AddInternal(int type, int animationIndex, float speed)
{
    const int INVALID_ID = -1;
    const float INITIAL_TIME = 0.0f;

    Animation animation;
    animation.modelHandle = INVALID_ID;
    animation.attachNumber = INVALID_ID;
    animation.animationIndex = animationIndex;
    animation.playbackSpeed = speed;
    animation.totalTime = INITIAL_TIME;
    animation.currentTime = INITIAL_TIME;
    animation.mode = MODE::INTERNAL;

    Add(type, animation);
}

void AnimationController::AddExternal(int type, const std::string& filePath, float speed)
{
    const int INVALID_ID = -1;
    const int FIRST_INDEX = 0;
    const float INITIAL_TIME = 0.0f;

    Animation animation;
    animation.modelHandle = MV1LoadModel(filePath.c_str());
    animation.attachNumber = INVALID_ID;
    animation.animationIndex = FIRST_INDEX;
    animation.playbackSpeed = speed;
    animation.totalTime = INITIAL_TIME;
    animation.currentTime = INITIAL_TIME;
    animation.mode = MODE::EXTERNAL;

    Add(type, animation);
}

void AnimationController::Add(int type, Animation animation)
{
    animations_[type] = animation;
}

void AnimationController::Play(int type, bool isLoop)
{
    if (type == playingType_)
    {
        return;
    }

    const int INVALID_ID = -1;

    if (playingType_ != INVALID_ID)
    {
        MV1DetachAnim(modelHandleId_, playingAnimation_.attachNumber);
    }

    playingAnimation_ = animations_[type];
    playingType_ = type;
    isLoop_ = isLoop;

    const float INITIAL_TIME = 0.0f;
    playingAnimation_.currentTime = INITIAL_TIME;

    if (playingAnimation_.mode == MODE::INTERNAL)
    {
        playingAnimation_.attachNumber = MV1AttachAnim(
            modelHandleId_,
            playingAnimation_.animationIndex
        );
    }
    else
    {
        playingAnimation_.attachNumber = MV1AttachAnim(
            modelHandleId_,
            playingAnimation_.animationIndex,
            playingAnimation_.modelHandle
        );
    }

    playingAnimation_.totalTime = MV1GetAttachAnimTotalTime(
        modelHandleId_,
        playingAnimation_.attachNumber
    );
}

void AnimationController::Update(void)
{
    float deltaTime = SceneManager::GetInstance().GetDeltaTime();

    playingAnimation_.currentTime += deltaTime * playingAnimation_.playbackSpeed;

    if (isLoop_)
    {
        if (playingAnimation_.currentTime >= playingAnimation_.totalTime)
        {
            const float INITIAL_TIME = 0.0f;
            playingAnimation_.currentTime = INITIAL_TIME;
        }
    }

    MV1SetAttachAnimTime(
        modelHandleId_,
        playingAnimation_.attachNumber,
        playingAnimation_.currentTime
    );
}

bool AnimationController::IsEnd(void) const
{
    if (isLoop_)
    {
        return false;
    }

    if (playingAnimation_.currentTime >= playingAnimation_.totalTime)
    {
        return true;
    }

    return false;
}

int AnimationController::GetPlayType(void) const
{
    return playingType_;
}

void AnimationController::Release(void)
{
    const int INVALID_ID = -1;

    for (auto& animationPair : animations_)
    {
        if (animationPair.second.mode == MODE::EXTERNAL)
        {
            if (animationPair.second.modelHandle != INVALID_ID)
            {
                MV1DeleteModel(animationPair.second.modelHandle);
            }
        }
    }

    if (playingType_ != INVALID_ID)
    {
        MV1DetachAnim(modelHandleId_, playingAnimation_.attachNumber);
    }

    animations_.clear();
    playingType_ = INVALID_ID;
}