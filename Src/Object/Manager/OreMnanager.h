#pragma once
#include <vector>
#include <memory>
#include "../Common/Transform.h"
#include "../GardenObject/OreObject.h"

class OreManager {
public:
    OreManager(void);
    ~OreManager(void);

    void Init(const std::vector<std::vector<int>>& mapData, float blockSize);
    void Update(void);
    void Draw(void);
    void Release(void);

    const std::vector<std::shared_ptr<OreObject>>& GetOreObjects() const;

private:
    std::vector<std::shared_ptr<OreObject>> ores_;
    int rows_, cols_;
    float offsetX_, offsetZ_;
};
