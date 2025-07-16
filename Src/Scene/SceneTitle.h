#pragma once

#include <memory>
#include "SceneBase.h"

class Grid;
class SceneUi;

class SceneTitle : public SceneBase
{
public:
    SceneTitle(void);
    ~SceneTitle(void) = default;

    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

private:
    int logo_;
    int movieHandle_;
    int operationHandle_;
    Grid* grid_;
    std::unique_ptr<SceneUi> ui_;

    // Å´ í«â¡
    bool isDecided_;
    int blackAlpha_;
    bool showBlackBackground_ = false;

    void DrawDebug(void);
};
