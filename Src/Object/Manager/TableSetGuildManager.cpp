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

    // 配置する座標（例：負数の位置を含む）
    std::vector<VECTOR> positions = {
        { 240.0f, 0.0f, -280.0f },
        { 240.0f, 0.0f, -50.0f },
        { -240.0f, 0.0f,  -50.0f },
        { -240.0f, 0.0f,  -280.0f }
    };

    for (const auto& pos : positions)
    {
        auto table = std::make_shared<TableSetGuild>();
        table->Init();

        // 位置を変更
        table->GetTransform().pos = pos;

        tableSets_.emplace_back(table);
    }
}

void TableSetGuildManager::Update(void)
{
    for (auto& table : tableSets_)
    {
        if (table && table->IsValid())
        {
            table->Update();
        }
    }
}

void TableSetGuildManager::Draw(void)
{
    for (auto& table : tableSets_)
    {
        if (table && table->IsValid())
        {
            table->Draw();
        }
    }
}

void TableSetGuildManager::Release(void)
{
    for (auto& table : tableSets_)
    {
        if (table)
        {
            table->Release();
        }
    }
    tableSets_.clear();
}

const std::vector<std::shared_ptr<TableSetGuild>>& TableSetGuildManager::GetTableSets(void) const
{
    return tableSets_;
}
