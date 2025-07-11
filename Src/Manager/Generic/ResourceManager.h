#pragma once
#include<map>
#include<string>
#include"Resource.h"

class ResourceManager
{
public:

	//リソース名
	enum class SRC
	{
		//ここに保存しておきたい画像やモデル、音源などの名前を記す

		/*例*/
		TYTLE_LOGO,				//タイトルロゴ
		GAMEOVER_LOGO,			//ゲームオーバー
		GAMECLERA_LOGO,			//ゲームクリア

		//完成品アイテム
		RECOVERY_POTION,		//回復ポーション
		ANTIDOTE_POTION,		//解毒ポーション
		MAGIC_POTION,			//魔力ポーション
		GARBAGE,				//失敗の作品

		//材料
		HERB,					//薬草
		ANTIDOTE_HERB,			//解毒草
		MAGIC_FLOWER,			//魔力草
		WATER,					//水

		//種子
		SEED,					//種

		//ギルド関係
		BULLETIN_BOARD,			//掲示板
		IMAGE_BOARD,			//掲示板の画像

		//アトリエ関係
		BOOKS_HELF,				//本棚
		ALCHEMYPOT,				//錬金釜

		//庭関係
		BLOCK_DIRT,				//土ブロック
		BLOCK_GFRASS,			//草ブロック
		SEED_MODEL,				//発芽モデル
		GROWING_MODEL,			//成長中モデル
		MATURE_MODEL,			//成熟モデル
		ORE_MODEL,				//鉱石モデル
		FENCE_MODEL,			//フェンスモデル

		//ミニマップ関係
		MAP_FRAME,				//ミニマップ枠
		MAP_GROUND,				//ミニマップ枠内
		MAP_MASK,				//ミニマップマスク用
		MAP_PLAYER,				//ミニマップ用プレイヤー
		MAP_ENEMY,				//ミニマップ用敵

		//サウンド
		BGM_TITLE,				//タイトルBGM
		BGM_GAME,				//ゲームBGM
		BGM_GAMEOVER,			//ゲームオーバーBGM
		BGM_GAMECLEAR,			//ゲームクリアBGM

		SE_PUSH,				//ボタン決定音
		SE_DAMAGE,				//ダメージ音
		SE_GET,					//アイテム取得音
	};

	//明示的にインスタンスを生成する
	static void CreateInstance(void);

	//静的インスタンスの取得
	static ResourceManager& GetInstance(void); 

	//初期化
	void Init(void);

	//タイトルで使うリソース初期化
	void InitTitle(void);

	//ゲームで使うリソース初期化
	void InitGame(void);

	//ゲームオーバーで使うリソース初期化
	void InitGameOver(void);

	//ゲームクリアで使うリソース初期化
	void InitGameClear(void);

	//アトリエで使うリソース
	void ResourceAtelier(void);

	//ギルドで使うリソース
	void ResourceGuild(void);

	//庭で使うリソース
	void ResourceGarden(void);

	//プレイヤーが使うリソース
	void ResourcePlayer(void);

	//敵が使うリソース
	void ResourceEnemy(void);

	//解放(シーン切り替え時に一旦解放)
	void Release(void);

	//リソース完全破棄
	void Destroy(void);

	//リソースのロード
	Resource Load(SRC src);

	//リソースの複製ロード(モデル用)
	int LoadModelDuplicate(SRC src);

private:

	//静的インスタンス
	static ResourceManager* instance_;

	//リソース管理の対象
	std::map<SRC, Resource> resourcesMap_;

	//読み込み済みリソース
	std::map<SRC, Resource*> loadedMap_;

	// デフォルトコンストラクタをprivateにして、
	// 外部から生成できない様にする
	ResourceManager(void);

	//デストラクタも同様
	~ResourceManager(void) = default;

	//内部ロード
	Resource* _Load(SRC src);

};
