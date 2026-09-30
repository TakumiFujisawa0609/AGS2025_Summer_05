#pragma once

#include <memory>

#include "StageBase.h"

/// @brief 自室（プライベートルーム）ステージの管理を行うクラス
class PrivateRoomStage : public StageBase
{
public:

    /// @brief コンストラクタ
    PrivateRoomStage(void);

    /// @brief デストラクタ
    ~PrivateRoomStage(void) = default;

    /// @brief 初期化処理
    void Init(void) override;

    /// @brief 更新処理
    void Update(void) override;

    /// @brief 描画処理
    void Draw(void) override;

    /// @brief 解放処理
    void Release(void) override;
};