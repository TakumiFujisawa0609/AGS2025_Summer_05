#pragma once

#include <DxLib.h>
#include <unordered_map>
#include <string>

#include "SoundManager.h"
#include "../../Common/Quaternion.h"

/// @brief エフェクト管理クラス
/// ゲーム内で使用される視覚エフェクトを管理する
class EffectManager
{
public:

    /// @brief エフェクトの種類を定義する列挙型
    enum class EFFECT
    {
        EFFECT_ALCHEMY,   // 錬金エフェクト
        EFFECT_BLAST,     // 爆発エフェクト
    };

    // 各種エフェクトの上限数
    static constexpr int NONE_MAX = 5; 

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return EffectManagerの唯一のインスタンス
    static EffectManager& GetInstance(void);

    /// @brief エフェクトの追加
    /// @param effect エフェクト種類名
    /// @param data エフェクトのデータ
    void Add(const EFFECT& effect, int data);

    /// @brief エフェクトの再生
    /// @param effect エフェクト種類名
    /// @param position 再生位置
    /// @param quaternion 角度
    /// @param size 大きさ
    /// @param sound 効果音
    void Play(
        const EFFECT& effect,
        const VECTOR& position,
        const Quaternion& quaternion,
        const float& size,
        const SoundManager::SOUND sound
    );

    /// @brief エフェクトの再生停止
    /// @param effect エフェクト種類名
    void Stop(const EFFECT& effect);

    /// @brief エフェクトの各パラメータ同期
    /// @param effect エフェクト名
    /// @param position 位置情報
    /// @param quaternion 回転情報
    /// @param size 大きさ
    void SyncEffect(
        const EFFECT& effect,
        const VECTOR& position,
        const Quaternion& quaternion,
        const float& size
    );

    /// @brief エフェクトの再生確認
    /// @param effect エフェクト名
    /// @return 再生中ならtrue、停止中ならfalse
    bool IsPlayEffect(const EFFECT& effect);

    /// @brief 解放処理
    void Release(void);

    /// @brief 消去処理
    void Destroy(void);

private:

    // シングルトンパターンのためのインスタンス保持用変数
    static EffectManager* instance_; 

    // エフェクトデータ関連
    std::unordered_map<EFFECT, int> effectRes_;   // 初期データ
    std::unordered_map<EFFECT, int> effectPlay_;  // 再生データ
    std::unordered_map<EFFECT, int> effectMax_;   // 再生データの最大所持数

    /// @brief コンストラクタ
    EffectManager(void);

    /// @brief デストラクタ
    ~EffectManager(void) = default;
};