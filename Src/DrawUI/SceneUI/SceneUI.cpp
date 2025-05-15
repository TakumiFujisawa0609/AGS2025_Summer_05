#include"SceneUI.h"

#include<DxLib.h>

#include"../../DrawUI/Font.h"
#include"../../Application.h"

//コンストラクタ
SceneUi::SceneUi(void)
{
	//フレームレート制御
	frameCount_ = 0;

	//点滅フラグ
	isBlinking_ = false;

	//切り替えフラグ
	changeFlag_ = false;
}

//デストラクタ
SceneUi::~SceneUi(void)
{

}

//描画処理
void SceneUi::Draw(void)
{
	DrawFont();
}

//フォントの描画処理
void SceneUi::DrawFont(void)
{
	for (const auto& font : fontList_)
	{
		//文字幅取得
		int textWidth = GetDrawStringWidth(font.message, static_cast<int>(strlen(font.message)));

#ifdef _DEBUG
		
		int xPos = (Application::SCREEN_SIZE_X - textWidth) / 2;
		int yPos = Application::SCREEN_SIZE_Y / 2;

#else
		int xPos = (Application::DEFA_SCREEN_SIZE_X - textWidth) / 2;
		int yPos = Application::DEFA_SCREEN_SZIE_Y / 2;
#endif // _DEBUG

		if (isBlinking_)
		{
			Font::GetInstance().DrawDefaultText(xPos, yPos, font.message, 0xFFFFFF, 24, Font::FONT_TYPE_NORMAL);
		}
		else
		{
			Font::GetInstance().DrawDefaultText(xPos, yPos, font.message, 0xAAAAAA, 24, Font::FONT_TYPE_NORMAL);
		}
	}
}

//フォント点滅設定
void SceneUi::FontBlinking(void)
{
	//更新処理
	frameCount_++;

	//点滅タイミング(一定のフレーム事に切り替え)
	isBlinking_ = (frameCount_ / blinkInterval_) % 2 ? true : false;
}

//フォントの追加
void SceneUi::AddCharctor(const char* _char)
{
	fontList_.push_back(FontData{ _char });
}