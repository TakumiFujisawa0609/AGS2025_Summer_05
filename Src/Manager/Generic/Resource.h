#pragma once
#include<string>
#include<vector>

class Resource
{

public:

	//リソースタイプ
	enum class TYPE
	{
		NONE,
		IMG,
		IMGS,
		MASK,
		MODEL,
		ANIM,
		EFFEKSEER,
		SOUND,
	};

	//コンストラクタ
	Resource(void);

	//コンストラクタ
	Resource(TYPE type, const std::string& path);

	//コンストラクタ(IMGS用)
	Resource(TYPE type, const std::string& path);

	//デストラクタ
	~Resource(void);

	//読み込み
	void Load(void);

	//解放
	void Release(void);

	//複数画像ハンドルを別配にコピー
	void CoopyHandle(int* imgs);

	//リソースタイプ
	TYPE resType_;
};