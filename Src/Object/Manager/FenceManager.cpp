#include "FenceManager.h"

FenceManager::FenceManager(void)
{
	rows_ = 0;

	cols_ = 0;

	offsetX_ = 0.0f;

	offsetZ_ = 0.0f;
}

FenceManager::~FenceManager(void)
{
	Release();
}

void FenceManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize)
{
    fences_.clear();

    rows_ = static_cast<int>(mapData.size());
    cols_ = mapData.empty() ? 0 : static_cast<int>(mapData[0].size());

    offsetX_ = -(cols_ * blockSize) / 2.0f;
    offsetZ_ = -(rows_ * blockSize) / 2.0f;

    for (int z = 0; z < rows_; ++z) {
        for (int x = 0; x < cols_; ++x) {
            if (mapData[z][x] == 4) {
                auto fne = std::make_shared<FenceObject>();
                fne->Init();
                VECTOR pos = { x * blockSize + offsetX_, 5.0f, z * blockSize + offsetZ_ };
                fne->GetTransform().pos = pos;
                fences_.push_back(fne);
            }
        }
    }
}

void FenceManager::Update(void)
{
    for (auto& fne : fences_)
    {
        fne->Update();
    }
}

void FenceManager::Draw(void)
{
    for (auto& fne : fences_)
    {
        fne->Draw();
    }
}

void FenceManager::Release(void)
{
    fences_.clear();
}

const std::vector<std::shared_ptr<FenceObject>>& FenceManager::GetFenceObjects() const
{
    return fences_;
}
