#include "AlchemyRecipe.h"

// コンストラクタ：必要な素材と結果アイテムを受け取り、レシピを初期化する
AlchemyRecipe::AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ItemBase> result)
    : requiredMaterials_(materials), result_(result)
{
}

// 指定された素材がレシピの必要素材と完全一致するかを判定する
bool AlchemyRecipe::Match(const std::map<std::string, int>& selected) const
{
    return selected == requiredMaterials_;
}

// 錬金の結果として得られるアイテムを取得する
std::shared_ptr<ItemBase> AlchemyRecipe::GetResult(void) const
{
    return result_;
}

// このレシピに必要な素材の一覧を取得する
const std::map<std::string, int>& AlchemyRecipe::GetMaterials(void) const
{
    return requiredMaterials_;
}
