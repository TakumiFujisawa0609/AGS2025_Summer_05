#pragma once

#include <DxLib.h>
#include <vector>
#include <memory>

#include "../Interact/HitObject.h"
#include "../NullHitObject.h"

class CollisionManager
{
public:
	// 表示開始距離
	static constexpr float SHOW_RADIUS = 50.0f; 
	
	// 非表示開始距離（少し大きく）
	static constexpr float HIDE_RADIUS = 60.0f; 

	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static CollisionManager& GetInstance(void);

	// 初期化処理
	void Init(void);


	// 登録(ポインタ渡し)
	void Register(const std::shared_ptr<HitObject>& obj);

	// 全てクリア
	void Clear(void);

	// プレイヤーとの当たり判定チェック(UI表示)
	void CheckHitWithPlayer(VECTOR& playerPos, float playerRadius);


	// リソースの解放
	void Destroy(void);

private:

	// 静的インスタンス
	static CollisionManager* instance_;

	// コンストラクタ
	CollisionManager(void) = default;

	// デストラクタ
	~CollisionManager(void) = default;

	std::vector<std::shared_ptr<HitObject>> hitObjects_;

	NullHitObject nullObject_;

	HitObject* SafeGet(HitObject* obj);
};
