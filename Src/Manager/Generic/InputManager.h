#pragma once
#include <map>
#include <Dxlib.h>
#include "../../Common/Vector2.h"

/// @brief 入力全般を管理するクラス
class InputManager
{
public:

    /// @brief ゲームコントローラーの認識番号
    enum class JOYPAD_NUMBER
    {
        KEY_PAD1,           // キー入力とパッド1入力
        PAD1,               // パッド1入力
        PAD2,               // パッド2入力
        PAD3,               // パッド3入力
        PAD4,               // パッド4入力
        INPUT_KEY = 4096    // キー入力
    };

    /// @brief ゲームコントローラータイプ
    enum class JOYPAD_TYPE
    {
        OTHER = 0,            // その他のコントローラー
        XBOX_360,             // Xbox 360 コントローラー
        XBOX_ONE,             // Xbox One コントローラー
        DUAL_SHOCK_4,         // PlayStation 4 コントローラー (DualShock 4)
        DUAL_SENSE,           // PlayStation 5 コントローラー (DualSense)
        SWITCH_JOY_CON_LEFT,  // Switch Joy-Con (L)
        SWITCH_JOY_CON_RIGHT, // Switch Joy-Con (R)
        SWITCH_PRO_CONTROLLER,// Switch Proコントローラー
        MAX                   // 最大値（要素数）
    };

    /// @brief ゲームコントローラーボタン
    enum class JOYPAD_BUTTON
    {
        LEFT = 0,             // 左ボタン（Dパッド左 等）
        RIGHT,                // 右ボタン（Dパッド右 等）
        TOP,                  // 上ボタン（Dパッド上 等）
        DOWN,                 // 下ボタン（Dパッド下 等）
        RIGHT_TRIGGER,        // 右トリガー (RT / R2)
        LEFT_TRIGGER,         // 左トリガー (LT / L2)
        RIGHT_BUTTON,         // 右ボタン (RB / R1)
        LEFT_BUTTON,          // 左ボタン (LB / L1)
        START_BUTTON,         // スタート（メニュー / オプション）ボタン
        SELECT_BUTTON,        // セレクト（ビュー / シェア）ボタン
        MAX                   // 最大値（要素数）
    };

    /// @brief ゲームコントローラーの入力情報
    struct JOYPAD_INPUT_STATE
    {
        unsigned char buttonsOld[static_cast<int>(JOYPAD_BUTTON::MAX)];     // 1フレーム前のボタン生データ
        unsigned char buttonsNew[static_cast<int>(JOYPAD_BUTTON::MAX)];     // 現フレームのボタン生データ
        bool isOld[static_cast<int>(JOYPAD_BUTTON::MAX)];                   // 1フレーム前の押下判定フラグ
        bool isNew[static_cast<int>(JOYPAD_BUTTON::MAX)];                   // 現フレームの押下判定フラグ
        bool isTriggerDown[static_cast<int>(JOYPAD_BUTTON::MAX)];           // 現フレームで新たに押されたか
        bool isTriggerUp[static_cast<int>(JOYPAD_BUTTON::MAX)];             // 現フレームで新たに離されたか
        int analogKeyLeftX;                                                 // 左アナログスティックのX軸入力
        int analogKeyLeftY;                                                 // 左アナログスティックのY軸入力
        int analogKeyRightX;                                                // 右アナログスティックのX軸入力
        int analogKeyRightY;                                                // 右アナログスティックのY軸入力
    };

    /// @brief インスタンスを明示的に生成
    static void CreateInstance(void);

    /// @brief インスタンスの取得
    /// @return インスタンスの参照
    static InputManager& GetInstance(void);

    /// @brief 初期化処理
    void Init(void);

    /// @brief 更新処理
    void Update(void);

    /// @brief リソースの破棄
    void Destroy(void);

    /// @brief 判定を行うキーを追加
    /// @param key 追加するキーのID
    void Add(int key);

    /// @brief 判定を行うキーをクリア
    void Clear(void);

    /// @brief キーの押下判定
    /// @param key 判定するキーID
    /// @return 押下されている場合はtrue
    bool IsNew(int key) const;

    /// @brief キーの押下判定(押しっぱなしはNG)
    /// @param key 判定するキーID
    /// @return 新たに押下された場合はtrue
    bool IsTriggerDown(int key) const;

    /// @brief キーを離した時の判定
    /// @param key 判定するキーID
    /// @return 離された場合はtrue
    bool IsTriggerUp(int key) const;

    /// @brief マウス座標の取得
    /// @return マウスの座標
    Vector2 GetMousePosition(void) const;

    /// @brief マウスのクリック状態を取得
    /// @return クリック状態の値
    int GetMouseInputState(void) const;

