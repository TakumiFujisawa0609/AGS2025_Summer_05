#pragma once

#include <vector>
#include <memory>
#include "../Common/Transform.h"
#include "../GardenObject/OreObject.h"

/// @brief 鉱石オブジェクトの配置と更新を管理するクラス
class OreManager
{
public:

    /// @brief コンストラクタ
    OreManager(void);

    /// @brief デストラクタ
    ~OreManager(void);

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

    /// @brief 鉱石オブジェクトのリストを取得する
    /// @return 鉱石オブジェクトのリストの参照
    const std::vector<std::shared_ptr<OreObject>>& GetOreObjects(void) const;

private:

    // 鉱石オブジェクトのリスト
    std::vector<std::shared_ptr<OreObject>> oreObjects_;

    // マップグリッド関連
    int rowCount_;         // 行数
    int columnCount_;      // 列数
    float offsetX_;        // X軸方向のオフセット
    float offsetZ_;        // Z軸方向のオフセット
};