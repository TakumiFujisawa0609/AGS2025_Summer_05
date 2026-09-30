#pragma once
#include <string>
#include <vector>

/// @brief リソースデータを管理するクラス
class Resource
{
public:

    /// @brief リソースタイプ
    enum class TYPE
    {
        NONE,
        IMAGE,        // 画像
        IMAGES,       // 分割画像
        MASK,         // マスク画像
        MODEL,        // 3Dモデル
        ANIMATION,    // アニメーション
        EFFEKSEER,    // エフェクト
        SOUND,        // サウンド
    };

    /// @brief デフォルトコンストラクタ
    Resource(void);

    /// @brief 通常リソース用のコンストラクタ
    /// @param resourceType リソースのタイプ
    /// @param filePath ファイルパス
    Resource(TYPE resourceType, const std::string& filePath);

    /// @brief 分割画像用のコンストラクタ
    /// @param resourceType リソースのタイプ
    /// @param filePath ファイルパス
    /// @param splitCountX 横方向の分割数
    /// @param splitCountY 縦方向の分割数
    /// @param imageWidth 1枚あたりの横幅
    /// @param imageHeight 1枚あたりの縦幅
    Resource(
        TYPE resourceType,
        const std::string& filePath,
        int splitCountX,
        int splitCountY,
        int imageWidth,
        int imageHeight
    );

    /// @brief デストラクタ
    ~Resource(void);

    /// @brief 読み込み処理
    void Load(void);

    /// @brief 解放処理
    void Release(void);

    /// @brief 複数画像ハンドルを別配列にコピーする
    /// @param imageHandles コピー先の配列ポインタ
    void CopyHandles(int* imageHandles);

    // リソース基本情報関連
    TYPE resourceType_;                // リソースタイプ
    std::string filePath_;             // リソースの読み込み先ファイルパス
    int handleId_;                     // 画像、音、モデルなどのハンドルID

    // 分割画像情報関連
    int* handleIds_;                   // IMAGES::LoadDivGraphで使用する複数のハンドルIDを格納
    int splitCountX_;                  // 分割画像の横方向の分割数
    int splitCountY_;                  // 分割画像の縦方向の分割数
    int imageWidth_;                   // 各分割画像の横幅（ピクセル単位）
    int imageHeight_;                  // 各分割画像の縦幅（ピクセル単位）

    // モデル複製用のハンドルIDリスト
    std::vector<int> duplicateModelIds_; 
};