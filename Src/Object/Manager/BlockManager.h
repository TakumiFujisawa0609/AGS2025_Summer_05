#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../../Object/GardenObject/Block.h"

/// @brief ブロックの配置、読み込み、管理を行うクラス
class BlockManager
{
public:

    /// @brief コンストラクタ
    BlockManager(void);

    /// @brief デストラクタ
    ~BlockManager(void);

    /// @brief 初期化処理
    /// @param csvFilePath 読み込むCSVファイルのパス
    void Init(const std::string& csvFilePath);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief マップデータを取得する
    /// @return マップデータの2次元配列の参照
    const std::vector<std::vector<int>>& GetMapData(void) const;

private:


    // ブロックサイズ
    static constexpr float blockSize_ = 50.0f;

    /// @brief CSVファイルからマップデータを読み込む
    /// @param filePath 読み込むファイルのパス
    /// @return 読み込んだマップデータの2次元配列
    std::vector<std::vector<int>> LoadCSV(const std::string& filePath);

    // オブジェクト管理関連
    std::vector<std::unique_ptr<Block>> blocks_;      // ブロックオブジェクトのリスト
    std::vector<std::vector<int>> mapData_;           // マップデータの2次元配列
};