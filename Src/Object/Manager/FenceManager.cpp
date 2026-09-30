#include "FenceManager.h"

FenceManager::FenceManager(void)
{
    const int INITIAL_COUNT = 0;
    const float INITIAL_OFFSET = 0.0f;

    rowCount_ = INITIAL_COUNT;
    columnCount_ = INITIAL_COUNT;
    offsetX_ = INITIAL_OFFSET;
    offsetZ_ = INITIAL_OFFSET;
}

FenceManager::~FenceManager(void)
{
    Release();
}

void FenceManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize)
{
    fenceObjects_.clear();
    fenceObjectsX_.clear();

    rowCount_ = static_cast<int>(mapData.size());

    const int EMPTY_SIZE = 0;
    const int FIRST_INDEX = 0;

    if (mapData.empty())
    {
        columnCount_ = EMPTY_SIZE;
    }
    else
    {
        columnCount_ = static_cast<int>(mapData[FIRST_INDEX].size());
    }

    const float DIVISOR_HALF = 2.0f;

    offsetX_ = -(columnCount_ * blockSize) / DIVISOR_HALF;
    offsetZ_ = -(rowCount_ * blockSize) / DIVISOR_HALF;

    const int BLOCK_TYPE_FENCE = 4;
    const int BLOCK_TYPE_FENCE_X = 5;
    const float FENCE_Y_POSITION = -40.0f;

    for (int zIndex = 0; zIndex < rowCount_; ++zIndex)
    {
        for (int xIndex = 0; xIndex < columnCount_; ++xIndex)
        {
            if (mapData[zIndex][xIndex] == BLOCK_TYPE_FENCE)
            {
                auto fenceObject = std::make_shared<FenceObject>();
                fenceObject->Init();

                VECTOR position = {
                    xIndex * blockSize + offsetX_,
                    FENCE_Y_POSITION,
                    zIndex * blockSize + offsetZ_
                };

                fenceObject->GetTransform().position = position;
                fenceObjects_.push_back(fenceObject);
            }

            if (mapData[zIndex][xIndex] == BLOCK_TYPE_FENCE_X)
            {
                auto fenceObjectX = std::make_shared<FenceObject1>();
                fenceObjectX->Init();

                VECTOR position = {
                    xIndex * blockSize + offsetX_,
                    FENCE_Y_POSITION,
                    zIndex * blockSize + offsetZ_
                };

                fenceObjectX->GetTransform().position = position;
                fenceObjectsX_.push_back(fenceObjectX);
            }
        }
    }
}

void FenceManager::Update(void)
{
    for (auto& fenceObject : fenceObjects_)
    {
        fenceObject->Update();
    }

    for (auto& fenceObjectX : fenceObjectsX_)
    {
        fenceObjectX->Update();
    }
}

void FenceManager::Draw(void)
{
    for (auto& fenceObject : fenceObjects_)
    {
        fenceObject->Draw();
    }

    for (auto& fenceObjectX : fenceObjectsX_)
    {
        fenceObjectX->Draw();
    }
}

void FenceManager::Release(void)
{
    fenceObjects_.clear();
    fenceObjectsX_.clear();
}

const std::vector<std::shared_ptr<FenceObject>>& FenceManager::GetFenceObjects(void) const
{
    return fenceObjects_;
}

const std::vector<std::shared_ptr<FenceObject1>>& FenceManager::GetFenceObjectsX(void) const
{
    return fenceObjectsX_;
}