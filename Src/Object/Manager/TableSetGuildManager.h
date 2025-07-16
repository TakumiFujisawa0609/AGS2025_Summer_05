#pragma once

#include <vector>
#include <memory>
#include "../GuildObject/TableSetGuild.h"

class TableSetGuildManager
{
public:
    TableSetGuildManager(void);
    ~TableSetGuildManager(void);

    void Init(void);
    void Update(void);
    void Draw(void);
    void Release(void);

    const std::vector<std::shared_ptr<TableSetGuild>>& GetTableSets(void) const;


private:
    std::vector<std::shared_ptr<TableSetGuild>> tableSets_;
};
