#pragma once

#include <string>
#include <vector>

/// @brief ポーズメニューを管理・表示するクラス
class PauseMenu
{
public:

    /// @brief ポーズメニューの表示モード
    enum class MODE_PAUSE
    {
        SELECT,             // 通常のメニュー選択
        HOW_TO_PLAY_MENU,   // 「遊び方」サブメニュー
        HOW_TO_PLAY_PAGE,   // サブメニューの個別ページ
        CONTROL             // 操作説明
    };

    // UI・描画関連の定数
    static constexpr int FONT_SIZE_MENU = 24;                  // メインメニューのフォントサイズ
    static constexpr int FONT_SIZE_SUB_MENU = 32;              // サブメニューのフォントサイズ
    static constexpr int FONT_SIZE_GUIDE = 24;                 // ガイドテキストのフォントサイズ
    static constexpr int MENU_BOX_WIDTH = 400;                 // メインメニューの枠の幅
    static constexpr int MENU_ITEM_HEIGHT = 50;                // メインメニューの項目高さ
    static constexpr int SUB_MENU_ITEM_HEIGHT = 25;            // サブメニューの項目高さ加算分
    static constexpr int MARGIN_X_SELECTION = 75;              // 選択枠の横の余白
    static constexpr int MARGIN_Y_SELECTION = 8;               // 選択枠の縦の余白
    static constexpr unsigned int COLOR_BLACK = 0x000000;      // 黒色
    static constexpr unsigned int COLOR_WHITE = 0xffffff;      // 白色
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;     // 黄色（選択枠）
    static constexpr unsigned int COLOR_GRAY = 0xc8c8c8;       // 灰色（GetColor(200, 200, 200)相当）

    /// @brief コンストラクタ
    PauseMenu(void);

    /// @brief デストラクタ
    ~PauseMenu(void) = default;

    /// @brief メニューを表示する
    void Show(void);

    /// @brief メニューを非表示にする
    void Hide(void);

    /// @brief メニューが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool IsVisible(void) const;

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief リソースの解放処理
    void Release(void);

    /// @brief 決定ボタンが押されたかどうかを取得する
    /// @return 決定済みの場合はtrue
    bool IsDecisionMade(void) const;

    /// @brief 選択されているメニューのインデックスを取得する
    /// @return 選択中のインデックス
    int GetSelectedIndex(void) const;

private:

    // 状態管理関連
    MODE_PAUSE mode_;                        // 表示モード
    bool visible_;                           // 表示状態
    bool decisionMade_;                      // 決定状態

    // メインメニュー関連
    std::vector<std::string> menuItems_;     // メインメニュー項目のリスト
    int currentIndex_;                       // 選択中のメインメニューインデックス

    // サブメニュー（遊び方）関連
    std::vector<std::string> howToPlayItems_;// サブメニュー項目のリスト
    int howToPlayIndex_;                     // 選択中のサブメニューインデックス
    int howToPlayPage_;                      // 1=目標 2=錬金 3=アトリエ 4=ギルド 5=ガーデン

    // 画像ハンドル関連
    int controlHandle_;                      // 操作説明画像のハンドル
    int alchemyHandle_;                      // 錬金画像のハンドル
    int objectiveHandle_;                    // 目標画像のハンドル
    int atelierHandle_;                      // アトリエ画像のハンドル
    int guildHandle_;                        // ギルド画像のハンドル
    int gardenHandle_;                       // ガーデン画像のハンドル
};