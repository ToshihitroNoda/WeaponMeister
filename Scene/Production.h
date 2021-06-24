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
	GameManager& gm  = GameManager::GetInstance(); // �Q�[���}�l�[�W���[�ւ̎Q��
	SceneManager& sm = SceneManager::GetInstance(); // �V�[���}�l�[�W���[�ւ̎Q��

	Production() : Scene() // �R���X�g���N�^
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
	{ "����̎悵���f�ނ𑁑����H���ĕ��������Ă݂܂��傤�I",
	  "�܂��쐬���镐���I�����܂��B�쐬�ł��镐��͓��ɂ����o���Ƃɑ����Ă����܂��B",
	  "���Ɏ����蕔���̑f�ނ�I�����܂��B�I���ł���͖̂؂̊p�ނ̑f�ނ݂̂ł��B",
	  "�����蕔���̑f�ނ�I�������玟�ɓ��g�����̑f�ނ�I�����܂��B�쐬���镐��ɂ���đI�ׂ�f�ނ��ς��܂��B",
	  "���ꂼ��̃Z�N�V������X�L�[�������ƑO�̃Z�N�V�����ɖ߂邱�Ƃ��ł��܂��B",
	  "��肽����������ׂč��I�������쐬����I����ʂ�END�������Ǝ��̉�ʂɐi�݂܂��B",
	  "�ȏオ�����ɂȂ�܂��B����ł͑������������Ă݂܂��傤�I"
	};
};

#endif