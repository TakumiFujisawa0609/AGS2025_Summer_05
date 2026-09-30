#pragma once

#include <string>
#include <map>
#include <memory>

#include "../Item/ItemBase.h" 

/// @brief 錬金のレシピ情報を管理するクラス
class AlchemyRecipe
{
public:

    /// @brief コンストラクタ
    /// @param materials 必要な素材のマップ
    /// @param result 生成される結果アイテム
    AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ItemBase> result);

    /// @brief デストラクタ
    ~AlchemyRecipe(void) = default;

    /// @brief 選択された素材がレシピと一致するか判定する
    /// @param selected 選択された素材のマップ
    /// @return 一致している場合はtrue
    bool Match(const std::map<std::string, int>& selected) const;

    /// @brief 結果アイテムを取得する
    /// @return 結果アイテムのshared_ptr
    std::shared_ptr<ItemBase> GetResult(void) const;

    /// @brief 必要な素材を取得する
    /// @return 必要な素材のマップの参照
    const std::map<std::string, int>& GetMaterials(void) const;

private:

    std::map<std::string, int> requiredMaterials_;   // 必要素材
    std::shared_ptr<ItemBase> result_;               // 結果
};