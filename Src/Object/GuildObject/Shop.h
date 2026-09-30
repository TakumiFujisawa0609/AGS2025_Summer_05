#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "../../Object/Item/ItemBase.h"

class Player;
class DateTimeManager;

/// @brief ショップのシステムとUIを管理するクラス
class Shop
{
public:

    /// @brief ショップの操作フェーズを定義する列挙型
    enum class SHOP_PHASE
    {
        SELECT_ITEM,    // アイテム選択中
        SELECT_AMOUNT   // 数量選択中
    };

    /// @brief 現在フォーカスしているUIエリアを定義する列挙型
    enum class SHOP_AREA
    {
        ITEM_LIST,      // 商品リストエリア
        PURCHASE_LIST   // 購入予定リストエリア
    };

    // UIレイアウト定数関連
    static constexpr int SHOP_COLUMNS = 3;              // 商品リストの列数
    static constexpr int SHOP_ICON_SIZE = 64;           // アイコンサイズ
    static constexpr int SHOP_PADDING = 20;             // アイコン間のパディング
    static constexpr int SHOP_ITEM_WIDTH = SHOP_ICON_SIZE + 10;  // 1アイテムあたりの幅
    static constexpr int SHOP_ITEM_HEIGHT = SHOP_ICON_SIZE + 45; // 1アイテムあたりの高さ

    /// @brief コンストラクタ
    Shop(void);

    /// @brief デストラクタ
    ~Shop(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief ショップUIを表示する
    void Show(void);

    /// @brief ショップUIを非表示にする
    void Hide(void);

    /// @brief ショップUIが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool IsVisible(void) const;

    /// @brief 更新処理
    void Update(void);

    /// @brief メイン描画処理
    void Draw(void);

    /// @brief 右側UI（購入予定リストなど）を描画する
    void DrawRightSideUI(void);

    /// @brief プレイヤーインスタンスを設定する
    /// @param player プレイヤーのshared_ptr
    void SetPlayer(std::shared_ptr<Player> player);

    /// @brief 日付管理マネージャーを設定する
    /// @param dateTime DateTimeManagerのポインタ
    void SetDateTimeManager(DateTimeManager* dateTime);

private:

    /// @brief アイテムの価格を取得する
    /// @param item 対象のアイテム
    /// @return アイテムの価格
    int GetPrice(std::shared_ptr<ItemBase> item) const;

    /// @brief 購入予定リストの合計金額を取得する
    /// @return 合計金額
    int GetTotalPrice(void) const;

    /// @brief 選択中のアイテムの購入数量を取得する
    /// @return 購入数量
    int GetSelectedQuantity(void) const;

    /// @brief 購入を確定し処理を実行する
    void ConfirmPurchase(void);

    /// @brief 日替わりアイテムのラインナップを更新する
    void RefreshDailyItems(void);

    /// @brief 現在選択中のアイテムを取得する
    /// @return 選択中アイテムのshared_ptr
    std::shared_ptr<ItemBase> GetSelectedItem(void) const;

    // ショップ商品リスト
    std::vector<std::shared_ptr<ItemBase>> shopItems_;

    // 購入予定数量管理
    std::unordered_map<std::string, int> purchaseQuantities_;

    // 選択状態・フラグ関連
    int selectedItemIndex_;             // 選択中のアイテムインデックス
    bool isVisible_;                    // ショップUIの表示フラグ
    bool skipFirstInputFrame_;          // 開いた直後の入力を無視するフラグ
    SHOP_PHASE currentPhase_;           // 現在の操作フェーズ
    int selectedQuantity_;              // 数量選択時の値
    int lastDay_;                       // 最後に商品を更新した日付

    // UIエリアフォーカス関連
    SHOP_AREA currentArea_;             // 現在フォーカスしているエリア
    int purchaseListSelectedIndex_;     // 購入リスト内での選択インデックス

    // 参照関連
    std::shared_ptr<Player> player_;    // プレイヤーへの参照
    DateTimeManager* dateTimeManager_;  // 日付管理マネージャーへの参照
};