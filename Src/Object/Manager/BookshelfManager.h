#pragma once

#include <vector>
#include <memory>
#include "../AtelierObject/Bookshelf.h"

class BookshelfManager
{
public:
    BookshelfManager(void);
    ~BookshelfManager(void);

    void Init(void);
    void Update(void);
    void Draw(void);
    void DrawUI(void);
    void Release(void);
    bool IsValid(void) const;

    const std::vector<std::shared_ptr<Bookshelf>>& GetGetBookSets(void) const;

private:
    std::vector<std::shared_ptr<Bookshelf>> bookshelves_;
};
