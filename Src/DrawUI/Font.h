#pragma once
#include <string>
#include <unordered_map>
#include <DxLib.h>

/// @brief フォントの管理・描画を行うシングルトンクラス
class Font
{
public:

    /// @brief ハッシュ関数の定義
    struct PairHash {
        std::size_t operator()(const std::pair<int, int>& pair) const noexcept {
            return std::hash<int>()(pair.first) ^ (std::hash<int>()(pair.second) << 1);
        }
    };

    // フォントのタイプ関連定数
    static constexpr int FONT_TYPE_NORMAL = DX_FONTTYPE_NORMAL;                       // 通常のフォント
    static constexpr int FONT_TYPE_EDGE = DX_FONTTYPE_EDGE;                           // 縁取りフォント
    static constexpr int FONT_TYPE_ANTIALIASING = DX_FONTTYPE_ANTIALIASING;           // アンチエイリアス
    static constexpr int FONT_TYPE_ANTIALIASING_EDGE = DX_FONTTYPE_ANTIALIASING_EDGE; // アンチエイリアス+縁取り

    /// @brief デストラクタ
    ~Font(void);

    /// @brief インスタンスを明示的に生成
    static void CreateInstance(void);

    /// @brief インスタンス取得
    /// @return Fontのインスタンス参照
    static Font& GetInstance(void);

    /// @brief フォントの初期化
    void Init(void);

    /// @brief フォントの追加
    /// @param fontId フォントID
    /// @param internalFontName 内部フォント名
    /// @param fontPath フォントファイルのパス
    /// @param fontSize フォントサイズ
    /// @param fontWeight フォントの太さ
    /// @param fontType フォントのタイプ
    /// @return 追加に成功した場合はtrue
    bool AddFont(
        const std::string& fontId,
        const std::string& internalFontName,
        const std::string& fontPath,
        int fontSize,
        int fontWeight,
        int fontType
    );

    /// @brief フォントの削除
    /// @param fontId 削除するフォントID
    void RemoveFont(const std::string& fontId);

    /// @brief デフォルトフォントの設定
    /// @param fontId デフォルトに設定するフォントID
    void SetDefaultFont(const std::string& fontId);

    /// @brief テキスト描画
    /// @param fontId 使用するフォントID
    /// @param positionX 描画のX座標
    /// @param positionY 描画のY座標
    /// @param text 描画するテキスト文字列
    /// @param color テキストの色
    /// @param fontSize フォントサイズ
    /// @param fontType フォントタイプ
    void DrawText(
        const std::string& fontId,
        int positionX,
        int positionY,
        const char* text,
        int color,
        int fontSize = -1,
        int fontType = -1
    );

    /// @brief デフォルトフォントで描画
    /// @param positionX 描画のX座標
    /// @param positionY 描画のY座標
    /// @param text 描画するテキスト文字列
    /// @param color テキストの色
    /// @param fontSize フォントサイズ
    /// @param fontType フォントタイプ
    void DrawDefaultText(
        int positionX,
        int positionY,
        const char* text,
        int color,
        int fontSize = -1,
        int fontType = -1
    );

    /// @brief 文字の横幅を取得
    /// @param text 計測対象のテキスト文字列
    /// @return テキストの横幅
    int GetDefaultTextWidth(const std::string& text) const;

    /// @brief リソースの解放
    void Destroy(void);

private:

    // シングルトンインスタンス関連
    static Font* instance_; // シングルトンインスタンス

    // フォントデータ管理関連
    std::unordered_map<
        std::string,
        std::unordered_map<std::pair<int, int>, int, PairHash>
    > fontHandles_; // フォントハンドルのマップ

    std::unordered_map<
        std::pair<int, int>,
        int,
        PairHash
    > dynamicFontHandles_; // 動的フォントサイズとタイプのキャッシュ

    std::unordered_map<std::string, std::string> fontNameMap_; // フォントIDと内部フォント名のマップ

    // 状態管理関連
    std::string defaultFont_; // デフォルトフォントID

    /// @brief コンストラクタ
    Font(void);

    /// @brief 一時的なフォントを取得または生成
    /// @param internalFontName 内部フォント名
    /// @param fontSize フォントサイズ
    /// @param fontWeight フォントの太さ
    /// @param fontType フォントのタイプ
    /// @return 作成または取得したフォントハンドル
    int GetDynamicFontHandle(
        const std::string& internalFontName,
        int fontSize,
        int fontWeight,
        int fontType
    );
};