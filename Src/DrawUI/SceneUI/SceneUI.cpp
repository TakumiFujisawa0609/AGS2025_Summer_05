#include "SceneUI.h"
#include <DxLib.h>
#include "../../DrawUI/Font.h"
#include "../../Application.h"

SceneUi::SceneUi(void)
    : frameCount_(0), isBlinking_(false), currentIndex_(0)
{
}

SceneUi::~SceneUi(void)
{
}

void SceneUi::Draw(void)
{
    DrawFont();
}

void SceneUi::FontBlinking(void)
{
    frameCount_++;
    isBlinking_ = (frameCount_ / blinkInterval_) % 2 ? true : false;
}

void SceneUi::DrawFont(void)
{
    int baseY = Application::DEFA_SCREEN_SZIE_Y / 2 + 100;  // 最初の項目のY位置
    int spacing = 40;  // 項目間の間隔

    for (size_t i = 0; i < fontList_.size(); ++i)
    {
        const auto& font = fontList_[i];
        int textWidth = GetDrawStringWidth(font.message.c_str(), static_cast<int>(font.message.length()));

        int xPos = (Application::DEFA_SCREEN_SIZE_X - textWidth) / 2;
        int yPos = baseY + static_cast<int>(i) * spacing;

        int color = (static_cast<int>(i) == currentIndex_) ? GetColor(255, 255, 0) : GetColor(170, 170, 170); // 選択中は黄色

        // 修正: 正しい引数順（サイズ→タイプ）
        Font::GetInstance().DrawDefaultText(xPos, yPos, font.message.c_str(), color, 26, Font::FONT_TYPE_ANTIALIASING_EDGE);
    }
}

void SceneUi::AddCharctor(const char* _char)
{
    fontList_.push_back(FontData{ _char });
}

void SceneUi::SetCurrentIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(fontList_.size()))
    {
        currentIndex_ = index;
    }
}

int SceneUi::GetCurrentIndex() const
{
    return currentIndex_;
}

int SceneUi::GetMaxIndex() const
{
    return static_cast<int>(fontList_.size());
}
