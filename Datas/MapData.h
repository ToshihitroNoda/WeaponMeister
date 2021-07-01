#ifndef MAPDATA_H_
#define MAPDATA_H_

#include "../MyLib/DataCsv.h"

class MapData : public DataCsv
{
public:
	MapData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~MapData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif