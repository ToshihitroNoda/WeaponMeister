#ifndef DATALOAD_H_
#define DATALOAD_H_

#include<fstream>
#include<vector>

#include "Scene/Adv.h"
#include "Scene/StageSelection.h"
#include "GameManager.h"

struct LStatus {
	int day;
	int money;
	int mapCount;
	int pouchSize;
	int weaponSize;
};

class DataLoad
{
public:
	GameManager& gm = GameManager::GetInstance();

	DataLoad()  = default;
	~DataLoad() = default;

	std::fstream file;

	void Load()
	{
		/* �Z�[�u����ׂ����̂�
		* ���ɂ��A�|�[�`���̃A�C�e���E�����A���ꂼ��̕i���A������
		*/

		LStatus lStatus = { 0 };

		file.open("savedata.dat", std::ios::binary | std::ios::in);

		file.read((char*)&lStatus, sizeof(lStatus));

		Adv::day                 = lStatus.day;
		gm.money                 = lStatus.money;
		StageSelection::mapCount = lStatus.mapCount;

		// ���[�h�O�ɉ����f�[�^���������܂�Ă�����d������̂�clear()
		gm.weapons.clear();
		gm.pouch.clear();

		for (int i = 0; i < lStatus.pouchSize; i++)
		{
			int loadItemData;
			int loadQualityData;
			// �A�C�e��ID�̓ǂݍ���
			file.read((char*)&loadItemData, sizeof(loadItemData)); 
			// �|�C���^�̈ʒu��i���̏ꏊ�ɂ��炷
			file.seekg((5 + i + lStatus.pouchSize) * sizeof(loadItemData));
			// �i���̓ǂݍ���
			file.read((char*)&loadQualityData, sizeof(loadQualityData)); 
			// �A�C�e��ID�ƕi����ǉ�
			gm.pouch.Add(loadItemData, loadQualityData);
			// �|�C���^�̈ʒu����i�߂�
			file.seekg((6 + i) * sizeof(loadItemData));
		}

		// ����f�[�^���ۑ�����Ă���ꏊ(LStatus�� + pouch�� + pouch�i����)
		int weaponDataPos = 5 + lStatus.pouchSize * 2;
		// �|�C���^�̈ʒu�𕐊�̏ꏊ�ɂ��炷
		file.seekg((weaponDataPos) * sizeof(int)); 

		for (int i = 0; i < lStatus.weaponSize; i++)
		{
			int loadWeaponData;
			int loadQualityData;
			// ����ID�̓ǂݍ���
			file.read((char*)&loadWeaponData, sizeof(loadWeaponData));
			// �|�C���^�̈ʒu��i���̏ꏊ�ɂ��炷
			file.seekg((weaponDataPos + i + lStatus.weaponSize) * sizeof(loadWeaponData));
			// �i���̓ǂݍ���
			file.read((char*)&loadQualityData, sizeof(loadQualityData)); 
			// ����ID�ƕi����ǉ�
			gm.weapons.Add(loadWeaponData, loadQualityData);
			// �|�C���^�̈ʒu����i�߂�
			file.seekg((6 + i) * sizeof(loadWeaponData));
		}

		file.close();
	}
};

#endif
