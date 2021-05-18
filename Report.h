#ifndef REPORT_H_
#define REPORT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

class Report :  public Scene
{
public:
	GameManager& gm = GameManager::GetInstance(); // �Q�[���}�l�[�W���[�ւ̎Q��
	SceneManager& sm = SceneManager::GetInstance(); // �V�[���}�l�[�W���[�ւ̎Q��

	Report() : Scene() // �R���X�g���N�^
	{
		this->tag = "Report";
	}
	~Report() = default;

	void Init() override;
	void Final() override;
	void Update() override;
	void Draw() override;

	static int prevMoney;
private:
	const int LastDay_ = 14;

	const float RentBase_ = 100;
	const float RentMultiplied_ = 1.5f;

	const int NextMassegeX_ = 900;
	const int NextMassegeY_ = 600;

	const int PrevMoneyX_	= 200;
	const int PrevMoneyY_	= 200;
	const int BuyAmountX_	= 200;
	const int BuyAmountY_	= 300;
	const int SaleAmountX_  = 200;
	const int SaleAmountY_  = 400;
	const int HaveMoneyX_   = 700;
	const int HaveMoneyY_	= 200;
	const int RentX_		= 700;
	const int RentY_		= 300;
	const int FinalMoneyX_  = 700;
	const int FinalMoneyY_  = 400;

	const int DrawDataNums_   = 6;
	const int prevDraw_		  = 1;
	const int buyAmountDraw_  = 2;
	const int saleAmountDraw_ = 3;
	const int haveMoneyDraw_  = 4;
	const int rentDraw_		  = 5;
	const int finalMoneyDraw_ = 6;

	const int FontSize_ = 30;

	int firstMoney_  = 0;
	int Rent_		= 0; // �ƒ��B��{�z * (���ɂ� * 1.5)
	int finalMoney_ = 0;

	int pressCount_ = 0;
};

#endif