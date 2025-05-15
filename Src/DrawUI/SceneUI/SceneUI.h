#pragma once

#include<vector>

/// <summary>
/// シーンUIの描画や文字列制御を行うクラス
/// </summary>
class SceneUi
{
public:
	/// <summary>
	///文字データ構造体
	/// </summary>
	struct FontData
	{
		const char* message; ///表示する文字列
	};

	/// <summary>
	///コンストラクタ
	/// </summary>
	SceneUi(void);

	/// <summary>
	///デストラクタ
	/// </summary>
	~SceneUi(void);

	/// <summary>
	///描画処理
	/// <summary>
	void Draw(void);

	/// <summary>
	///フォント点滅設定
	/// </summary> 
	void FontBlinking(void);

	/// <summary>
	///フォント描画
	/// </summary>
	void DrawFont(void);

	/// <summary>
	///文字列の追加
	/// </summary>
	/// <param name="_char">追加する文字列</param>
	void AddCharctor(const char* _char);

private:

	/// <summary>
	///フレームレート制御のための変数
	/// </summary>
	int frameCount_;

	/// <summary>
	///点滅間隔(フレーム数)
	/// </summary>
	const int blinkInterval_ = 30;

	/// </summary>
	///点滅フラグ（true: 表示、false: 非表示）
	/// </summary>
	bool isBlinking_;

	/// </summary>
	///切り替えフラグ
	/// </summary>
	bool changeFlag_;

	/// </summary>
	///フォント追加
	/// </summary>
	std::vector<FontData> fontList_;
};
