#include "PauseMenu.h"
#include <DxLib.h>
#include "../../Manager/Generic/InputManager.h"
#include "../../Application.h"

PauseMenu::PauseMenu()
	: currentIndex_(0), visible_(false), decisionMade_(false)
{
	menuItems_ = {
		"‘±‚¯‚é",
		"—V‚Ñ•û",
		"‘€ìà–¾",
		"ƒQ[ƒ€I—¹"
	};
}

void PauseMenu::Show()
{
	visible_ = true;
	currentIndex_ = 0;
	decisionMade_ = false;
}

void PauseMenu::Hide()
{
	visible_ = false;
	decisionMade_ = false;
}

bool PauseMenu::IsVisible() const
{
	return visible_;
}

bool PauseMenu::IsDecisionMade() const
{
	return decisionMade_;
}

int PauseMenu::GetSelectedIndex() const
{
	return currentIndex_;
}

void PauseMenu::Update()
{
    if (mode_ == MODE_POUSE::SELECT)
    {
		if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_UP))
		{
			currentIndex_ = (currentIndex_ + menuItems_.size() - 1) % menuItems_.size();  // C³
		}
		if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_DOWN))
		{
			currentIndex_ = (currentIndex_ + 1) % menuItems_.size();  // C³
		}

        if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_RETURN))
        {
            if (currentIndex_ == 0) // ‘±‚¯‚é
            {
                visible_ = false;
            }
            else if (currentIndex_ == 1) // —V‚Ñ•û
            {
                mode_ = MODE_POUSE::HOW_TO_PLAY;
            }
            else if (currentIndex_ == 2) // ‘€ìà–¾
            {
                mode_ = MODE_POUSE::CONTROL;
            }
            else if (currentIndex_ == 3) // ƒQ[ƒ€I—¹
            {
                decisionMade_ = true;
            }
        }
    }
    else
    {
        // X‚Å–ß‚é
        if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_X))
        {
            mode_ = MODE_POUSE::SELECT;
        }
    }
}

void PauseMenu::Draw()
{
    if (!visible_) return;

    const int screenW = Application::DEFA_SCREEN_SIZE_X;
    const int screenH = Application::DEFA_SCREEN_SZIE_Y;

    // u—V‚Ñ•ûv‚©u‘€ìà–¾v‚Ì‚Æ‚«‚Í‰æ–Ê‘S‘Ì‚ğ•‚­“h‚é
    if (mode_ == MODE_POUSE::HOW_TO_PLAY || mode_ == MODE_POUSE::CONTROL)
    {
        DrawBox(0, 0, screenW, screenH, GetColor(0, 0, 0), TRUE);

        // TODO: ‚±‚±‚Éà–¾•¶‚Ì•`‰æ‚È‚Ç‚à“ü‚ê‚ç‚ê‚Ü‚·
        const char* message = (mode_ == MODE_POUSE::HOW_TO_PLAY) ? "—V‚Ñ•ûà–¾..." : "‘€ìà–¾...";
        DrawString(50, 50, message, GetColor(255, 255, 255));
        DrawString(50, 100, "–ß‚é‚É‚ÍXƒL[‚ğ‰Ÿ‚µ‚Ä‚­‚¾‚³‚¢", GetColor(255, 255, 255));
        return;
    }

    // ’Êí‚Ìƒƒjƒ…[•\¦‚Í‚±‚±‚©‚ç
    const int boxW = 400;
    const int boxH = static_cast<int>(menuItems_.size()) * 50 + 40;

    const int x = (screenW - boxW) / 2;
    const int y = (screenH - boxH) / 2;

    // ƒƒjƒ…[”wŒi
    DrawBox(x, y, x + boxW, y + boxH, GetColor(0, 0, 0), TRUE);

    // ˜gü
    DrawBox(x, y, x + boxW, y + boxH, GetColor(255, 255, 255), FALSE);

    // ƒƒjƒ…[€–Ú•`‰æ
    for (int i = 0; i < menuItems_.size(); ++i)
    {
        int itemY = y + 20 + i * 50;
        if (i == currentIndex_)
        {
            DrawBox(x + 10, itemY - 5, x + boxW - 10, itemY + 30, GetColor(100, 100, 255), TRUE);
        }
        DrawString(x + 20, itemY, menuItems_[i].c_str(), GetColor(255, 255, 255));
    }
}
