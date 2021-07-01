#ifndef ITEMDATA_H_
#define ITEMDATA_H_

#include "../MyLib/DataCsv.h"

class ItemData : public DataCsv
{
public:
	ItemData(std::string filePath = "", std::string csvOption = "DATA") : DataCsv(filePath)
	{
	};
	~ItemData() { clear(); };//お掃除処理はこちら
	// csvファイルの読み込み
	void Load(std::string filePath)
	{
		assert(filePath != "" && "ファイル名filePathを設定して！" != "");
		DataCsv::LoadData(filePath);
	}
};

#endif