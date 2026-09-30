#pragma once

#include <vector>
#include <memory>
#include "../Common/Transform.h"
#include "../GardenObject/FenceObject.h"
#include "../GardenObject/FenceObject1.h"

/// @brief フェンスオブジェクトの配置と管理を行うクラス
class FenceManager
{
public:

    /// @brief コンストラクタ
    FenceManager(void);

    /// @brief デストラクタ
    ~FenceManager(void);

    /// @brief 初期化処理
    /// @param mapData マップデータ（2次元配列）
    /// @param blockSize ブロック1つのサイズ
    void Init(const std::vector<std::vector<int>>& mapData, float blockSize);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief 通常フェンスオブジェクトのリストを取得する
    /// @return 通常フェンスオブジェクトのリストの参照
    const std::vector<std::shared_ptr<FenceObject>>& GetFenceObjects(void) const;

    /// @brief X方向フェンスオブジェクトのリストを取得する
    /// @return X方向フェンスオブジェクトのリストの参照
    const std::vector<std::shared_ptr<FenceObject1>>& GetFenceObjectsX(void) const;

private:

    // フェンスオブジェクト関連
    std::vector<std::shared_ptr<FenceObject>> fenceObjects_;
    std::vector<std::shared_ptr<FenceObject1>> fenceObjectsX_;

    // マップグリッド関連
    int rowCount_;      // 行数
    int columnCount_;   // 列数
    float offsetX_;     // X軸方向のオフセット
    float offsetZ_;     // Z軸方向のオフセット
};