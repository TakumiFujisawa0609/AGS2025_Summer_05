#pragma once

#include <vector>
#include <memory>
#include "../AtelierObject/Bookshelf.h"

/// @brief 本棚オブジェクトの配置と管理を行うクラス
class BookshelfManager
{
public:

    /// @brief コンストラクタ
    BookshelfManager(void);

    /// @brief デストラクタ
    ~BookshelfManager(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief UI描画処理
    void DrawUI(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief 有効状態かどうかを取得する
    /// @return 有効な場合はtrue
    bool IsValid(void) const;

    /// @brief 本棚オブジェクトのリストを取得する
    /// @return 本棚オブジェクトのリストの参照
    const std::vector<std::shared_ptr<Bookshelf>>& GetBookshelves(void) const;

private:

    // 本棚オブジェクト関連
    std::vector<std::shared_ptr<Bookshelf>> bookshelves_;
};