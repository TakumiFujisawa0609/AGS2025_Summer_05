#pragma once

/// @brief 図鑑（ライブラリ）UIを管理・表示するクラス
class LibraryUI
{
public:

    /// @brief インベントリの表示タブ
    enum class TAB
    {
        MATERIAL,   // 素材アイテム
        PRODUCT     // 完成品アイテム
    };

    // UIレイアウト関連
    static constexpr int MAX_COLUMNS = 5;               // 横に並べる最大数
    static constexpr int ICON_SIZE = 64;                // アイテムアイコンサイズ
    static constexpr int PADDING = 70;                  // 各アイテムの間隔

    // 背景描画関連
    static constexpr int BACKGROUND_OFFSET_X = 100;     // 背景描画時のX軸オフセット
    static constexpr int BACKGROUND_OFFSET_Y_TOP = 140; // 背景描画時のY軸上部位置
    static constexpr int BACKGROUND_OFFSET_W = 200;     // 背景描画時の幅オフセット
    static constexpr int BACKGROUND_OFFSET_H = 200;     // 背景描画時の高さオフセット
    static constexpr int ALPHA_MAX = 255;               // アルファブレンド最大値
    static constexpr unsigned int COLOR_BLACK = 0x000000; // 黒色
    static constexpr unsigned int COLOR_WHITE = 0xffffff; // 白色
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;// 黄色（選択枠、タブ）
    static constexpr unsigned int COLOR_GRAY = 0xc8c8c8;  // 灰色（未入手アイテム枠）
    static constexpr unsigned int COLOR_DARK_GRAY = 0x969696; // 濃い灰色（未入手テキスト）

    /// @brief コンストラクタ
    LibraryUI(void);

    /// @brief デストラクタ
    ~LibraryUI(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 図鑑を表示する
    void Show(void);

    /// @brief 図鑑を非表示にする
    void Hide(void);

    /// @brief 状態の更新処理
    void Update(void);

    /// @brief 図鑑の描画処理
    void Draw(void);

    /// @brief 現在図鑑が表示中かどうかを取得する
    bool IsVisible(void) const { return isVisible_; }

private:
    // 状態管理関連
    bool isVisible_;                                // インベントリ表示フラグ
    int selectedItemIndex_;                         // 選択中のアイテムインデックス
    TAB currentTab_;                                // 現在選択中のタブ（素材 or 完成品）
    int frameCount_;                                // フレームカウンタ
};