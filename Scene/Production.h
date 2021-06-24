#ifndef PRODUCTION_H_
#define PRODUCTION_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "DataCsv.h"
#include "Screen.h"
#include "RecipeSelect.h"
#include "ItemSelect.h"
#include "HandleItemSelect.h"
#include "MainItemSelect.h"
#include "CreateRun.h"
#include "ProductionFlagManager.h"

class Production : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance(); // ゲームマネージャーへの参照
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャーへの参照

	Production() : Scene() // コンストラクタ
	{
		this->tag = "Production";
	}
	~Production() {};

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static std::vector<bool> canWeaponMake_;

private:
	RecipeSelect recipeSelect_;
	ItemSelect itemSelect_;
	HandleItemSelect handleItemSelect_;
	MainItemSelect mainItemSelect_;
	CreateRun createRun_;
	ProductionFlagManager productionFlag_;

	void Format();

	int operationDescriptionMassegeNum_ = 0;
	bool is_Operation_Description_Been_ = false;

	std::string description_[7]
	{ "先程採取した素材を早速加工して武器を作ってみましょう！",
	  "まず作成する武器を選択します。作成できる武器は日にちが経つごとに増えていきます。",
	  "次に持ち手部分の素材を選択します。選択できるのは木の角材の素材のみです。",
	  "持ち手部分の素材を選択したら次に刀身部分の素材を選択します。作成する武器によって選べる素材が変わります。",
	  "それぞれのセクションでXキーを押すと前のセクションに戻ることができます。",
	  "作りたい武器をすべて作り終わったら作成武器選択画面でENDを押すと次の画面に進みます。",
	  "以上が説明になります。それでは早速武器を作ってみましょう！"
	};
};

#endif