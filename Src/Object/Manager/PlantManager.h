#pragma once

#include <vector>
#include <memory>

#include "../GardenObject/PlantObject.h"

class PlantManager
{
public:
	PlantManager(void);
	~PlantManager(void);

	void Init(const std::vector<std::vector<int>>& mapData, float blockSize);

	void Update(const VECTOR& playerPos);

	void Draw(void);

	void Release(void);

	const std::vector<std::shared_ptr<PlantObject>>& GetPlantObjects(void) const;

private:
	std::vector<std::shared_ptr<PlantObject>> plants_;

	int rows_;

	int cols_;

	float offsetX_;

	float offsetZ_;

	VECTOR pos_;
};

