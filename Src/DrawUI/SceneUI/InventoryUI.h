#pragma once
#include <memory>
#include <vector>
#include <string>
#include <DxLib.h>

class ItemBase;

/// @brief インベントリUIを管理・表示するクラス
class InventoryUI
{
public:

    /// @brief インベントリの表示タブ
    enum class TAB
    {
        MATERIAL,   // 素材アイテム
        PRODUCT     // 完成品アイテム
    };

    // UIレイアウト関連
    static constexpr int MAX_COLUMNS = 5;      // 横に並べる最大数
    static constexpr int ICON_SIZE = 64;       // アイテムアイコンサイズ
    static constexpr int PADDING = 100;        // 各アイテムの間隔
    
    // 背景描画関連
    static constexpr int BACKGROUND_OFFSET_X = 100;     // 背景描画時のX軸オフセット
    static constexpr int BACKGROUND_OFFSET_Y_TOP = 140; // 背景描画時のY軸上部位置
    static constexpr int BACKGROUND_OFFSET_W = 200;     // 背景描画時の幅オフセット
    static constexpr int BACKGROUND_OFFSET_H = 200;     // 背景描画時の高さオフセット
    static constexpr int ALPHA_MAX = 255;               // アルファブレンド最大値
    static constexpr unsigned int COLOR_BLACK = 0x000000; // 黒色
    static constexpr unsigned int COLOR_WHITE = 0xffffff; // 白色
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;// 黄色（選択枠）

    /// @brief コンストラクタ
    InventoryUI(void);

    /// @brief デストラクタ
    ~InventoryUI(void);

    /// @brief 初期化処理
    /// @param void 
    /// @return なし
    void Init(void);

    /// @brief インベントリを表示する
    void Show(void);

    /// @brief インベントリを非表示にする
    void Hide(void);

    /// @brief 状態の更新処理
    void Update(void);

    /// @brief インベントリの描画処理
    void Draw(void);

    /// @brief 現在インベントリが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool IsVisible(void) const { return isVisible_; }

private:
    // 状態管理関連
    bool isVisible_;                                // インベントリ表示フラグ
    int selectedItemIndex_;                         // 選択中のアイテムインデックス
    TAB currentTab_;                                // 現在選択中のタブ（素材 or 完成品）
    int frameCount_;                                // フレームカウンタ

    // 数量 > 0 のアイテムのみ表示対象にするリスト
    std::vector<std::shared_ptr<ItemBase>> visibleItems_; 
};