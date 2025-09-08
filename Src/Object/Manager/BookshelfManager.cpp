#include "BookshelfManager.h"

BookshelfManager::BookshelfManager()
{
}

BookshelfManager::~BookshelfManager()
{
    Release();
}

void BookshelfManager::Init()
{
    bookshelves_.clear();

    // 設置座標（負の位置含む）
    std::vector<VECTOR> positions = {
        { 275.0f, 0.0f, 350.0f },
        { 90.5f, 0.0f, 350.0f },
        { -90.5f, 0.0f, 350.0f },
        { -275.0f, 0.0f, 350.0f }
    };

    for (const auto& pos : positions)
    {
        auto shelf = std::make_shared<Bookshelf>();
        shelf->Init();
        shelf->GetTransform().pos = pos;

        bookshelves_.emplace_back(shelf);

    }
}

void BookshelfManager::Update()
{
    for (auto& shelf : bookshelves_)
    {
        if (shelf && shelf->IsValid())
        {
            shelf->Update();
        }
    }
}

void BookshelfManager::Draw()
{
    for (auto& shelf : bookshelves_)
    {
        if (shelf && shelf->IsValid())
        {
            shelf->Draw();
        }
    }
}

void BookshelfManager::DrawUI(void)
{
    for (auto& shelf : bookshelves_)
    {
        if (shelf && shelf->IsValid())
        {
            shelf->DrawUI();
        }
    }
}

void BookshelfManager::Release()
{
    for (auto& shelf : bookshelves_)
    {
        if (shelf)
        {
            shelf->Release();
        }
    }
    bookshelves_.clear();
}

bool BookshelfManager::IsValid(void) const
{
    for (auto& shelf : bookshelves_)
    {
        return shelf->isVisible();
    }
    return false;
}

const std::vector<std::shared_ptr<Bookshelf>>& BookshelfManager::GetGetBookSets(void) const
{
    return bookshelves_;
}

