#pragma once

#include <vector>
#include <string>

/// @brief アイテム取得時のUI表示を管理するクラス
class ItemPickupUI
{
public:

    /// @brief コンストラクタ
    ItemPickupUI(void);

    /// @brief デストラクタ
    ~ItemPickupUI(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

private:

    /// @brief アイテム取得情報の構造体
    struct PickupInfo
    {
        std::string itemName; // アイテム名
        int quantity;         // 取得数
        int timer;            // 表示タイマー
    };

    // 描画・UI関連の定数
    static constexpr int DISPLAY_TIME = 180;              // 表示時間
    static constexpr int DRAW_START_POSITION_X = 0;       // 描画開始X座標
    static constexpr int DRAW_LINE_HEIGHT = 30;           // 行の高さ
    static constexpr int FONT_SIZE = 18;                  // フォントサイズ
    static constexpr unsigned int COLOR_WHITE = 0xffffff; // 白色

    // アイテム情報関連
    std::vector<PickupInfo> pickups_;                     // 取得アイテム情報のリスト

    /// @brief アイテム取得情報を追加する
    /// @param itemName 追加するアイテムの名前
    /// @param quantity 追加するアイテムの数
    void AddPickup(const std::string& itemName, int quantity);
};