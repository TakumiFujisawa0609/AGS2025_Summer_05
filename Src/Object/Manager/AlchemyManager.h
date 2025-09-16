#pragma once

#include<vector>
#include<memory>
#include<map>

#include "../Item/Material/MaterialItem.h"
#include "../Item/Product/ProductItem.h"
#include "AlchemyRecipe.h"


class AlchemyManager
{
public:

	enum class ALCHEMYRESULT
	{
		NONE,
		SUCCESS,
		FAILURE
	};


	const int MAX_COLUMNS = 5;

	static void CreateInstance();
	static AlchemyManager& GetInstance();
	static void Destroy();

	//初期化処理
	void Init(void);

	//更新処理
	void Update(void);

	//描画処理
	void Draw(void);

	//入力処理
	void Open(void);
	void Close(void);
	bool IsOpen(void) const;

	void ShowRecipeDifferenceMessage(const std::map<std::string, int>& selectedMap);

	//レシピと選択素材の差分をメッセージとして表示する
	const AlchemyRecipe* FindClosestRecipe(const std::map<std::string, int>& selectedMap);


private:

	//コンストラクタ
	AlchemyManager(void);

	//デストラクタ
	~AlchemyManager(void);

	/*void SelectMaterial(void);

	void SelectAmount(void);*/

	void ExecuteAlchemy(void);

	void ResetSelection(void);

	struct SelectedMaterial
	{
		std::shared_ptr<MaterialItem> item;
		int amount;
	};

	std::vector<SelectedMaterial> selectedMaterials_;
	
	std::vector<AlchemyRecipe> recipes_;

	std::string pendingResultMessage_;

	int currentPhase_;

	int currentIndex_;

	int currentAmount_;

	// 個数選択中の素材Index
	int selectedMaterialIndex_; 

	//個数選択中の素材
	int selectedMaterialEditIndex_;


	bool isOpen_;

	bool waitingForSEFinish_;

	bool effectPlayedDuringAlchemy_;

	static AlchemyManager* instance_;

	bool start_;

	// 生成結果のメッセージ
	std::string resultMessage_;    

	// 表示タイマー（フレーム数）
	int resultMessageTimer_;       

	ALCHEMYRESULT alchemyResult_;
};

