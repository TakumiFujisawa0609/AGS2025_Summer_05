#pragma once
#include <vector>
#include <memory>
#include "../Common/Transform.h"
#include "../GardenObject/FenceObject.h"
#include "../GardenObject/FenceObjectX.h"

class FenceManager
{
public:
	FenceManager(void);
	
	~FenceManager(void);

	void Init(const std::vector<std::vector<int>>& mapData, float blockSize);

	void Update(void);

	void Draw(void);
	void Release(void);

	const std::vector<std::shared_ptr<FenceObject>>& GetFenceObjects(void) const;
	const std::vector<std::shared_ptr<FenceObjectX>>& GetFenceObjectsX(void) const;

private:
	std::vector<std::shared_ptr<FenceObject>> fences_;
	std::vector<std::shared_ptr<FenceObjectX>> fencesX_;
	int rows_, cols_;
	float offsetX_, offsetZ_;

};

