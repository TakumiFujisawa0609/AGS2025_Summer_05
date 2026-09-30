#pragma once

#include <memory>
#include "SceneBase.h"

class Grid;
class SceneUi;

/// @brief タイトルシーンを管理するクラス
class SceneTitle : public SceneBase
{
public:

    // ポーズUIカウントの最大値
    static constexpr int PAUSE_UI_COUNT = 2;

    /// @brief コンストラクタ
    SceneTitle(void);

    /// @brief デストラクタ
    virtual ~SceneTitle(void) override = default;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief ゲーム終了が要求されているかを取得する
    /// @return 要求されている場合はtrue
    bool IsExitRequested(void) const;

private:

    // オブジェクト・UI管理関連
    Grid* grid_;                                            // グリッドオブジェクト
    std::unique_ptr<SceneUi> uiMain_;                       // メインメニューのUI
    std::unique_ptr<SceneUi> uiHowToPlay_;                  // 遊び方サブメニューのUI

    // リソースハンドル関連
    int logoHandle_;                                        // ロゴ画像のハンドル
    int movieHandle_;                                       // 動画のハンドル
    int operationHandle_;                                   // 操作説明画像のハンドル
    int playHandle_;                                        // 遊び方画像1のハンドル
    int playHandle2_;                                       // 遊び方画像2のハンドル
    int atelierHandle_;                                     // アトリエ説明画像のハンドル
    int guildHandle_;                                       // ギルド説明画像のハンドル
    int gardenHandle_;                                      // ガーデン説明画像のハンドル

    // 状態管理関連
    int blackAlpha_;                                        // 黒背景のアルファ値
    int pauseUiCount_;                                      // ポーズUIカウント
    int howToPlayPage_;                                     // 遊び方の表示ページ番号

    // フラグ関連
    bool inHowToPlayMenu_;                                  // 遊び方メニュー内かどうかのフラグ
    bool isDecided_;                                        // 決定フラグ
    bool showBlackBackground_;                              // 黒背景表示フラグ
    bool exitRequested_;                                    // 終了要求フラグ
    bool isPlay_;                                           // プレイ中フラグ

    /// @brief デバッグ情報を描画する
    void DrawDebug(void);
};