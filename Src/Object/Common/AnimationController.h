#pragma once

#include<string>
#include<map>
class SceneManager;

class AnimationController
{
public:

	//アニメーションデータ
	struct Animation
	{
		int model = -1;
		int attachNo = -1;
		int amimIndex = 0;
		float speed = 0.0f;
		float totalTime = 0.0f;
		float step = 0.0f;
	};

	//コンストラクタ
	AnimationController(int modeiId);

	//デストラクタ
	~AnimationController(void);

	//アニメーション追加
	void Add(int type, const std::string& path, float speed);

	/// <summary>
	/// アニメーション再生
	/// </summary>
	/// <param name="type">アニメーションの種類</param>
	/// <param name="isLoop">ループするか</param>
	/// <param name="startStep">途中開始する時間</param>
	/// <param name="endStep">終了時間</param>
	/// <param name="isStop">止めるか</param>
	/// <param name="isForce">強制変更するか</param>
	void Play(int type, bool isLoop = true,float startStep = 0.0f, float endStep = -1.0f, bool isStop = false, bool isForce = false);

	//更新処理
	void Update(void);

	//アニメーション終了後に繰り返すループステップ
	void SetEndLoop(float startStep, float endStep, float speed);

	//再生中のアニメーション
	int GetPlayType(void) const;

	//再生終了
	bool IsEnd(void) const;

private:

	//モデルのハンドルID
	int modelId_;

	//種類別のアニメーションデータ
	std::map<int, Animation> animations_;

	int PlayType_;
	Animation playAnim_;

	//アニメーションをループするかしないか
	bool isLoop_;

	//アニメーションを止めたままにする
	bool isStop_;

	//アニメーション終了後に繰り返すループステップ
	float stepEndLoopStart_;

	float stepEndLoopEnd_;

	float endLoopSpeed_;

	//逆再生
	float switchLoopReverse_;
};

