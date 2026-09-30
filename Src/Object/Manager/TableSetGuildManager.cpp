#include "TableSetGuildManager.h"

TableSetGuildManager::TableSetGuildManager(void)
{
}

TableSetGuildManager::~TableSetGuildManager(void)
{
    Release();
}

void TableSetGuildManager::Init(void)
{
    tableSets_.clear();

    const float POSITION_X_RIGHT = 240.0f;
    const float POSITION_X_LEFT = -240.0f;
    const float POSITION_Y_GROUND = 0.0f;
    const float POSITION_Z_FRONT = -50.0f;
    const float POSITION_Z_BACK = -280.0f;

    std::vector<VECTOR> initialPositions = {
        { POSITION_X_RIGHT, POSITION_Y_GROUND, POSITION_Z_BACK },
        { POSITION_X_RIGHT, POSITION_Y_GROUND, POSITION_Z_FRONT },
        { POSITION_X_LEFT,  POSITION_Y_GROUND, POSITION_Z_FRONT },
        { POSITION_X_LEFT,  POSITION_Y_GROUND, POSITION_Z_BACK }
    };

    for (const auto& position : initialPositions)
    {
        auto tableSet = std::make_shared<TableSetGuild>();
        tableSet->Init();

        tableSet->GetTransform().position = position;

        tableSets_.emplace_back(tableSet);
    }
}

void TableSetGuildManager::Update(void)
{
    for (auto& tableSet : tableSets_)
    {
        if (tableSet != nullptr && tableSet->IsValid())
        {
            tableSet->Update();
        }
    }
}

void TableSetGuildManager::Draw(void)
{
    for (auto& tableSet : tableSets_)
    {
        if (tableSet != nullptr && tableSet->IsValid())
        {
            tableSet->Draw();
        }
    }
}

void TableSetGuildManager::Release(void)
{
    for (auto& tableSet : tableSets_)
    {
        if (tableSet != nullptr)
        {
            tableSet->Release();
        }
    }

    tableSets_.clear();
}

const std::vector<std::shared_ptr<TableSetGuild>>& TableSetGuildManager::GetTableSets(void) const
{
    return tableSets_;
}