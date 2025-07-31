#pragma once

#include <string>
#include <map>
#include <memory>

#include "../Item/ItemBase.h" // ← ItemBase を共通基底クラスとして利用

class AlchemyRecipe
{
public:
    // コンストラクタ：素材と結果アイテム
    AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ItemBase> result);

    // 素材が一致するか判定
    bool Match(const std::map<std::string, int>& selected) const;

    // 結果アイテム取得
    std::shared_ptr<ItemBase> GetResult(void) const;

    // 必要な素材を取得
    const std::map<std::string, int>& GetMaterials(void) const;

private:
    std::map<std::string, int> requiredMaterials_;   // 必要素材
    std::shared_ptr<ItemBase> result_;               // 結果（製品 or 素材）
};
