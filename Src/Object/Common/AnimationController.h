#pragma once

#include <string>
#include <map>

/// @brief アニメーションの制御・管理を行うクラス
class AnimationController
{
public:

    /// @brief アニメーションの読み込み元モードを定義する列挙型
    enum class MODE
    {
        INTERNAL, // モデル内包アニメーション
        EXTERNAL  // 外部ファイルアニメーション
    };

    /// @brief アニメーション情報を保持する構造体
    struct Animation
    {
        int modelHandle;         // 外部モデルハンドル（内部アニメの場合は無効値）
        int attachNumber;        // アタッチ番号
        int animationIndex;      // アニメーションインデックス（内部用）
        float playbackSpeed;     // 再生速度
        float totalTime;         // アニメーションの総再生時間
        float currentTime;       // 現在の再生時間
        MODE mode;               // 読み込みモード
    };

    /// @brief コンストラクタ
    /// @param modelHandleId 操作対象のモデルハンドルID
    AnimationController(int modelHandleId);

    /// @brief デストラクタ
    ~AnimationController(void);

    /// @brief 内部アニメーションの追加
    /// @param type アニメーションの種類
    /// @param animationIndex 内部のアニメーションインデックス
    /// @param speed 再生速度
    void AddInternal(int type, int animationIndex, float speed);

    /// @brief 外部アニメーションの追加
    /// @param type アニメーションの種類
    /// @param filePath 外部ファイルのパス
    /// @param speed 再生速度
    void AddExternal(int type, const std::string& filePath, float speed);

    /// @brief アニメーションの再生
    /// @param type 再生するアニメーションの種類
    /// @param isLoop ループ再生するかどうか
    void Play(int type, bool isLoop = true);

    /// @brief 更新処理
    void Update(void);

    /// @brief アニメーションが終了しているか判定する
    /// @return 終了していればtrue
    bool IsEnd(void) const;

    /// @brief 現在再生中のアニメーションの種類を取得する
    /// @return 再生中のアニメーション種類
    int GetPlayType(void) const;

    /// @brief 解放処理
    void Release(void);

private:

    /// @brief アニメーションの登録
    /// @param type アニメーションの種類
    /// @param animation 登録するアニメーション情報
    void Add(int type, Animation animation);

    // 操作対象のモデルハンドルID
    int modelHandleId_;

    // アニメーション管理関連
    std::map<int, Animation> animations_; // 登録されたアニメーションのマップ
    Animation playingAnimation_;          // 現在再生中のアニメーション情報
    int playingType_;                     // 現在再生中のアニメーションの種類

    //ループ再生フラグ
    bool isLoop_;
};