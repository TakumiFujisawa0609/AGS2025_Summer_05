#pragma once

#include <vector>
#include <memory>
#include "../AtelierObject/Bookshelf.h"

class BookshelfManager
{
public:
    BookshelfManager();
    ~BookshelfManager();

    void Init();
    void Update();
    void Draw();
    void Release();

    const std::vector<std::shared_ptr<Bookshelf>>& GetGetBookSets(void) const;

private:
    std::vector<std::shared_ptr<Bookshelf>> bookshelves_;
};
