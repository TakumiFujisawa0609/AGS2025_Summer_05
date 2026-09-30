#include "PrivateRoomStage.h"

#include <DxLib.h>

#include "../Application.h"
#include "../Manager/Generic/Resource.h"
#include "../Manager/Generic/ResourceManager.h"
#include "../Manager/Generic/InputManager.h"
#include "../Object/Manager/StageManager.h"

PrivateRoomStage::PrivateRoomStage(void)
{
}

void PrivateRoomStage::Init(void)
{
}

void PrivateRoomStage::Update(void)
{
    auto& inputManager = InputManager::GetInstance();
}

void PrivateRoomStage::Draw(void)
{
    const int DRAW_X = 0;
    const int DRAW_Y = 20;
    const int COLOR_WHITE = 0xffffff;

    DrawFormatString(DRAW_X, DRAW_Y, COLOR_WHITE, "プライベート");
}

void PrivateRoomStage::Release(void)
{
}