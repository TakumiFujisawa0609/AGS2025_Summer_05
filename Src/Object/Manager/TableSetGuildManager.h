#pragma once

#include <vector>
#include <memory>
#include "../GuildObject/TableSetGuild.h"

/// @brief ギルドのテーブルセット群を管理するクラス
class TableSetGuildManager
{
public:

    /// @brief コンストラクタ
    TableSetGuildManager(void);

    /// @brief デストラクタ
    ~TableSetGuildManager(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief テーブルセットのリストを取得する
    /// @return テーブルセットのリストの参照
    const std::vector<std::shared_ptr<TableSetGuild>>& GetTableSets(void) const;

private:

    // テーブルセットのリスト
    std::vector<std::shared_ptr<TableSetGuild>> tableSets_;
};