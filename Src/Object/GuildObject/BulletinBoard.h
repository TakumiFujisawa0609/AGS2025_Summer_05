#pragma once

#include <DxLib.h>
#include <memory>
#include <string>

#include "../Interact/HitObject.h"
#include "../UnitBase.h"

/// @brief 依頼を受けるための掲示板オブジェクトを管理するクラス
class BulletinBoard : public HitObject, public UnitBase
{
public:

    // UI遅延・距離定数関連
    static constexpr int UI_ENTER_DELAY_FRAME = 10;     // 入力無視フレーム数
    static constexpr int UI_SHOW_DELAY_MAX = 30;        // UI持続猶予の最大フレーム数
    static constexpr float UI_CLOSE_DISTANCE = 100.0f;  // UIが閉じる距離

    // 配置・寸法定数関連
    static constexpr float RADIUS = 50.0f;              // 当たり判定の球体半径
    static constexpr VECTOR SCALE = { 0.05f, 0.05f, 0.05f }; // モデルのスケール
    static constexpr VECTOR MODEL_POS = { 200.0f, -5.0f, 350.0f }; // 初期配置座標

    /// @brief コンストラクタ
    BulletinBoard(void);

    /// @brief デストラクタ
    virtual ~BulletinBoard(void) override;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 3Dモデルを描画する
    void DrawModel(void);

    /// @brief UIを描画する
    void DrawUI(void);

    /// @brief 描画処理（標準用）
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;

    /// @brief 当たり判定領域の最小座標を取得する
    /// @return 最小座標
    VECTOR GetHitMin(void) const override;

    /// @brief 当たり判定領域の最大座標を取得する
    /// @return 最大座標
    VECTOR GetHitMax(void) const override;

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

    /// @brief UI表示フラグを状態に合わせて更新する
    /// @param isHit 接触しているかどうか
    void UpdateUIVisibility(bool isHit) override;

    /// @brief 依頼リストが表示中かどうかを取得する
    /// @return 表示中の場合はtrue
    bool GetQuestList(void) const;

private:

    // 画像ハンドル関連
    int imageBoardId_;          // 掲示板背景画像のID
    int imageQuest_;            // 依頼画像のID

    // タイマー関連
    int uiOpenWaitFrame_;       // UI展開後の猶予時間
    int uiShowUIDelayFrames_;   // 表示遅延用フレーム

    // 状態管理関連
    bool isShowUI_;             // 接近UI表示フラグ
    bool isShowQuestList_;      // クエストリスト表示フラグ
    int selectedQuest_;         // 選択中のクエスト番号

    // クエストリストテキスト配列
    std::string questList_[3];  
};