#ifndef REPORT_H_
#define REPORT_H_

#include "Scene.h"
#include "SceneManager.h"
#include "../GameManager.h"
#include "../DataSave.h"

class Report : public Scene
{
public:
	GameManager& gm  = GameManager::GetInstance(); // �Q�[���}�l�[�W���[�ւ̎Q��
	SceneManager& sm = SceneManager::GetInstance(); // �V�[���}�l�[�W���[�ւ̎Q��

	Report() : Scene() // �R���X�g���N�^
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
	int Rent_       = 0; // �ƒ��B��{�z * (���ɂ� * 2)
	int nextRent_   = 0;
	int finalMoney_ = 0;

	int pressCount_ = 0;

	int autoSaveCount_ = 120;

	int operationDescriptionMessageNum_ = 0;

	bool is_Operation_Description_Been_ = false;

	std::string description_[6]
	{ "1���̍Ō�ɍ����̎��x�̊m�F���ł��܂��B",
	  "�O���̏������A�������Ŏg�������z�A���p�ŉ҂������z�A",
	  "���݂̏������A�����̉ƒ��A�����̉ƒ���6���m�F���邱�Ƃ��ł��܂��B",
	  "�����̏������Ƃɗ����ȍ~�������Ă����܂��傤�B",
	  "�܂��A���̉�ʂŃI�[�g�Z�[�u���s���܂��B",
	  "�ȏオ�����ɂȂ�܂��B�������Ƃɗ����ȍ~���ǂ��X�܌o�c�����܂��傤�I"
	};
};

#endif