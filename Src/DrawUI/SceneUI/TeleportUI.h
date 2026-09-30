#pragma once

#include "../../Object/Common/Transform.h"

class StageManager;

class Player;

/// @brief テレポートUIの管理および表示を行うクラス
class TeleportUI
{
public:

    /// @brief 転送先の種類
    enum class DESTINATION
    {
        GUILD,      // ギルド
        ATELIER,    // アトリエ
        GARDEN,     // ガーデン
        MAX         // 最大値
    };

    // UI描画関連の定数
    static constexpr int FONT_SIZE = 24;                         // フォントサイズ
    static constexpr int DRAW_BOX_OFFSET_LEFT = 200;             // 枠の左側オフセット
    static constexpr int DRAW_BOX_OFFSET_RIGHT = 400;            // 枠の右側オフセット
    static constexpr int DRAW_BOX_HEIGHT = 32;                   // 枠の高さ
    static constexpr int DRAW_BOX_MARGIN = 8;                    // 枠同士の余白
    static constexpr int DRAW_TEXT_OFFSET_X = 80;                // テキストのX座標オフセット
    static constexpr int DRAW_TEXT_OFFSET_Y = 4;                 // テキストのY座標オフセット
    static constexpr unsigned int COLOR_BLACK = 0x000000;        // 黒色
    static constexpr unsigned int COLOR_WHITE = 0xffffff;        // 白色
    static constexpr unsigned int COLOR_YELLOW = 0xffff00;       // 黄色（選択時）

    /// @brief コンストラクタ
    /// @param stageManager ステージマネージャーへのポインタ
    /// @param player プレイヤーへのポインタ
    TeleportUI(StageManager* stageManager, Player* player);

    /// @brief デストラクタ
    ~TeleportUI(void) = default;

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief メニューを表示する
    void Show(void);

    /// @brief メニューを非表示にする
    void Hide(void);

    /// @brief メニューが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool IsVisible(void) const;

private:

    // 状態管理関連
    bool isVisible_;             // 表示状態フラグ
    DESTINATION selected_;       // 選択中の転送先

    // 参照データ関連
    StageManager* stageManager_; // ステージマネージャーへの参照
    Player* player_;             // プレイヤーへの参照
};