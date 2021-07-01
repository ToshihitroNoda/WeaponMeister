#ifndef ITEMDATA_H_
#define ITEMDATA_H_

#include "../MyLib/DataCsv.h"

class ItemData : public DataCsv
{
public:
	ItemData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ItemData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif