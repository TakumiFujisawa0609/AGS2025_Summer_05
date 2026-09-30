#include "BlockManager.h"
#include <fstream>
#include <sstream>

BlockManager::BlockManager(void)
{
}

BlockManager::~BlockManager(void)
{
    Release();
}

void BlockManager::Init(const std::string& csvFilePath)
{
    mapData_ = LoadCSV(csvFilePath);

    int rowCount = static_cast<int>(mapData_.size());

    const int EMPTY_SIZE = 0;
    const int FIRST_INDEX = 0;

    int columnCount = mapData_.empty() ? EMPTY_SIZE : static_cast<int>(mapData_[FIRST_INDEX].size());

    const float DIVISOR_HALF = 2.0f;

    // 原点を中央にずらすためのオフセット
    float offsetX = -(columnCount * blockSize_) / DIVISOR_HALF;
    float offsetZ = -(rowCount * blockSize_) / DIVISOR_HALF;

    const float BLOCK_Y_POSITION = -50.0f;
    const float DEFAULT_ALPHA = 0.3f;
    const float ROAD_ALPHA = 0.255f;

    const int CELL_TYPE_DIRT = 1;
    const int CELL_TYPE_GRASS_MIN = 2;
    const int CELL_TYPE_GRASS_MAX = 5;
    const int CELL_TYPE_ROAD = 6;

    for (int zIndex = 0; zIndex < rowCount; ++zIndex)
    {
        for (int xIndex = 0; xIndex < columnCount; ++xIndex)
        {
            int cellType = mapData_[zIndex][xIndex];

            // オフセットを加味した位置
            VECTOR position = VGet(
                xIndex * blockSize_ + offsetX,
                BLOCK_Y_POSITION,
                zIndex * blockSize_ + offsetZ
            );

            if (cellType == CELL_TYPE_DIRT)
            {
                blocks_.emplace_back(std::make_unique<Block>(
                    ResourceManager::SRC::BLOCK_DIRT,
                    position,
                    blockSize_,
                    DEFAULT_ALPHA
                ));
            }
            else if (cellType >= CELL_TYPE_GRASS_MIN && cellType <= CELL_TYPE_GRASS_MAX)
            {
                blocks_.emplace_back(std::make_unique<Block>(
                    ResourceManager::SRC::BLOCK_GRASS,
                    position,
                    blockSize_,
                    DEFAULT_ALPHA
                ));
            }
            else if (cellType == CELL_TYPE_ROAD)
            {
                blocks_.emplace_back(std::make_unique<Block>(
                    ResourceManager::SRC::BLOCK_ROAD,
                    position,
                    blockSize_,
                    ROAD_ALPHA
                ));
            }
            else
            {
                // その他のセルタイプは何もしない
            }
        }
    }
}

void BlockManager::Update(void)
{
    for (auto& block : blocks_)
    {
        if (block != nullptr)
        {
            block->Update();
        }
    }
}

void BlockManager::Draw(void)
{
    for (auto& block : blocks_)
    {
        if (block != nullptr)
        {
            block->Draw();
        }
    }
}

void BlockManager::Release(void)
{
    blocks_.clear();
}

const std::vector<std::vector<int>>& BlockManager::GetMapData(void) const
{
    return mapData_;
}

std::vector<std::vector<int>> BlockManager::LoadCSV(const std::string& filePath)
{
    std::vector<std::vector<int>> data;
    std::ifstream file(filePath);

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream stringStream(line);
        std::string cell;
        std::vector<int> row;

        const char COMMA_DELIMITER = ',';

        while (std::getline(stringStream, cell, COMMA_DELIMITER))
        {
            row.push_back(std::stoi(cell));
        }

        data.push_back(row);
    }

    return data;
}