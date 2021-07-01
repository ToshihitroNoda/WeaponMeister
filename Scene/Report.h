#ifndef REPORT_H_
#define REPORT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../DataSave.h"

class Report : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance(); // ゲームマネージャーへの参照
	SceneManager& sm = SceneManager::GetInstance(); // シーンマネージャーへの参照

	Report() : Scene() // コンストラクタ
	{
		this->tag = "Report";
	}
	~Report() = default;

	void Init() override;
	void Final() override;
	void Update() override;
	void Change() override;
	void Draw() override;

	static int prevMoney;

private:
	DataSave dataSave_;

	const int LastDay_ = 14;

	const int NextMessageX_ = 900;
	const int NextMessageY_ = 650;

	const int AutoSaveX_ = 1000;
	const int AutoSaveY_ = 10;

	const int PrevMoneyX_  = 200;
	const int PrevMoneyY_  = 200;
	const int BuyAmountX_  = 200;
	const int BuyAmountY_  = 300;
	const int SaleAmountX_ = 200;
	const int SaleAmountY_ = 400;
	const int HaveMoneyX_  = 700;
	const int HaveMoneyY_  = 200;
	const int RentX_       = 700;
	const int RentY_       = 300;
	const int FinalMoneyX_ = 700;
	const int FinalMoneyY_ = 400;
	const int NextRentX_   = 700;
	const int NextRentY_   = 500;

	const int DrawDataNums_   = 7;
	const int prevDraw_       = 1;
	const int buyAmountDraw_  = 2;
	const int saleAmountDraw_ = 3;
	const int haveMoneyDraw_  = 4;
	const int rentDraw_       = 5;
	const int finalMoneyDraw_ = 6;
	const int nextRentDraw_   = 7;

	const int FontSize_ = 30;

	const float RentBase_       = 100.0f;
	const float RentMultiplied_ = 2.0f;

	int firstMoney_ = 0;
	int Rent_       = 0; // 家賃。基本額 * (日にち * 2)
	int nextRent_   = 0;
	int finalMoney_ = 0;

	int pressCount_ = 0;

	int autoSaveCount_ = 120;

	int operationDescriptionMessageNum_ = 0;

	bool is_Operation_Description_Been_ = false;

	std::string description_[6]
	{ "1日の最後に今日の収支の確認ができます。",
	  "前日の所持金、買い物で使った金額、売却で稼いだ金額、",
	  "現在の所持金、今日の家賃、明日の家賃の6つを確認することができます。",
	  "これらの情報をもとに翌日以降活動していきましょう。",
	  "また、この画面でオートセーブが行われます。",
	  "以上が説明になります。情報をもとに翌日以降より良い店舗経営をしましょう！"
	};
};

#endif