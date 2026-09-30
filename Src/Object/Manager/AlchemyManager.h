#pragma once

#include <vector>
#include <memory>
#include <map>

#include "../Item/Material/MaterialItem.h"
#include "../Item/Product/ProductItem.h"
#include "AlchemyRecipe.h"

/// @brief 錬金システムの全体管理を行うシングルトンクラス
class AlchemyManager
{
public:

    /// @brief 錬金結果の状態を定義する列挙型
    enum class ALCHEMY_RESULT
    {
        NONE,       // なし
        SUCCESS,    // 成功
        FAILURE     // 失敗
    };

    // UI表示定数
    static constexpr int MAX_COLUMNS = 5;

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return AlchemyManagerのインスタンス参照
    static AlchemyManager& GetInstance(void);

    /// @brief インスタンスを破棄する
    static void Destroy(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief 描画処理
    void Draw(void);

    /// @brief 錬金メニューを開く
    void Open(void);

    /// @brief 錬金メニューを閉じる
    void Close(void);

    /// @brief メニューが開いているかどうかを取得する
    /// @return 開いている場合はtrue
    bool IsOpen(void) const;

    /// @brief レシピとの差分メッセージを表示する
    /// @param selectedMap 選択された素材のマップ
    void ShowRecipeDifferenceMessage(const std::map<std::string, int>& selectedMap);

    /// @brief 最も近いレシピを見つける
    /// @param selectedMap 選択された素材のマップ
    /// @return 最も近いレシピのポインタ（見つからない場合はnullptr）
    const AlchemyRecipe* FindClosestRecipe(const std::map<std::string, int>& selectedMap);

private:

    /// @brief コンストラクタ
    AlchemyManager(void);

    /// @brief デストラクタ
    ~AlchemyManager(void);

    /// @brief 錬金処理を実行する
    void ExecuteAlchemy(void);

    /// @brief 選択状態をリセットする
    void ResetSelection(void);

    /// @brief 選択された素材の情報を保持する構造体
    struct SelectedMaterial
    {
        // 選択素材情報関連
        std::shared_ptr<MaterialItem> item; // 素材アイテムのポインタ
        int amount;                         // 投入する個数
    };

    // レシピ・選択素材コレクション関連
    std::vector<SelectedMaterial> selectedMaterials_;   // 現在選択中の素材リスト
    std::vector<AlchemyRecipe> recipes_;                // 登録されている全レシピ一覧

    // 保留メッセージ
    std::string pendingResultMessage_;

    // UI選択状態関連
    int currentPhase_;                  // 現在の操作フェーズ
    int currentIndex_;                  // 素材選択グリッド上のカーソル位置
    int currentAmount_;                 // 投入個数の選択値
    int selectedMaterialIndex_;         // 個数選択対象の素材インデックス
    int selectedMaterialEditIndex_;     // 編集対象の選択済み素材インデックス

    // 演出・状態フラグ関連
    bool isOpen_;                       // 錬金メニューが開いているか
    bool waitingForSEFinish_;           // 錬金SEの再生終了待機フラグ
    bool effectPlayedDuringAlchemy_;    // 錬金エフェクト再生済みフラグ
    bool start_;                        // 錬金メニューの決定入力受付開始フラグ

    // 結果通知関連
    std::string resultMessage_;         // 画面に表示する結果メッセージ
    int resultMessageTimer_;            // メッセージの表示タイマー（フレーム単位）
    ALCHEMY_RESULT alchemyResult_;      // 錬金の成功・失敗状態

    // シングルトンインスタンス
    static AlchemyManager* instance_;
};