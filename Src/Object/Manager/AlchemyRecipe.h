#pragma once

#include <string>
#include <map>
#include <memory>

#include "../Item/ItemBase.h" // ItemBase を共通基底クラスとして利用

/// <summary>
/// 錬金レシピを表すクラス。
/// 必要な素材と錬金結果アイテムを管理する。
/// </summary>
class AlchemyRecipe {
public:
    /// <summary>
    /// コンストラクタ。必要素材と結果アイテムを指定してレシピを作成する。
    /// </summary>
    /// <param name="materials">必要素材のマップ（アイテムIDと必要数）</param>
    /// <param name="result">錬金によって生成されるアイテム</param>
    AlchemyRecipe(const std::map<std::string, int>& materials, std::shared_ptr<ItemBase> result);

    /// <summary>
    /// 指定された素材がこのレシピに一致するか判定する。
    /// </summary>
    /// <param name="selected">プレイヤーが選択した素材のマップ</param>
    /// <returns>レシピに一致すれば true、一致しなければ false</returns>
    bool Match(const std::map<std::string, int>& selected) const;

    /// <summary>
    /// このレシピで生成される結果アイテムを取得する。
    /// </summary>
    /// <returns>結果アイテムの共有ポインタ</returns>
    std::shared_ptr<ItemBase> GetResult(void) const;

    /// <summary>
    /// レシピに必要な素材一覧を取得する。
    /// </summary>
    /// <returns>必要素材のマップ（アイテムIDと必要数）</returns>
    const std::map<std::string, int>& GetMaterials(void) const;

private:
    /// <summary>
    /// 必要な素材（アイテムIDと数量）
    /// </summary>
    std::map<std::string, int> requiredMaterials_;

    /// <summary>
    /// 錬金結果として得られるアイテム
    /// </summary>
    std::shared_ptr<ItemBase> result_;
};
