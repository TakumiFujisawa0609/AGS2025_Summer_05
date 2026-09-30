#pragma once

#include <vector>
#include <string>

/// @brief シーンのUIを管理するクラス
class SceneUi
{
public:

    /// @brief 表示するフォントのデータ構造体
    struct FontData
    {
        std::string message;  // 表示する文字列
    };

    // UI描画関連の定数
    static constexpr int BLINK_INTERVAL = 30;             // 点滅の切り替え間隔フレーム数
    static constexpr int DRAW_LINE_SPACING = 80;          // 描画時の行間隔
    static constexpr int FONT_SIZE = 42;                  // フォントサイズ
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;// 選択中の色（黄色）
    static constexpr unsigned int COLOR_GRAY = 0xaaaaaa;  // 非選択時の色（灰色、RGB:170, 170, 170相当）

    /// @brief コンストラクタ
    SceneUi(void);

    /// @brief デストラクタ
    ~SceneUi(void);

    /// @brief 描画処理
    /// @param basePositionYOverride 描画基準のY座標
    void Draw(int basePositionYOverride = -1);

    /// @brief フォントの点滅状態を更新する
    void FontBlinking(void);

    /// @brief フォントを描画する
    /// @param basePositionYOverride 描画基準のY座標
    void DrawFont(int basePositionYOverride);

    /// @brief 描画する文字列を追加する
    /// @param text 追加する文字列
    void AddCharacter(const char* text);

    /// @brief 現在の選択インデックスを設定する
    /// @param index 設定するインデックス
    void SetCurrentIndex(int index);

    /// @brief 現在の選択インデックスを取得する
    /// @return 現在のインデックス
    int GetCurrentIndex(void) const;

    /// @brief 登録されている文字列の最大数を取得する
    /// @return 最大インデックス
    int GetMaxIndex(void) const;

private:

    // 状態管理関連
    int frameCount_;                 // フレームカウンタ
    bool isBlinking_;                // 点滅状態フラグ
    int currentIndex_;               // 現在選択中のインデックス

    // データ関連
    std::vector<FontData> fontList_; // 登録されたフォントデータのリスト
};