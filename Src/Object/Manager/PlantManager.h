#pragma once

#include <vector>
#include <memory>

#include "../GardenObject/PlantObject.h"

/// @brief 植物オブジェクトの管理を行うクラス
class PlantManager
{
public:

    /// @brief コンストラクタ
    PlantManager(void);

    /// @brief デストラクタ
    ~PlantManager(void);

    /// @brief 初期化処理
    /// @param mapData マップデータ（2次元配列）
    /// @param blockSize ブロック1つのサイズ
    void Init(const std::vector<std::vector<int>>& mapData, float blockSize);

    /// @brief 更新処理
    /// @param playerPosition プレイヤーの現在座標
    void Update(const VECTOR& playerPosition);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief 植物オブジェクトのリストを取得する
    /// @return 植物オブジェクトのリストの参照
    const std::vector<std::shared_ptr<PlantObject>>& GetPlantObjects(void) const;

private:

    // 植物オブジェクトのリスト
    std::vector<std::shared_ptr<PlantObject>> plants_;

    // マップグリッド関連
    int rowCount_;         // 行数
    int columnCount_;      // 列数
    float offsetX_;        // X軸方向のオフセット
    float offsetZ_;        // Z軸方向のオフセット
    VECTOR position_;      // 植物の座標保持用
};