    /// @brief マウスが左クリックされたか
    /// @return 左クリックされている場合はtrue
    bool IsClickMouseLeft(void) const;

    /// @brief マウスが右クリックされたか
    /// @return 右クリックされている場合はtrue
    bool IsClickMouseRight(void) const;

    /// @brief マウスが左クリックされたか(押しっぱなしはNG)
    /// @return 新たに左クリックされた場合はtrue
    bool IsTriggerMouseLeft(void) const;

    /// @brief マウスが右クリックされたか(押しっぱなしはNG)
    /// @return 新たに右クリックされた場合はtrue
    bool IsTriggerMouseRight(void) const;

    /// @brief コントローラの入力情報を取得する
    /// @param number コントローラの認識番号
    /// @return 入力情報
    JOYPAD_INPUT_STATE GetJoypadInputState(JOYPAD_NUMBER number);

    /// @brief ボタンが押された
    /// @param number コントローラの認識番号
    /// @param button 対象のボタン
    /// @return 押されている場合はtrue
    bool IsPadButtonNew(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const;

    /// @brief パッドボタンが新しく押されたか
    /// @param number コントローラの認識番号
    /// @param button 対象のボタン
    /// @return 新たに押された場合はtrue
    bool IsPadButtonTriggerDown(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const;

    /// @brief パッドボタンが離されたか
    /// @param number コントローラの認識番号
    /// @param button 対象のボタン
    /// @return 離された場合はtrue
    bool IsPadButtonTriggerUp(JOYPAD_NUMBER number, JOYPAD_BUTTON button) const;

private:

    // 内部構造体関連

    /// @brief キー情報
    struct Info
    {
        int key;              // キーID
        bool isKeyOld;        // 1フレーム前の押下状態
        bool isKeyNew;        // 現フレームの押下状態
        bool isTriggerDown;   // 現フレームでボタンが押されたか
        bool isTriggerUp;     // 現フレームでボタンが離されたか
    };

    /// @brief マウス情報
    struct MouseInfo
    {
        int key;              // キーID
        bool isKeyOld;        // 1フレーム前の押下状態
        bool isKeyNew;        // 現フレームの押下状態
        bool isTriggerDown;   // 現フレームでボタンが押されたか
        bool isTriggerUp;     // 現フレームでボタンが離されたか
    };

    // インスタンス関連

    static InputManager* instance_; // シングルトン用インスタンス

    // 入力状態管理関連

    JOYPAD_INPUT_STATE padInputStates_[5]; // コントローラの入力情報（5個分）
    Vector2 mousePosition_;                // マウスカーソルの位置
    int mouseInputState_;                  // マウスボタンの入力状態
    DINPUT_JOYSTATE directInputState_;     // DirectInputのコントローラ情報
    XINPUT_STATE xInputState_;             // XInputのコントローラ情報

    // キー情報関連

    std::map<int, InputManager::Info> keyInfos_; // キー情報のマップ
    InputManager::Info emptyKeyInfo_;            // 空のキー情報（検索失敗時用）

    // マウス情報関連

    std::map<int, InputManager::MouseInfo> mouseInfos_; // マウス情報のマップ
    InputManager::MouseInfo emptyMouseInfo_;            // 空のマウス情報（検索失敗時用）

    /// @brief コンストラクタ
    InputManager(void);

    /// @brief コピーコンストラクタ（使用禁止）
    InputManager(const InputManager& manager);

    /// @brief デストラクタ
    ~InputManager(void) = default;

    /// @brief 配列の中からキー情報を取得する
    /// @param key 検索するキーID
    /// @return キー情報の参照
    const InputManager::Info& Find(int key) const;

    /// @brief 配列の中からマウス情報を取得する
    /// @param key 検索するキーID
    /// @return マウス情報の参照
    const InputManager::MouseInfo& FindMouse(int key) const;

    /// @brief 接続されたコントローラの種別を取得する
    /// @param number コントローラの認識番号
    /// @return コントローラのタイプ
    JOYPAD_TYPE GetJoypadType(JOYPAD_NUMBER number);

    /// @brief コントローラの入力情報を取得する
    /// @param number コントローラの認識番号
    /// @return DirectInputの状態
    DINPUT_JOYSTATE GetJoypadDirectInputState(JOYPAD_NUMBER number);

    /// @brief コントローラ(XBOX)の入力情報を取得する
    /// @param number コントローラの認識番号
    /// @return XInputの状態
    XINPUT_STATE GetJoypadXInputState(JOYPAD_NUMBER number);

    /// @brief コントローラの入力情報を更新する
    /// @param number コントローラの認識番号
    void SetJoypadInputState(JOYPAD_NUMBER number);
};