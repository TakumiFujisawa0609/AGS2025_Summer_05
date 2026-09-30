#pragma once

#include <string>
#include <windows.h>

class Fps;
class PauseMenu;

/// @brief アプリケーション全体の管理を行うシングルトンクラス
class Application
{
public:

    /// @brief アクティブなUIの種類を定義する列挙型
    enum class ACTIVE_UI_TYPE
    {
        NONE,
        QUEST,
        DELIVERY,
        SHOP,
        TELEPORT
    };

    // 画面サイズ関連
    static constexpr int SCREEN_SIZE_X = 1920;         // ウィンドウ幅
    static constexpr int SCREEN_SIZE_Y = 1080;         // ウィンドウ高さ
    static constexpr int FULL_SCREEN_SIZE_X = 1920; // フルスクリーン幅
    static constexpr int FULL_SCREEN_SIZE_Y = 1080; // フルスクリーン高さ

    // フレームレート関連
    static constexpr int DEFAULT_FPS = 60;             // デフォルトFPS
    static constexpr int FRAME_RATE = 1000 / 60;       // 1フレームのミリ秒数

    // データパス関連
    static const std::string PATH_IMAGE;               // 画像データパス
    static const std::string PATH_MODEL;               // モデルデータパス
    static const std::string PATH_ANIMATION;           // アニメーションデータパス
    static const std::string PATH_EFFECT;              // エフェクトデータパス
    static const std::string PATH_TEXT;                // テキストデータパス
    static const std::string PATH_FONT;                // フォントデータパス
    static const std::string PATH_JSON;                // JSONデータパス
    static const std::string PATH_BGM;                 // BGMデータパス
    static const std::string PATH_SE;                  // SEデータパス
    static const std::string PATH_MOVIE;               // 動画データパス
    static const std::string PATH_MAP_DATA;            // マップデータパス

    /// @brief 明示的にインスタンスを生成する
    static void CreateInstance(void);

    /// @brief 静的インスタンスの取得
    /// @return Applicationのインスタンス参照
    static Application& GetInstance(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief ゲームループ開始
    void Run(void);

    /// @brief リソースの破棄
    void Destroy(void);

    /// @brief 初期化成功/失敗の判定
    /// @return 初期化に失敗していればtrue
    bool IsInitializeFailed(void) const;

    /// @brief 解放成功/失敗の判定
    /// @return 解放に失敗していればtrue
    bool IsReleaseFailed(void) const;

    /// @brief UIの表示状態を取得する
    /// @return UIがアクティブであればtrue
    bool IsActiveUI(void) const;

    /// @brief UIの表示状態を設定する
    /// @param isActive 設定する表示状態
    void SetActiveUI(bool isActive);

    /// @brief アクティブなUIの種類を設定する
    /// @param uiType 設定するUIの種類
    void SetActiveUIType(ACTIVE_UI_TYPE uiType);

    /// @brief テレポートUIがアクティブか判定する
    /// @return アクティブであればtrue
    bool IsTeleportUIActive(void) const;

    /// @brief アクティブなUIの種類を取得する
    /// @return 現在のアクティブUIの種類
    ACTIVE_UI_TYPE GetActiveUIType(void) const;

private:

    /// @brief 静的インスタンス
    static Application* instance_;

    // 状態管理関連
    bool isInitializeFailed_;        // 初期化失敗フラグ
    bool isReleaseFailed_;           // 解放失敗フラグ
    bool isActiveUI_;                // UIアクティブフラグ
    ACTIVE_UI_TYPE activeUIType_;    // 現在のアクティブなUIの種類

    // システムオブジェクト関連
    Fps* fps_;                       // フレームレート制御
    PauseMenu* pauseMenu_;           // ポーズメニュー

    /// @brief コンストラクタ
    Application(void);

    /// @brief コピーコンストラクタ（使用禁止）
    Application(const Application&);

    /// @brief デストラクタ
    ~Application(void) = default;

    /// @brief Effekseerの初期化
    void InitEffekseer(void);
};