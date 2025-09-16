#pragma once
class LibraryUI
{
public:
    // 横に並べる最大数
    static constexpr int MAX_COLUMNS = 5;

    // アイテムアイコンサイズ
    static constexpr int ICON_SIZE = 64;

    // 各アイテムの間隔
    static constexpr int PADDING = 70;

    // インベントリの表示タブ
    enum class TAB
    {
        Material,   // 素材アイテム
        Product     // 完成品アイテム
    };

    LibraryUI(void);
    ~LibraryUI(void);

    void Init(void);      // 初期化

    void Show(void);

    void Hide(void);

    void Update(void);    // 更新
    void Draw(void);      // 描画

    bool IsVisible(void) const { return isVisible_; }  // 表示中か

private:
    bool isVisible_;          // インベントリ表示フラグ
    int selectedItemIndex_;   // 選択中のアイテムインデックス
    TAB currentTab_;          // 現在選択中のタブ（素材 or 完成品）
    int frameCount_;          // フレームカウンタ（任意で利用）

};

