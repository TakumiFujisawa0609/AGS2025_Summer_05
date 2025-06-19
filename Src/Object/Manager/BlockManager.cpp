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
    auto mapData = LoadCSV(csvFilePath);

    int rows = static_cast<int>(mapData.size());
    int cols = mapData.empty() ? 0 : static_cast<int>(mapData[0].size());

    // 原点を中央にずらすためのオフセット
    float offsetX = -(cols * blockSize_) / 2.0f;
    float offsetZ = -(rows * blockSize_) / 2.0f;

    for (int z = 0; z < rows; ++z)
    {
        for (int x = 0; x < cols; ++x)
        {
            int cell = mapData[z][x];

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
