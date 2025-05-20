#pragma once

#include<string>

/// <summary>
/// すべてのアイテムの基底クラス
/// </summary>
class ItemBase
{
public:

	//コンストラクタ
	ItemBase(const std::string& name, const std::string& description, int quantity, int imageHandle);

	//デストラクタ
	virtual ~ItemBase(void) = default;

	//名前を取得
	const std::string& GetName(void) const;

	//説明を取得
	const std::string& GetDescription(void) const;

	//所持数を取得
	int GetQuantity(void) const;

	//画像を取得
	int GetImageHandle() const;

	//所持数を増やす
	void AddQuantity(int amount);

	//所持数を減らす(o未満にならない)
	void SubtractQuantity(int amount);

protected:
	std::string name_;			// アイテム名
	std::string description_;   //アイテムの説明
	int imageHandle_;			// アイテムID
	int quantity_;				// アイテムの在庫数
};

