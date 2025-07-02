#include "PlantManager.h"

PlantManager::PlantManager(void)
{
	rows_ = 0;

	cols_ = 0;

	offsetX_ = 0.0f;

	offsetZ_ = 0.0f;
}

PlantManager::~PlantManager(void)
{
}

void PlantManager::Init(const std::vector<std::vector<int>>& mapData, float blockSize)
{
	plants_.clear();

	rows_ = static_cast<int>(mapData.size());

	cols_ = mapData.empty() ? 0 : static_cast<int>(mapData[0].size());

	offsetX_ = -(cols_ * blockSize) / 2.0f;

	offsetZ_ = -(rows_ * blockSize) / 2.0f;

	for (int z = 0; z < rows_; z++)
	{
		for (int x = 0; x < cols_; x++)
		{
			if (mapData[z][x] == 1)
			{
				auto plant = std::make_shared<PlantObject>();
				plant->Init();
				pos_ = { x * blockSize + offsetX_, 0.0f, z * blockSize + offsetZ_ };
				plant->GetTransforms().pos = pos_;
				plant->SetActive(false);  // Å‰‚ÍA‚¦‚ç‚ê‚Ä‚¢‚È‚¢
				plants_.push_back(plant);
			}
		}
	}
}

void PlantManager::Update()
{
	for (auto& plant : plants_)
	{
		plant->Update();
	}
}

void PlantManager::Draw()
{
	for (auto& plant : plants_)
	{
		plant->Draw();
	}
}

void PlantManager::Release()
{
	plants_.clear();
}

const std::vector<std::shared_ptr<PlantObject>>& PlantManager::GetPlantObjects(void) const
{
	return plants_;
}


