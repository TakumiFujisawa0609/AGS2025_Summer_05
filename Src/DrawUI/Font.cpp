#include "Font.h"

Font* Font::instance_ = nullptr;

Font::Font(void) : defaultFont_("")
{
}

Font::~Font(void)
{
    for (auto& outerPair : fontHandles_)
    {
        for (auto& innerPair : outerPair.second)
        {
            int fontHandle = innerPair.second;
            if (fontHandle != -1 && fontHandle != DX_DEFAULT_FONT_HANDLE)
            {
                DeleteFontToHandle(fontHandle);
            }
        }
    }

    for (const auto& dynamicFont : dynamicFontHandles_)
    {
        if (dynamicFont.second != -1 && dynamicFont.second != DX_DEFAULT_FONT_HANDLE)
        {
            DeleteFontToHandle(dynamicFont.second);
        }
    }
}

void Font::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new Font();
    }
    instance_->Init();
}

Font& Font::GetInstance(void)
{
    if (instance_ == nullptr)
    {
        Font::CreateInstance();
    }
    return *instance_;
}

void Font::Init(void)
{
}

bool Font::AddFont(
    const std::string& fontId,
    const std::string& internalFontName,
    const std::string& fontPath,
    int fontSize,
    int fontWeight,
    int fontType)
{
    int fontFileSize = FileRead_size(fontPath.c_str());
    int fontFileHandle = FileRead_open(fontPath.c_str());

    if (fontFileSize <= 0 || fontFileHandle == -1)
    {
        OutputDebugString("フォントファイルが見つかりません\n");
        return false;
    }

    void* buffer = new char[fontFileSize];
    FileRead_read(buffer, fontFileSize, fontFileHandle);
    FileRead_close(fontFileHandle);

    DWORD fontNumber = 0;
    if (AddFontMemResourceEx(buffer, fontFileSize, NULL, &fontNumber) == 0)
    {
        OutputDebugString("AddFontMemResourceEx 失敗\n");
        delete[] static_cast<char*>(buffer);
        return false;
    }

    delete[] static_cast<char*>(buffer);

    fontNameMap_[fontId] = internalFontName;

    int fontHandle = CreateFontToHandle(
        internalFontName.c_str(), fontSize, fontWeight, fontType);

    if (fontHandle == -1)
    {
        OutputDebugString("フォントハンドル作成失敗\n");
        return false;
    }

    fontHandles_[fontId][std::make_pair(fontSize, fontType)] = fontHandle;

    return true;
}

void Font::RemoveFont(const std::string& fontId)
{
    auto iterator = fontHandles_.find(fontId);
    if (iterator != fontHandles_.end())
    {
        for (auto& innerPair : iterator->second)
        {
            int fontHandle = innerPair.second;
            if (fontHandle != -1 && fontHandle != DX_DEFAULT_FONT_HANDLE)
            {
                DeleteFontToHandle(fontHandle);
            }
        }
        fontHandles_.erase(iterator);
    }
}

void Font::SetDefaultFont(const std::string& fontId)
{
    auto iterator = fontHandles_.find(fontId);
    if (iterator != fontHandles_.end() && !iterator->second.empty())
    {
        defaultFont_ = fontId;
    }
    else
    {
        std::string errorMessage = "SetDefaultFont: フォントID [" + fontId +
            "] は未登録またはサイズ情報がありません。\n";
        OutputDebugStringA(errorMessage.c_str());
    }
}

void Font::DrawText(
    const std::string& fontId,
    int positionX,
    int positionY,
    const char* text,
    int color,
    int fontSize,
    int fontType)
{
    int fontHandle = -1;
    int useFontType = (fontType >= 0) ? fontType : FONT_TYPE_NORMAL;

    auto nameIterator = fontNameMap_.find(fontId);
    std::string internalFontName = (nameIterator != fontNameMap_.end())
        ? nameIterator->second : "";

    if (fontSize > 0)
    {
        auto fontIterator = fontHandles_.find(fontId);
        if (fontIterator != fontHandles_.end())
        {
            auto& sizeMap = fontIterator->second;
            auto sizeIterator = sizeMap.find({ fontSize, useFontType });
            if (sizeIterator != sizeMap.end())
            {
                fontHandle = sizeIterator->second;
            }
        }

        if (fontHandle == -1)
        {
            const int DEFAULT_FONT_WEIGHT = 3;
            fontHandle = GetDynamicFontHandle(
                internalFontName, fontSize, DEFAULT_FONT_WEIGHT, useFontType);
        }
    }
    else
    {
        auto fontIterator = fontHandles_.find(fontId);
        if (fontIterator != fontHandles_.end())
        {
            auto& sizeMap = fontIterator->second;
            if (!sizeMap.empty())
            {
                fontHandle = sizeMap.begin()->second;
            }
        }
    }

    if (fontHandle == -1)
    {
        fontHandle = DX_DEFAULT_FONT_HANDLE;
    }

    DrawFormatStringFToHandle(positionX, positionY, color, fontHandle, text);
}

void Font::DrawDefaultText(
    int positionX,
    int positionY,
    const char* text,
    int color,
    int fontSize,
    int fontType)
{
    DrawText(defaultFont_, positionX, positionY, text, color, fontSize, fontType);
}

int Font::GetDefaultTextWidth(const std::string& text) const
{
    return GetDrawStringWidth(text.c_str(), static_cast<int>(text.size()));
}

int Font::GetDynamicFontHandle(
    const std::string& internalFontName,
    int fontSize,
    int fontWeight,
    int fontType)
{
    auto cacheKey = std::make_pair(fontSize, fontType);
    auto iterator = dynamicFontHandles_.find(cacheKey);

    if (iterator != dynamicFontHandles_.end())
    {
        return iterator->second;
    }

    int fontHandle = CreateFontToHandle(
        internalFontName.c_str(), fontSize, fontWeight, fontType);

    if (fontHandle != -1)
    {
        dynamicFontHandles_[cacheKey] = fontHandle;
    }

    return fontHandle;
}

void Font::Destroy(void)
{
    if (instance_ != nullptr)
    {
        delete instance_;
        instance_ = nullptr;
    }
}