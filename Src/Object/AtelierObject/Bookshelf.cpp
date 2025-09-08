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
    isShowUI_ = false;
    isLibraryOpen_ = false;
    libraryUI_ = new LibraryUI();
    
    radius_ = 50.0f;
    speed_ = 0.0f;
    movePow_ = { 0.0f, 0.0f, 0.0f };
}

Bookshelf::~Bookshelf(void)
{
    Release();
    delete libraryUI_;
    libraryUI_ = nullptr;
}

void Bookshelf::Init(void)
{
    auto& res = ResourceManager::GetInstance();
    trans_.SetModel(res.LoadModelDuplicate(ResourceManager::SRC::BOOKS_HELF));

    // フェンスの位置を地面に固定（例）
    trans_.pos = { 0.0f, 0.0f, 0.0f };
    trans_.scl = { 5.0f, 5.0f, 5.0f };
    trans_.rot = { 0.0f, 0.0f, 0.0f };

    // 当たり判定の範囲
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };

    isValid_ = true;

    libraryUI_->Init();
}

void Bookshelf::Update(void)
{
    // 現在の位置に合わせて当たり判定範囲を毎フレーム更新
    hitMin_ = { trans_.pos.x - WIDTH / 2, trans_.pos.y - HEIGHT / 2, trans_.pos.z - DEPTH / 2 };
    hitMax_ = { trans_.pos.x + WIDTH / 2, trans_.pos.y + HEIGHT / 2, trans_.pos.z + DEPTH / 2 };

    auto& input = InputManager::GetInstance();

    if (isShowUI_ && !isLibraryOpen_)
    {
        if (input.IsTrgDown(KEY_INPUT_RETURN))
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_PUSH);
            isLibraryOpen_ = true;
            if (libraryUI_) libraryUI_->Show(); // ← Zキー制御なしで表示
        }
    }

    if (isLibraryOpen_ && libraryUI_)
    {
        libraryUI_->Update();
        if (input.IsTrgDown(KEY_INPUT_ESCAPE))
        {
            Application::GetInstance().SetActiveUI(true);
            SoundManager::GetInstance().Play(SoundManager::SOUND::SE_CANCEL);
            isLibraryOpen_ = false;
            libraryUI_->Hide();
        }
    }
}

void Bookshelf::Draw(void)
{
    if (trans_.modelId >= 0)
    {
        MV1SetScale(trans_.modelId, trans_.scl);
        MV1SetPosition(trans_.modelId, trans_.pos);
        MV1SetRotationXYZ(trans_.modelId, trans_.rot);
        MV1DrawModel(trans_.modelId);
    }
}

void Bookshelf::DrawUI(void)
{
    const int screenWidth = Application::DEFA_SCREEN_SIZE_X;
    const int screenHeight = Application::DEFA_SCREEN_SZIE_Y;

    // UIメッセージ表示（インベントリが未表示のとき）
    if (isShowUI_ && !isLibraryOpen_)
    {
        // テキスト内容
        const char* text = "書庫";
        int fontSize = 24;
        int textWidth = GetDrawStringWidth(text, strlen(text), fontSize);
        int boxWidth = textWidth + 30;
        int boxHeight = 30;

        int boxX = (screenWidth - boxWidth) / 2;
        int boxY = screenHeight / 2 + 100;

        // UI表示（中央）
        DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(0, 0, 0), TRUE);
        DrawBox(boxX - 20, boxY - 10, boxX + boxWidth + 20, boxY + boxHeight + 10, GetColor(255, 255, 255), FALSE);
        Font::GetInstance().DrawDefaultText(boxX + 5, boxY + 5, text, GetColor(255, 255, 255), fontSize);
    }

    // インベントリ表示中
    if (isLibraryOpen_)
    {
        libraryUI_->Draw();
    }
}

void Bookshelf::Release(void)
{
    if (trans_.modelId >= 0)
    {
        MV1DeleteModel(trans_.modelId);
        trans_.modelId = -1;
    }
    isValid_ = false;

    delete libraryUI_;
    libraryUI_ = nullptr;
}

VECTOR Bookshelf::GetHitMin(void) const
{
    return hitMin_;
}

VECTOR Bookshelf::GetHitMax(void) const
{
    return hitMax_;
}

HitObject::HIT_TYPE Bookshelf::GetHitType() const
{
    return HIT_TYPE::AABB;
}

VECTOR Bookshelf::GetHitPosition(void) const
{
    return trans_.pos;
}

float Bookshelf::GetHitRadius(void) const
{
    return radius_;  // フェンスはAABBなので半径は不要
}

bool Bookshelf::IsValid(void) const
{
    return isValid_;
}

void Bookshelf::ShowUI(void)
{
    isShowUI_ = true;
}

void Bookshelf::HideUI(void)
{
    isShowUI_ = false;
    isLibraryOpen_ = false;
    if (libraryUI_) libraryUI_->Hide();
}

void Bookshelf::OnPlayerHit(void)
{
    ShowUI();
}

void Bookshelf::OnPlayerExit(void)
{
    HideUI();
}

bool Bookshelf::isVisible(void) const
{
    return libraryUI_->IsVisible();
}

Transform& Bookshelf::GetTransform(void)
{
    return trans_;
}
