#include"ResourceManager.h"

#include<DxLib.h>

#include"../../Application.h"
#include"Resource.h"

// シングルトンのインスタンス初期化
ResourceManager* ResourceManager::instance_ = nullptr;

// インスタンス生成（初回のみ）＋初期化呼び出し
void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

// インスタンス参照を返す
ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

// 共通初期化処理（今は空）
void ResourceManager::Init(void)
{

}

// タイトルシーン用リソースの初期化
void ResourceManager::InitTitle(void)
{
	Resource res;

	// タイトルロゴ画像を登録
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "");
	resourcesMap_.emplace(SRC::TYTLE_LOGO, res);

	// タイトルBGMを登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "");
	resourcesMap_.emplace(SRC::BGM_TITLE, res);

	// 決定音を登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

// ゲームシーン用リソースの初期化
void ResourceManager::InitGame(void)
{
	Resource res;

	// ゲームBGMを登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "");
	resourcesMap_.emplace(SRC::BGM_GAME, res);

	// ダメージ音を登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "");
	resourcesMap_.emplace(SRC::SE_DAMAGE, res);

	// アイテム取得音を登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "");
	resourcesMap_.emplace(SRC::SE_GET, res);

	// プレイヤー関連リソースの初期化
	ResourcePlayer();

	// 敵関連リソースの初期化
	ResourceEnemy();
}

// ゲームオーバーシーン用リソースの初期化
void ResourceManager::InitGameOver(void)
{
	Resource res;

	// ゲームオーバーロゴ画像を登録
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "");
	resourcesMap_.emplace(SRC::GAMEOVER_LOGO, res);

	// ゲームオーバーBGMを登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "");
	resourcesMap_.emplace(SRC::BGM_GAMEOVER, res);

	// 決定音を登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

// ゲームクリアシーン用リソースの初期化
void ResourceManager::InitGameClear(void)
{
	Resource res;

	// ゲームクリアロゴ画像を登録
	res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "");
	resourcesMap_.emplace(SRC::GAMECLERA_LOGO, res);

	// ゲームクリアBGMを登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_BGM + "");
	resourcesMap_.emplace(SRC::BGM_GAMECLEAR, res);

	// 決定音を登録
	res = Resource(Resource::TYPE::SOUND, Application::PATH_SE + "");
	resourcesMap_.emplace(SRC::SE_PUSH, res);
}

// プレイヤー用リソース初期化（未実装）
void ResourceManager::ResourcePlayer(void)
{
	Resource res;
}

// 敵用リソース初期化
void ResourceManager::ResourceEnemy(void)
{
	Resource res;

	// 敵モデルを登録
	res = Resource(Resource::TYPE::MODEL, Application::PATH_MODEL + "");
	resourcesMap_.emplace(SRC::ENEMY, res);
}

// 全リソースの解放処理
void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second->Release(); // リソース解放
		delete p.second;     // メモリ解放
	}

	loadedMap_.clear();     // ロード済みリソースマップをクリア
	resourcesMap_.clear();  // 登録済みリソースマップをクリア
}

// インスタンス破棄処理
void ResourceManager::Destroy(void)
{
	Release();        // リソース解放
	delete instance_; // インスタンス削除
}

// リソースの読み込み（読み込み済みなら再利用）
Resource ResourceManager::Load(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource(); // 空のリソースを返す
	}
	return *res; // コピーして返す
}

// モデルの複製を行い、複製IDを返す
int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1; // 読み込み失敗
	}

	// モデル複製
	int duId = MV1DuplicateModel(res->handleId_);
	res->duplicateModelIds_.push_back(duId);

	return duId;
}

// コンストラクタ
ResourceManager::ResourceManager(void)
{
}

// 内部リソース読み込み処理
Resource* ResourceManager::_Load(SRC src)
{
	// すでに読み込み済みか確認
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		return lPair->second;
	}

	// 登録済みリソースか確認
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない
		return nullptr;
	}

	// リソース読み込み実行
	rPair->second.Load();

	// コピーを保持（読み込み済みマップに追加）
	Resource* ret = new Resource(rPair->second);
	loadedMap_.emplace(src, ret);

	return ret;
}
