#pragma once

#include <DxLib.h>
#include <vector>
#include <memory>

#include "../Interact/HitObject.h"
#include "../NullHitObject.h"

class Player;

/// @brief プレイヤーとヒットオブジェクトとの当たり判定を管理するクラス
class CollisionManager
{
public:

    // 表示開始距離
    static constexpr float SHOW_RADIUS = 50.0f;

    // 非表示開始距離
    static constexpr float HIDE_RADIUS = 60.0f;

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return CollisionManagerのインスタンス参照
    static CollisionManager& GetInstance(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 当たり判定オブジェクトを登録する
    /// @param object 登録するヒットオブジェクトのshared_ptr
    void Register(const std::shared_ptr<HitObject>& object);

    /// @brief 全ての当たり判定オブジェクトをクリアする
    void Clear(void);

    /// @brief プレイヤーとの当たり判定をチェックする
    /// @param player プレイヤーのポインタ
    /// @param playerPosition プレイヤーの座標
    /// @param playerRadius プレイヤーの半径
    /// @param playerMin プレイヤーのAABB最小値
    /// @param playerMax プレイヤーのAABB最大値
    void CheckHitWithPlayer(
        Player* player,
        VECTOR& playerPosition,
        float playerRadius,
        const VECTOR& playerMin,
        const VECTOR& playerMax
    );

    /// @brief リソースの解放処理
    void Destroy(void);

private:

    // 静的インスタンス関連
    static CollisionManager* instance_;

    /// @brief コンストラクタ
    CollisionManager(void) = default;

    /// @brief デストラクタ
    ~CollisionManager(void) = default;

    // 当たり判定オブジェクト関連
    std::vector<std::shared_ptr<HitObject>> hitObjects_;
    NullHitObject nullObject_;

    // 作業用変数関連
    VECTOR objectPosition_;
    float objectRadius_;
    VECTOR objectMinimum_;
    VECTOR objectMaximum_;
    float objectSizeX_;
    float objectSizeZ_;
    VECTOR difference_;

    /// @brief 安全にヒットオブジェクトを取得する
    /// @param object 取得対象のヒットオブジェクト
    /// @return 取得したヒットオブジェクト
    HitObject* SafeGet(HitObject* object);

    /// @brief 球体同士の当たり判定をチェックする
    /// @param object ヒットオブジェクト
    /// @param playerPosition プレイヤーの座標
    /// @param playerRadius プレイヤーの半径
    void CheckHitSphere(
        std::shared_ptr<HitObject> object,
        VECTOR& playerPosition,
        float playerRadius
    );

    /// @brief AABB同士の当たり判定をチェックする
    /// @param object ヒットオブジェクト
    /// @param player プレイヤーのポインタ
    /// @param playerPosition プレイヤーの座標
    /// @param playerMin プレイヤーのAABB最小値
    /// @param playerMax プレイヤーのAABB最大値
    void CheckHitAABB(
        std::shared_ptr<HitObject> object,
        Player* player,
        VECTOR& playerPosition,
        const VECTOR& playerMin,
        const VECTOR& playerMax
    );
};