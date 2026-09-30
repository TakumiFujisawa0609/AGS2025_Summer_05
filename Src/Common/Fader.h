#pragma once

/// @brief フェード処理を管理するクラス
class Fader
{
public:
    /// @brief フェード状態
    enum class STATE
    {
        NONE,           // 何もしていない
        FADE_OUT,       // 徐々に暗転
        FADE_IN,        // 徐々に明転
        FADE_KEEP,      // 現在の状態を保つ
        SET_FADE_OUT    // アルファ値を決めて暗転
    };

    // 透過関連
    static constexpr int ALPHA_MAX = 255;                      // 透過最大値
    static constexpr int LITTLE_ALPHA = 150;                   // 少し暗くする時のアルファ値

    // フェード速度関連
    static constexpr float LITTLE_FADE_OUT_SPEED = 2.0f;       // 少し暗くする時のフェードアウト速度
    static constexpr float SPEED_SCENE = 5.0f;                 // シーン遷移時のフェード速度
    static constexpr float SPEED_PHASE = 2.0f;                 // フェーズ遷移時のフェード速度
    static constexpr float SPEED_ALPHA = 3.0f;                 // 汎用フェード操作時の速度

    /// @brief 現在のフェード状態を取得する
    /// @param void 
    /// @return 現在の状態
    STATE GetState(void) const;

    /// @brief フェード処理が完了しているかどうかを判定する
    /// @param void 
    /// @return 完了している場合はtrue
    bool IsEnd(void) const;

    /// @brief 指定されたフェード処理を開始する
    /// @param state 設定するフェード状態
    void SetFade(STATE state);

    /// @brief 任意のアルファ値を設定する
    /// @param alpha 設定するアルファ値
    void SetAlpha(float alpha);

    /// @brief 初期化処理
    /// @param void 
    virtual void Init(void);

    /// @brief 更新処理
    /// @param void 
    virtual void Update(void);

    /// @brief 描画処理
    /// @param void 
    virtual void Draw(void);

protected:
    // フェード状態関連
    STATE state_;                                              // 現在のフェード状態
    bool isPreEnd_;                                            // 状態(STATE)を保ったまま終了判定を行うため、Update->Draw->Updateの1フレーム判定用
    bool isEnd_;                                               // フェード処理の終了判定

    // 透過度関連
    float alpha_;                                              // 暗転・明転用透過度
    float alphaMax_;                                           // 透明度の指定値用

    // フェード速度
    float speed_;                                              // フェード速度

private:
    // マスク画像領域
    int temporaryScene_;                                       

    /// @brief マスク描画処理
    /// @param void 
    void CircleMask(void);
};