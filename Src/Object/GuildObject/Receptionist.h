#pragma once
#include <DxLib.h>
#include <memory>
#include <string>
#include "../Interact/HitObject.h"
#include "../UnitBase.h"

class Shop;
class Player;

/// @brief アイテムの種類を定義する列挙型
enum class ITEM_TYPE
{
    HEALTH_POTION = 0,
    ANTIDOTE_POTION,
    MAGIC_POTION,
    GARBAGE,
    ANTIPARALYSIS_POTION,
    SPEED_POTION,
    POWER_POTION,
    DEFENSE_POTION,
    FIRE_SWORD,
    WATER_SWORD,
    WIND_SWORD,
    EARTH_SWORD,
    ICE_SWORD,
    LIGHT_SWORD,
    DARK_SWORD,
    FIRE_WAND,
    WATER_WAND,
    WIND_WAND,
    EARTH_WAND,
    ICE_WAND,
    LIGHT_WAND,
    DARK_WAND,
    ITEM_COUNT
};

/// @brief 受付嬢キャラクターを管理し、ショップや納品処理を行うクラス
class Receptionist : public HitObject, public UnitBase
{
public:

    // 配置・寸法定数関連
    static constexpr float RADIUS = 50.0f;                                  // 当たり判定の球体半径
    static constexpr VECTOR SCALE = { 0.03f, 0.03f, 0.03f };                // モデルのスケール
    static constexpr VECTOR MODEL_POS = { -150.0f, 0.0f, 190.0f };          // 初期配置座標

    /// @brief コンストラクタ
    Receptionist(void);

    /// @brief デストラクタ
    virtual ~Receptionist(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理（標準用）
    void Draw(void) override;

    /// @brief 3Dモデルを描画する
    void DrawModel(void);

    /// @brief UIを描画する
    void DrawUI(void);

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定種別を取得する
    /// @return 当たり判定種別（球体）
    HIT_TYPE GetHitType(void) const override;

    /// @brief 当たり判定の中心座標を取得する
    /// @return 中心座標
    VECTOR GetHitPosition(void) const override;

    /// @brief 当たり判定の半径を取得する
    /// @return 半径
    float GetHitRadius(void) const override;

    /// @brief UIを表示状態にする
    void ShowUI(void) override;

    /// @brief UIを非表示状態にする
    void HideUI(void) override;

    /// @brief オブジェクトが有効かどうかを取得する
    /// @return 有効な場合はtrue
    bool IsValid(void) const override;

    /// @brief プレイヤーと接触した時の処理
    void OnPlayerHit(void) override;

    /// @brief プレイヤーが離れた時の処理
    void OnPlayerExit(void) override;

    /// @brief メインメニューの更新処理
    void UpdateMainMenu(void);

    /// @brief ショップメニューの更新処理
    void UpdateShopMenu(void);

    /// @brief 納品メニューの更新処理
    void UpdateDeliveryMenu(void);

    /// @brief 納品可能アイテムリストの更新処理
    void UpdateDeliverableItems(void);

    /// @brief 選択された数量の納品処理を実行する
    /// @return 納品に成功した場合はtrue
    bool DeliverSelectedQuantity(void);

    /// @brief メインメニューを描画する
    void DrawMainMenu(void);

    /// @brief 納品メニューを描画する
    void DrawDeliveryMenu(void);

    /// @brief アイテムの所持数を設定する（デバッグ・システム用）
    /// @param itemType 対象のアイテム種類
    /// @param count 設定する数
    void SetItemCount(ITEM_TYPE itemType, int count);

    /// @brief アイテムの所持数を取得する
    /// @param itemType 対象のアイテム種類
    /// @return 所持数
    int GetItemCount(ITEM_TYPE itemType) const;

    /// @brief 最大納品可能数を取得する
    /// @return 納品可能な最大数
    int GetMaxDeliveryQuantity(void) const;

    /// @brief アイテム名を取得する
    /// @param itemType 対象のアイテム種類
    /// @return アイテムの名称
    const char* GetItemName(ITEM_TYPE itemType) const;

    /// @brief アイテムのIDを取得する
    /// @param itemType 対象のアイテム種類
    /// @return アイテムのID文字列
    std::string GetItemId(ITEM_TYPE itemType) const;

    /// @brief プレイヤーインスタンスを設定する
    /// @param player プレイヤーのshared_ptr
    void SetPlayer(std::shared_ptr<Player> player);

    /// @brief 依頼の残り納品数を取得する
    /// @param itemType 対象のアイテム種類
    /// @return 残り納品数
    int GetRemainingDeliveryAmount(ITEM_TYPE itemType) const;

    /// @brief ショップUIが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool GetShopUiVisible(void) const;

    /// @brief 納品メニューが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool GetDeliveryMenu(void) const;

private:

    /// @brief メニューのモードを定義する列挙型
    enum class MENU_MODE
    {
        NONE,           // モードなし
        MAIN_SELECT,    // メインメニュー選択
        DELIVERY_MENU,  // 納品メニュー
        SHOP_MENU       // ショップメニュー
    };

    // 状態管理関連
    MENU_MODE currentMode_;         // 現在のメニューモード
    int mainMenuSelected_;          // 選択中のメインメニューインデックス

    // UI制御フラグ関連
    bool isShowUI_;                 // UIの表示フラグ
    bool isShowDeliveryMenu_;       // 納品メニューの表示フラグ
    int selectedItem_;              // 選択中のアイテムインデックス
    bool isSelectingQuantity_;      // 数量選択中フラグ
    bool isUIForcedClosed_;         // UI強制終了フラグ
    int selectedQuantity_;          // 選択された数量

    // メッセージ表示関連
    int deliveryMessageTimer_;      // 納品結果メッセージの表示タイマー
    std::string lastDeliveryMessage_;// 最後に表示した納品メッセージ

    // アイテム情報関連
    std::string itemNames_[static_cast<int>(ITEM_TYPE::ITEM_COUNT)]; // アイテム名配列
    std::string itemIds_[static_cast<int>(ITEM_TYPE::ITEM_COUNT)];   // アイテムID配列
    std::vector<ITEM_TYPE> deliverableItems_;                        // 納品可能なアイテムリスト

    // 参照情報関連
    std::shared_ptr<Player> player_;    // プレイヤーへの参照
    std::shared_ptr<Shop> shop_;        // ショップへの参照
};