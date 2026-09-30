#include "SoundManager.h"
#include <DxLib.h>
#include <cassert>

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new SoundManager();
    }
}

SoundManager& SoundManager::GetInstance(void)
{
    return *instance_;
}

void SoundManager::Add(const TYPE type, const SOUND sound, const int data)
{
    if (sounds_.find(sound) != sounds_.end())
    {
        return;
    }

    int mode = -1;
    if (type == TYPE::BGM)
    {
        mode = DX_PLAYTYPE_LOOP;
    }
    else
    {
        mode = DX_PLAYTYPE_BACK;
    }

    sounds_.emplace(sound, SOUND_DATA{ data, type, mode });
}

void SoundManager::Play(const SOUND sound)
{
    if (sounds_.find(sound) == sounds_.end())
    {
        assert(false && "Ý’è‚µ‚Ä‚¢‚È‚¢‰¹º‚ðÄ¶‚µ‚æ‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·B");
    }

    PlaySoundMem(sounds_[sound].data, sounds_[sound].playMode);
}

void SoundManager::Stop(const SOUND sound)
{
    if (sounds_.find(sound) == sounds_.end())
    {
        assert(false && "Ý’è‚µ‚Ä‚¢‚È‚¢‰¹º‚ð’âŽ~‚µ‚æ‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·B");
    }

    StopSoundMem(sounds_[sound].data);
}

void SoundManager::Release(void)
{
    sounds_.clear();
}

void SoundManager::AdjustVolume(const SOUND sound, const int percent)
{
    if (sounds_.find(sound) == sounds_.end())
    {
        assert(false && "Ý’è‚µ‚Ä‚¢‚È‚¢‰¹º‚Ì‰¹—Ê‚ðÝ’è‚µ‚æ‚¤‚Æ‚µ‚Ä‚¢‚Ü‚·B");
    }

    const int VOLUME_MAX = 255;
    const int PERCENT_MAX = 100;

    int convertedVolume = VOLUME_MAX * percent / PERCENT_MAX;

    ChangeVolumeSoundMem(convertedVolume, sounds_[sound].data);
}

bool SoundManager::IsPlaying(SOUND sound)
{
    auto iterator = sounds_.find(sound);
    if (iterator == sounds_.end())
    {
        return false;
    }

    const int IS_PLAYING_FLAG = 1;
    int handle = iterator->second.data;

    if (CheckSoundMem(handle) == IS_PLAYING_FLAG)
    {
        return true;
    }

    return false;
}

void SoundManager::Destroy(void)
{
    Release();
    delete instance_;
}