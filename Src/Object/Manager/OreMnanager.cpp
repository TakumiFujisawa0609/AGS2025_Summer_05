#include "OreMnanager.h"

OreManager::OreManager(void)
{
    const int INITIAL_COUNT = 0;
    const float INITIAL_OFFSET = 0.0f;

    rowCount_ = INITIAL_COUNT;
    columnCount_ = INITIAL_COUNT;
    offsetX_ = INITIAL_OFFSET;
    offsetZ_ = INITIAL_OFFSET;
}

OreManager::~OreManager(void)
{
    Release();
}

void OreManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize)
{
    oreObjects_.clear();

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

    const int BLOCK_TYPE_ORE = 3;
    const float ORE_Y_POSITION = -10.0f;

    for (int zIndex = 0; zIndex < rowCount_; ++zIndex)
    {
        for (int xIndex = 0; xIndex < columnCount_; ++xIndex)
        {
            if (mapData[zIndex][xIndex] == BLOCK_TYPE_ORE)
            {
                auto oreObject = std::make_shared<OreObject>();
                oreObject->Init();

                VECTOR position = {
                    xIndex * blockSize + offsetX_,
                    ORE_Y_POSITION,
                    zIndex * blockSize + offsetZ_
                };

                oreObject->GetTransform().position = position;
                oreObjects_.push_back(oreObject);
            }
        }
    }
}

void OreManager::Update(void)
{
    for (auto& oreObject : oreObjects_)
    {
        oreObject->Update();
    }
}

void OreManager::Draw(void)
{
    for (auto& oreObject : oreObjects_)
    {
        oreObject->Draw();
    }
}

void OreManager::Release(void)
{
    oreObjects_.clear();
}

const std::vector<std::shared_ptr<OreObject>>& OreManager::GetOreObjects(void) const
{
    return oreObjects_;
}