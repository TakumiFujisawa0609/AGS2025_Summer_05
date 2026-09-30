#include "PlantManager.h"
#include <cfloat>

PlantManager::PlantManager(void)
{
    const int INITIAL_COUNT = 0;
    const float INITIAL_OFFSET = 0.0f;

    rowCount_ = INITIAL_COUNT;
    columnCount_ = INITIAL_COUNT;
    offsetX_ = INITIAL_OFFSET;
    offsetZ_ = INITIAL_OFFSET;
}

PlantManager::~PlantManager(void)
{
}

void PlantManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize)
{
    plants_.clear();

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

    const int BLOCK_TYPE_PLANT = 1;
    const float PLANT_Y_POSITION = -10.0f;

    for (int zIndex = 0; zIndex < rowCount_; zIndex++)
    {
        for (int xIndex = 0; xIndex < columnCount_; xIndex++)
        {
            if (mapData[zIndex][xIndex] == BLOCK_TYPE_PLANT)
            {
                auto plant = std::make_shared<PlantObject>();
                plant->Init();

                position_ = {
                    xIndex * blockSize + offsetX_,
                    PLANT_Y_POSITION,
                    zIndex * blockSize + offsetZ_
                };

                plant->GetTransform().position = position_;
                plant->SetActive(false);
                plants_.push_back(plant);
            }
        }
    }
}

void PlantManager::Update(const VECTOR& playerPosition)
{
    std::shared_ptr<PlantObject> closestPlant = nullptr;
    float minimumDistance = FLT_MAX;

    const float INTERACT_DISTANCE = 50.0f;

    for (auto& plant : plants_)
    {
        float distance = VSize(VSub(plant->GetTransform().position, playerPosition));

        if (distance < INTERACT_DISTANCE && distance < minimumDistance)
        {
            minimumDistance = distance;
            closestPlant = plant;
        }
    }

    for (auto& plant : plants_)
    {
        plant->HideUI();
    }

    if (closestPlant != nullptr)
    {
        closestPlant->ShowUI();
    }

    for (auto& plant : plants_)
    {
        plant->Update();
    }
}

void PlantManager::Draw(void)
{
    for (auto& plant : plants_)
    {
        plant->Draw();
    }
}

void PlantManager::Release(void)
{
    plants_.clear();
}

const std::vector<std::shared_ptr<PlantObject>>& PlantManager::GetPlantObjects(void) const
{
    return plants_;
}