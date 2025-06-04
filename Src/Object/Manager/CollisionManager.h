#pragma once

#include<DxLib.h>
#include<vector>

#include"../../Manager/System/Collision.h"
#include"../Interact/HitObject.h"

class CollisionManager
{
public:
	//インスタンスの生成
	static void CreateInstance(void);

	//インスタンスの取得
	static CollisionManager& GetInstance(void);

	//初期化処理
	void Init(void);

	//登録(ポインタ渡し)
	void Register(HitObject* obj);

	//全てクリア
	void Clear(void);

	//プレイヤーとの当たり判定チェック(UI表示)
	void CheckHitWithPlayer(const VECTOR playerPos, float PlayerRadus);

private:

	//静的インスタンス
	static CollisionManager* instance_;
	
	//コンストラクタ
	CollisionManager(void) = default;

	//デストラクタ
	~CollisionManager(void) = default;

	std::vector<HitObject*> hitObjects_;

};

