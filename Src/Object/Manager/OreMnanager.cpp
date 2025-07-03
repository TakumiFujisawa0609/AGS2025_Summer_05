#include "OreMnanager.h"

OreManager::OreManager(void) : rows_(0), cols_(0), offsetX_(0.0f), offsetZ_(0.0f) {}

OreManager::~OreManager(void) 
{
    Release();
}

void OreManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize) 
{
    ores_.clear();

    rows_ = static_cast<int>(mapData.size());
    cols_ = mapData.empty() ? 0 : static_cast<int>(mapData[0].size());

    offsetX_ = -(cols_ * blockSize) / 2.0f;
    offsetZ_ = -(rows_ * blockSize) / 2.0f;

    for (int z = 0; z < rows_; ++z) {
        for (int x = 0; x < cols_; ++x) {
            if (mapData[z][x] == 3) { // 3‚ªzÎ‚ð•\‚·
                auto ore = std::make_shared<OreObject>();
                ore->Init();
                VECTOR pos = { x * blockSize + offsetX_, -10.0f, z * blockSize + offsetZ_ };
                ore->GetTransform().pos = pos;
                ores_.push_back(ore);
            }
        }
    }
}

void OreManager::Update(void)
{
    for (auto& ore : ores_) {
        ore->Update();
    }
}

void OreManager::Draw(void) 
{
    for (auto& ore : ores_) {
        ore->Draw();
    }
}

void OreManager::Release(void)
{
    ores_.clear();
}

const std::vector<std::shared_ptr<OreObject>>& OreManager::GetOreObjects() const 
{
    return ores_;
}
