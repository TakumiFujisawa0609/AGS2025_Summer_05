#pragma once
#include <unordered_map>

/// @brief サウンド管理クラス
class SoundManager
{
public:
    /// @brief 再生の種類を分類する列挙型
    enum class TYPE
    {
        NONE,
        BGM,   // バックグラウンドミュージック
        SE     // サウンドエフェクト
    };

    /// @brief 使用する音声データの種類を定義する列挙型
    enum class SOUND
    {
        NONE,
        BGM_TITLE,          // タイトル画面BGM
        BGM_GAME,           // ゲームプレイ中BGM
        BGM_GAMEOVER,       // ゲームオーバー時BGM
        BGM_GAMECLEAR,      // ゲームクリア時BGM
        BGM_GARDEN_DAY,     // ガーデンの朝昼BGM
        BGM_GARDEN_NIGHT,   // ガーデンの夕方夜BGM
        BGM_ATELIER,        // アトリエBGM
        BGM_GUILD,          // ギルドのBGM

        SE_PUSH,            // ボタン押下時効果音
        SE_CANCEL,          // キャンセル音
        SE_SELECT,          // カーソル移動
        SE_DAMAGE,          // ダメージ受けた時効果音
        SE_GET,             // アイテム取得時効果音
        SE_ALCHEMY,         // 錬金時効果音    
        SE_ALCHEMY_FAIL,    // 錬金失敗効果音
        SE_ALCHEMY_SUCCESS, // 錬金成功効果音
    };

    /// @brief 音声データを格納する構造体
    struct SOUND_DATA
    {
        int data;       // 音声データ格納
        TYPE type;      // 音声データの種類
        int playMode;   // 音声データの再生タイプ
    };

    /// @brief インスタンスを生成する
    static void CreateInstance(void);

    /// @brief インスタンスを取得する
    /// @return SoundManagerの唯一のインスタンス参照
    static SoundManager& GetInstance(void);

    /// @brief サウンドの追加
    /// @param type 音の種類分け(SEかBGMか)
    /// @param sound 具体的な用途
    /// @param data 音のデータ
    void Add(const TYPE type, const SOUND sound, const int data);

    /// @brief 音声データの再生
    /// @param sound 再生する音声データ
    void Play(const SOUND sound);

    /// @brief 音声データの停止処理
    /// @param sound 停止する音声データ
    void Stop(const SOUND sound);

    /// @brief 音声データの解放処理
    void Release(void);

    /// @brief 音量調節
    /// @param sound 調整対象の音声
    /// @param percent 調整割合(0%～100%)
    void AdjustVolume(const SOUND sound, const int percent);

    /// @brief なり終わってるかどうかを確認する
    /// @param sound 確認する音声データ
    /// @return 再生中の場合はtrue、そうでない場合はfalse
    bool IsPlaying(SOUND sound);

    /// @brief インスタンスの破棄
    void Destroy(void);

private:

    // シングルトンインスタンス保持用
    static SoundManager* instance_;                

    // SOUND列挙型をキーとして対応する音声データを管理
    std::unordered_map<SOUND, SOUND_DATA> sounds_; 

    /// @brief コンストラクタ
    SoundManager(void) = default;

    /// @brief デストラクタ
    ~SoundManager(void) = default;
};