#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../../Object/GardenObject/Block.h"

class BlockManager
{
public:
    BlockManager(void);
    ~BlockManager(void);

    void Init(const std::string& csvFilePath);
    void Update(void);
    void Draw(void);
    void Release(void);

private:
    std::vector<std::unique_ptr<Block>> blocks_;

    // CSVファイル読み込み用
    std::vector<std::vector<int>> LoadCSV(const std::string& filePath);

    // ブロックサイズ（CSV1マス = 50×50の正方形）
    const float blockSize_ = 50.0f;
};
