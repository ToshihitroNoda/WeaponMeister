#ifndef MAPDATA_H_
#define MAPDATA_H_

#include "../MyLib/DataCsv.h"

class MapData : public DataCsv
{
public:
	MapData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~MapData() { clear(); };//���|�������͂�����
	// csv�t�@�C���̓ǂݍ���
	void Load(std::string filePath)
	{
		assert(filePath != "" && "�t�@�C����filePath��ݒ肵�āI" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif