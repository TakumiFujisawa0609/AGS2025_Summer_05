#include "BookshelfManager.h"

BookshelfManager::BookshelfManager(void)
{
}

BookshelfManager::~BookshelfManager(void)
{
    Release();
}

void BookshelfManager::Init(void)
{
    bookshelves_.clear();

    const float POS_X_FIRST = 275.0f;
    const float POS_X_SECOND = 90.5f;
    const float POS_X_THIRD = -90.5f;
    const float POS_X_FOURTH = -275.0f;
    const float POS_Y_DEFAULT = 0.0f;
    const float POS_Z_DEFAULT = 350.0f;

    // 設置座標（負の位置含む）
    std::vector<VECTOR> positions = {
        { POS_X_FIRST, POS_Y_DEFAULT, POS_Z_DEFAULT },
        { POS_X_SECOND, POS_Y_DEFAULT, POS_Z_DEFAULT },
        { POS_X_THIRD, POS_Y_DEFAULT, POS_Z_DEFAULT },
        { POS_X_FOURTH, POS_Y_DEFAULT, POS_Z_DEFAULT }
    };

    for (const auto& position : positions)
    {
        auto bookshelf = std::make_shared<Bookshelf>();
        bookshelf->Init();
        bookshelf->GetTransform().position = position;

        bookshelves_.emplace_back(bookshelf);
    }
}

void BookshelfManager::Update(void)
{
    for (auto& bookshelf : bookshelves_)
    {
        if (bookshelf != nullptr && bookshelf->IsValid())
        {
            bookshelf->Update();
        }
    }
}

void BookshelfManager::Draw(void)
{
    for (auto& bookshelf : bookshelves_)
    {
        if (bookshelf != nullptr && bookshelf->IsValid())
        {
            bookshelf->Draw();
        }
    }
}

void BookshelfManager::DrawUI(void)
{
    for (auto& bookshelf : bookshelves_)
    {
        if (bookshelf != nullptr && bookshelf->IsValid())
        {
            bookshelf->DrawUI();
        }
    }
}

void BookshelfManager::Release(void)
{
    for (auto& bookshelf : bookshelves_)
    {
        if (bookshelf != nullptr)
        {
            bookshelf->Release();
        }
    }

    bookshelves_.clear();
}

bool BookshelfManager::IsValid(void) const
{
    for (auto& bookshelf : bookshelves_)
    {
        if (bookshelf != nullptr)
        {
            return bookshelf->IsVisible();
        }
    }

    return false;
}

const std::vector<std::shared_ptr<Bookshelf>>& BookshelfManager::GetBookshelves(void) const
{
    return bookshelves_;
}