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

void SceneUi::Draw(int basePositionYOverride)
{
    DrawFont(basePositionYOverride);
}

void SceneUi::FontBlinking(void)
{
    frameCount_++;

    if ((frameCount_ / BLINK_INTERVAL) % 2 != 0)
    {
        isBlinking_ = true;
    }
    else
    {
        isBlinking_ = false;
    }
}

void SceneUi::DrawFont(int basePositionYOverride)
{
    int basePositionY = basePositionYOverride;

    for (size_t index = 0; index < fontList_.size(); ++index)
    {
        const auto& fontData = fontList_[index];

        int textWidth = GetDrawStringWidth(
            fontData.message.c_str(),
            static_cast<int>(fontData.message.length())
        );

        int drawPositionX = (Application::FULL_SCREEN_SIZE_X / 2) - textWidth;
        int drawPositionY = basePositionY + static_cast<int>(index) * DRAW_LINE_SPACING;

        unsigned int color = (static_cast<int>(index) == currentIndex_)
            ? COLOR_YELLOW : COLOR_GRAY;

        Font::GetInstance().DrawDefaultText(
            drawPositionX,
            drawPositionY,
            fontData.message.c_str(),
            color,
            FONT_SIZE,
            Font::FONT_TYPE_ANTIALIASING_EDGE
        );
    }
}

void SceneUi::AddCharacter(const char* text)
{
    fontList_.push_back(FontData{ text });
}

void SceneUi::SetCurrentIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(fontList_.size()))
    {
        currentIndex_ = index;
    }
}

int SceneUi::GetCurrentIndex(void) const
{
    return currentIndex_;
}

int SceneUi::GetMaxIndex(void) const
{
    return static_cast<int>(fontList_.size());
}