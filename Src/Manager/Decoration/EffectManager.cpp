#include "EffectManager.h"
#include <EffekseerForDXLib.h>
#include <cassert>

EffectManager* EffectManager::instance_ = nullptr;

void EffectManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new EffectManager();
    }
}

EffectManager& EffectManager::GetInstance(void)
{
    return *instance_;
}

EffectManager::EffectManager(void)
{
    int testArray[NONE_MAX] = {};
}

void EffectManager::Add(const EFFECT& effect, int data)
{
    if (effectRes_.find(effect) != effectRes_.end())
    {
        return;
    }

    effectRes_.emplace(effect, data);
}

void EffectManager::Play(
    const EFFECT& effect,
    const VECTOR& position,
    const Quaternion& quaternion,
    const float& size,
    const SoundManager::SOUND sound)
{
    if (effectRes_.find(effect) == effectRes_.end())
    {
        assert(false && "設定していないエフェクトを再生しようとしています。");
    }

    if (effectPlay_.find(effect) == effectPlay_.end())
    {
        effectPlay_.emplace(effect, PlayEffekseer3DEffect(effectRes_[effect]));
    }
    else
    {
        effectPlay_[effect] = PlayEffekseer3DEffect(effectRes_[effect]);
    }

    SyncEffect(effect, position, quaternion, size);

    if (sound != SoundManager::SOUND::NONE)
    {
        SoundManager::GetInstance().Play(sound);
    }
}

void EffectManager::Stop(const EFFECT& effect)
{
    if (effectPlay_.find(effect) == effectPlay_.end())
    {
        assert(false && "設定していないエフェクトを停止しようとしています。");
    }

    StopEffekseer3DEffect(effectPlay_[effect]);
}

void EffectManager::SyncEffect(
    const EFFECT& effect,
    const VECTOR& position,
    const Quaternion& quaternion,
    const float& size)
{
    SetScalePlayingEffekseer3DEffect(effectPlay_[effect], size, size, size);

    // 引数が長くなるためオイラー角をローカル定数で受けてから渡す
    const VECTOR eulerAngles = quaternion.ToEuler();

    SetRotationPlayingEffekseer3DEffect(
        effectPlay_[effect],
        eulerAngles.x,
        eulerAngles.y,
        eulerAngles.z
    );

    SetPosPlayingEffekseer3DEffect(
        effectPlay_[effect],
        position.x,
        position.y,
        position.z
    );
}

bool EffectManager::IsPlayEffect(const EFFECT& effect)
{
    if (effectPlay_[effect] == -1 || IsEffekseer3DEffectPlaying(effectPlay_[effect]) == -1)
    {
        return true;
    }

    return false;
}

void EffectManager::Release(void)
{
    effectRes_.clear();
}

void EffectManager::Destroy(void)
{
    Release();
    delete instance_;
}