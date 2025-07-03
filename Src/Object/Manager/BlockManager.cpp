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

    int rows = static_cast<int>(mapData_.size());
    int cols = mapData_.empty() ? 0 : static_cast<int>(mapData_[0].size());

    // 原点を中央にずらすためのオフセット
    float offsetX = -(cols * blockSize_) / 2.0f;
    float offsetZ = -(rows * blockSize_) / 2.0f;

    for (int z = 0; z < rows; ++z)
    {
        for (int x = 0; x < cols; ++x)
        {
            int cell = mapData_[z][x];

            // オフセットを加味した位置
            VECTOR pos = VGet(x * blockSize_ + offsetX, -50.0f, z * blockSize_ + offsetZ);

            switch (cell)
            {
            case 1:
                blocks_.emplace_back(std::make_unique<Block>(ResourceManager::SRC::BLOCK_DIRT, pos, blockSize_, 0.3f));
                break;

            case 2:
                blocks_.emplace_back(std::make_unique<Block>(ResourceManager::SRC::BLOCK_GFRASS, pos, blockSize_, 0.3f)); 
                break;

            case 3:
                blocks_.emplace_back(std::make_unique<Block>(ResourceManager::SRC::BLOCK_GFRASS, pos, blockSize_, 0.3f));
                break;


            default:
                break;
            }
        }
    }
}


void BlockManager::Update()
{
    for (auto& block : blocks_)
    {
        block->Update();
    }
}

void BlockManager::Draw()
{
    for (auto& block : blocks_)
    {
        block->Draw();
    }
}

void BlockManager::Release()
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
        std::stringstream ss(line);
        std::string cell;
        std::vector<int> row;

        while (std::getline(ss, cell, ','))
        {
            row.push_back(std::stoi(cell));
        }

        data.push_back(row);
    }

    return data;
}
