#include "Bookshelf.h"

#include "../../Manager/Generic/ResourceManager.h"
#include "../../Manager/Generic/InputManager.h"
#include "../../Manager/Decoration/SoundManager.h"
#include "../../DrawUI/SceneUI/LibraryUI.h"
#include "../../DrawUI/Font.h"
#include "../../Application.h"

Bookshelf::Bookshelf(void)
    : isValid_(false)
{
    isShowUserInterface_ = false;
    isLibraryOpen_ = false;
    libraryUserInterface_ = new LibraryUI();

    const float INITIAL_RADIUS = 50.0f;
    const float INITIAL_SPEED = 0.0f;

    radius_ = INITIAL_RADIUS;
    speed_ = INITIAL_SPEED;
    movementVector_ = { INITIAL_SPEED, INITIAL_SPEED, INITIAL_SPEED };
}

Bookshelf::~Bookshelf(void)
{
    Release();
    delete libraryUserInterface_;
    libraryUserInterface_ = nullptr;
}

void Bookshelf::Init(void)
{
    auto& resourceManager = ResourceManager::GetInstance();
    transform_.SetModel(resourceManager.LoadModelDuplicate(ResourceManager::SRC::BOOK_SHELF));

    const float POSITION_ZERO = 0.0f;
    const float SCALE_VALUE = 5.0f;

    transform_.position = { POSITION_ZERO, POSITION_ZERO, POSITION_ZERO };
    transform_.scale = { SCALE_VALUE, SCALE_VALUE, SCALE_VALUE };
    transform_.rotation = { POSITION_ZERO, POSITION_ZERO, POSITION_ZERO };

    const float HALF_DIVISOR = 2.0f;

    hitMin_ = {
        transform_.position.x - WIDTH / HALF_DIVISOR,
        transform_.position.y - HEIGHT / HALF_DIVISOR,
        transform_.position.z - DEPTH / HALF_DIVISOR
    };

    hitMax_ = {
        transform_.position.x + WIDTH / HALF_DIVISOR,
        transform_.position.y + HEIGHT / HALF_DIVISOR,
        transform_.position.z + DEPTH / HALF_DIVISOR
    };

    isValid_ = true;

    libraryUserInterface_->Init();
}

void Bookshelf::Update(void)
{
    const float HALF_DIVISOR = 2.0f;

    hitMin_ = {
        transform_.position.x - WIDTH / HALF_DIVISOR,
        transform_.position.y - HEIGHT / HALF_DIVISOR,
        transform_.position.z - DEPTH / HALF_DIVISOR
    };

    hitMax_ = {
        transform_.position.x + WIDTH / HALF_DIVISOR,
        transform_.position.y + HEIGHT / HALF_DIVISOR,
        transform_.position.z + DEPTH / HALF_DIVISOR
    };

    auto& inputManager = InputManager::GetInstance();
    const int INPUT_PRESSED = 1;

    if (isShowUserInterface_ && !isLibraryOpen_)
    {
        if (inputManager.IsTriggerDown(KEY_INPUT_RETURN) == INPUT_PRESSED)
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
            isLibraryOpen_ = true;

            if (libraryUserInterface_ != nullptr)
            {
                libraryUserInterface_->Show();
            }
        }
    }

    if (isLibraryOpen_ && libraryUserInterface_ != nullptr)
    {
        libraryUserInterface_->Update();

        if (inputManager.IsTriggerDown(KEY_INPUT_ESCAPE) == INPUT_PRESSED)
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_CANCEL);
            isLibraryOpen_ = false;
            libraryUserInterface_->Hide();
        }
    }
}

void Bookshelf::Draw(void)
{
    const int INVALID_MODEL_ID = -1;

    if (transform_.modelId > INVALID_MODEL_ID)
    {
        MV1SetScale(transform_.modelId, transform_.scale);
        MV1SetPosition(transform_.modelId, transform_.position);
        MV1SetRotationXYZ(transform_.modelId, transform_.rotation);
        MV1DrawModel(transform_.modelId);
    }
}

void Bookshelf::DrawUI(void)
{
    const int SCREEN_WIDTH = Application::FULL_SCREEN_SIZE_X;
    const int SCREEN_HEIGHT = Application::FULL_SCREEN_SIZE_Y;

    if (isShowUserInterface_ && !isLibraryOpen_)
    {
        const char* TEXT = "èëå…";
        const int FONT_SIZE = 24;
        const int TEXT_MARGIN = 30;
        const int BOX_HEIGHT = 30;

        int textWidth = GetDrawStringWidth(TEXT, static_cast<int>(strlen(TEXT)), FONT_SIZE);
        int boxWidth = textWidth + TEXT_MARGIN;

        const int HALF_DIVISOR = 2;
        const int Y_OFFSET = 100;

        int boxX = (SCREEN_WIDTH - boxWidth) / HALF_DIVISOR;
        int boxY = SCREEN_HEIGHT / HALF_DIVISOR + Y_OFFSET;

        const int BOX_MARGIN_X = 20;
        const int BOX_MARGIN_Y = 10;

        const int COLOR_BLACK = GetColor(0, 0, 0);
        const int COLOR_WHITE = GetColor(255, 255, 255);

        DrawBox(
            boxX - BOX_MARGIN_X,
            boxY - BOX_MARGIN_Y,
            boxX + boxWidth + BOX_MARGIN_X,
            boxY + BOX_HEIGHT + BOX_MARGIN_Y,
            COLOR_BLACK,
            true
        );

        DrawBox(
            boxX - BOX_MARGIN_X,
            boxY - BOX_MARGIN_Y,
            boxX + boxWidth + BOX_MARGIN_X,
            boxY + BOX_HEIGHT + BOX_MARGIN_Y,
            COLOR_WHITE,
            false
        );

        const int TEXT_OFFSET = 5;

        Font::GetInstance().DrawDefaultText(
            boxX + TEXT_OFFSET,
            boxY + TEXT_OFFSET,
            TEXT,
            COLOR_WHITE,
            FONT_SIZE
        );
    }

    if (isLibraryOpen_)
    {
        libraryUserInterface_->Draw();
    }
}

void Bookshelf::Release(void)
{
    const int INVALID_MODEL_ID = -1;

    if (transform_.modelId > INVALID_MODEL_ID)
    {
        MV1DeleteModel(transform_.modelId);
        transform_.modelId = INVALID_MODEL_ID;
    }

    isValid_ = false;

    delete libraryUserInterface_;
    libraryUserInterface_ = nullptr;
}

VECTOR Bookshelf::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR Bookshelf::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE Bookshelf::GetHitType(void) const
{
    return HIT_TYPE::AABB;
}

VECTOR Bookshelf::GetHitPosition(void) const
{
    return transform_.position;
}

float Bookshelf::GetHitRadius(void) const
{
    return radius_;
}

bool Bookshelf::IsValid(void) const
{
    return isValid_;
}

void Bookshelf::ShowUI(void)
{
    isShowUserInterface_ = true;
}

void Bookshelf::HideUI(void)
{
    isShowUserInterface_ = false;
    isLibraryOpen_ = false;

    if (libraryUserInterface_ != nullptr)
    {
        libraryUserInterface_->Hide();
    }
}

void Bookshelf::OnPlayerHit(void)
{
    ShowUI();
}

void Bookshelf::OnPlayerExit(void)
{
    HideUI();
}

bool Bookshelf::IsVisible(void) const
{
    return libraryUserInterface_->IsVisible();
}

Transform& Bookshelf::GetTransform(void)
{
    return transform_;
}