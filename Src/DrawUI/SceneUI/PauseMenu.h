#pragma once

#include <string>
#include <vector>

class PauseMenu
{
public:
	enum class MODE_POUSE
	{
		SELECT,
		HOW_TO_PLAY,
		CONTROL,
	};

	PauseMenu(void);
	~PauseMenu(void) = default;

	// 表示/非表示
	void Show(void);
	void Hide(void);
	bool IsVisible(void) const;

	// 更新・描画
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// 結果取得
	bool IsDecisionMade(void) const;
	int GetSelectedIndex(void) const;

private:
	// 選択項目
	std::vector<std::string> menuItems_;
	std::vector<std::string> items_;
	int currentIndex_;
	bool visible_;
	bool decisionMade_;

	int controlHandle_;

	MODE_POUSE mode_;
};
