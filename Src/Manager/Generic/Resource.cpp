#include "Resource.h"

#include <DxLib.h>
#include <EffekseerForDXLib.h>

Resource::Resource(void)
{
    resourceType_ = TYPE::NONE;
    filePath_ = "";

    splitCountX_ = -1;
    splitCountY_ = -1;
    imageWidth_ = -1;
    imageHeight_ = -1;

    handleId_ = -1;
    handleIds_ = nullptr;
}

Resource::Resource(TYPE resourceType, const std::string& filePath)
{
    resourceType_ = resourceType;
    filePath_ = filePath;

    splitCountX_ = -1;
    splitCountY_ = -1;
    imageWidth_ = -1;
    imageHeight_ = -1;

    handleId_ = -1;
    handleIds_ = nullptr;
}

Resource::Resource(
    TYPE resourceType,
    const std::string& filePath,
    int splitCountX,
    int splitCountY,
    int imageWidth,
    int imageHeight)
{
    resourceType_ = resourceType;
    filePath_ = filePath;
    splitCountX_ = splitCountX;
    splitCountY_ = splitCountY;
    imageWidth_ = imageWidth;
    imageHeight_ = imageHeight;

    handleId_ = -1;
    handleIds_ = nullptr;
}

Resource::~Resource(void)
{
}

void Resource::Load(void)
{
    switch (resourceType_)
    {
    case Resource::TYPE::IMAGE:
        handleId_ = LoadGraph(filePath_.c_str());
        break;

    case Resource::TYPE::IMAGES:
    {
        const int totalSplitCount = splitCountX_ * splitCountY_;

        // ハンドルを格納する配列が確保されていないとクラッシュするため動的確保
        if (handleIds_ == nullptr)
        {
            handleIds_ = new int[totalSplitCount];
        }

        // 100文字を超えないように引数を改行
        handleId_ = LoadDivGraph(
            filePath_.c_str(),
            totalSplitCount,
            splitCountX_,
            splitCountY_,
            imageWidth_,
            imageHeight_,
            handleIds_
        );
        break;
    }

    case Resource::TYPE::MASK:
        handleId_ = LoadGraph(filePath_.c_str());
        break;

    case Resource::TYPE::MODEL:
        handleId_ = MV1LoadModel(filePath_.c_str());
        break;

    case Resource::TYPE::EFFEKSEER:
        handleId_ = LoadEffekseerEffect(filePath_.c_str());
        break;

    case Resource::TYPE::SOUND:
        handleId_ = LoadSoundMem(filePath_.c_str());
        break;

    case Resource::TYPE::NONE:
    case Resource::TYPE::ANIMATION:
        // 特になし（警告回避）
        break;
    }
}

void Resource::Release(void)
{
    switch (resourceType_)
    {
    case Resource::TYPE::IMAGE:
        DeleteGraph(handleId_);
        break;

    case Resource::TYPE::IMAGES:
    {
        const int totalSplitCount = splitCountX_ * splitCountY_;

        if (handleIds_ != nullptr)
        {
            for (int index = 0; index < totalSplitCount; ++index)
            {
                DeleteGraph(handleIds_[index]);
            }
            delete[] handleIds_;
            handleIds_ = nullptr;
        }
        break;
    }

    case Resource::TYPE::MASK:
        DeleteGraph(handleId_);
        break;

    case Resource::TYPE::MODEL:
    {
        MV1DeleteModel(handleId_);

        auto modelIds = duplicateModelIds_;
        for (auto modelId : modelIds)
        {
            MV1DeleteModel(modelId);
        }
        break;
    }

    case Resource::TYPE::EFFEKSEER:
        DeleteEffekseerEffect(handleId_);
        break;

    case Resource::TYPE::SOUND:
        DeleteSoundMem(handleId_);
        break;

    case Resource::TYPE::NONE:
    case Resource::TYPE::ANIMATION:
        break;
    }
}

void Resource::CopyHandles(int* imageHandles)
{
    if (handleIds_ == nullptr)
    {
        return;
    }

    const int totalSplitCount = splitCountX_ * splitCountY_;

    for (int index = 0; index < totalSplitCount; ++index)
    {
        imageHandles[index] = handleIds_[index];
    }
}