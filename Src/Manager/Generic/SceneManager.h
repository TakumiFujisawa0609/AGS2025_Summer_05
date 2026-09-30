#pragma once

#include <chrono>
#include <vector>
#include <memory>

#include "../../Application.h"
#include "../../Common/Fader.h"

class SceneBase;
class Fader;
class Camera;

/// @brief シーンの進行と切り替えを管理するシングルトンクラス
class SceneManager
{
public:

    /// @brief シーン管理用ID
    enum class SCENE_ID
    {
        NONE,       // 指定なし
        TITLE,      // タイトルシーン
        GAME,       // ゲームシーン
        GAMECLEAR,  // ゲームクリアシーン
        GAMEOVER,   // ゲームオーバーシーン
    };

    /// @brief コントローラ系統
    enum class CONTROLLER
    {
        NONE,       // 指定なし
        KEYBOARD,   // キーボード
        PAD         // ゲームパッド
    };

    /// @brief インスタンスの生成
    static void CreateInstance(void);

    /// @brief インスタンスの取得
    /// @return SceneManagerのインスタンス参照
    static SceneManager& GetInstance(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 3Dの初期化処理
    void Init3D(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief リソースの破棄
    void Destroy(void);

    /// @brief 状態遷移
    /// @param nextId 遷移先のシーンID
    void ChangeScene(SCENE_ID nextId);

    /// @brief シーンIDの取得
    /// @return 現在のシーンID
    SCENE_ID GetSceneID(void);

    /// @brief デルタタイムの取得
    /// @return デルタタイム
    float GetDeltaTime(void) const;

    /// @brief 現在のシーンを取得する
    /// @return 現在のシーンのポインタ
    SceneBase* GetScene(void) const;

    /// @brief カメラの取得
    /// @return カメラのshared_ptr
    std::shared_ptr<Camera> GetCamera(void) const;

private:

    /// 静的インスタンス
    static SceneManager* instance_;

    // シーン状態管理関連
    SCENE_ID sceneId_;              // 現在のシーン
    SCENE_ID waitSceneId_;          // 次のシーン
    bool isSceneChanging_;          // シーン遷移中判定

    // オブジェクト管理関連
    std::unique_ptr<Fader> fader_;  // フェード
    SceneBase* scene_;              // 各種シーン
    std::shared_ptr<Camera> camera_;// カメラ

    // デルタタイム管理関連
    std::chrono::system_clock::time_point preTime_; // 前回計測時の時間
    float deltaTime_;                               // デルタタイム

    /// @brief デフォルトコンストラクタ（外部からの生成を禁止）
    SceneManager(void);

    /// @brief コピーコンストラクタ（使用禁止）
    SceneManager(const SceneManager&);

    /// @brief デストラクタ
    ~SceneManager(void) = default;

    /// @brief デルタタイムをリセットする
    void ResetDeltaTime(void);

    /// @brief シーン遷移
    /// @param sceneId 遷移先のシーンID
    void DoChangeScene(SCENE_ID sceneId);

    /// @brief フェード
    void Fade(void);
};