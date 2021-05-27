#ifndef IMAGE_H_
#define IMAGE_H_

#include "DxLib.h"
#include <string>
#include <vector>

class Image
{
public:
	Image() = default;
	~Image() = default; 

	void Load(std::string SceneName);
	void Final();
	void LoadDivGraph(std::string fileName, int allNum, int xNum, int yNum, int xSize, int ySize, int* hundleArray);

	// タイル画像の画像総数を取得する。
	int GetGraphSize(std::string ImageHandle, int CellSizeX, int CellSizeY);
	int ImageWidth{ 0 }; // 横幅保存用
	int ImageHeight{ 0 }; // 縦幅保存用

	// UI関係
	std::vector<int> dayNum		{ NULL }; 
	std::vector<int> scores     { NULL };
	int arrow					{ -1 };
	int pressStartButton		{ -1 };
	int menuCursor				{ -1 };
	int dayWindow				{ -1 };
	int itemIconWindow			{ -1 };
	int itemWindow				{ -1 };
	int shopWindow				{ -1 };
	int itemSelection			{ -1 };
	int recipeWindow			{ -1 };
	int recipeSelection			{ -1 };
	int detailWindow			{ -1 };
	int moneyWindow				{ -1 };
	int salePriceWindow			{ -1 };
	int selectItemWindow		{ -1 };
	int textWindow				{ -1 };
	int textCursor				{ -1 };
	int next					{ -1 };
	int nextCursor				{ -1 };
	int end						{ -1 };
	int buy						{ -1 };
	int sale					{ -1 };
	int collectionStart			{ -1 };
	int collectionEnd			{ -1 };
	int watchBase               { -1 };
	int watchPointer            { -1 };
	int rank                    { -1 };

	// 背景
	int titleBack				{ -1 };
	int titleLogo				{ -1 };
	int mainmenuBack			{ -1 };
	int worldMap				{ -1 };
	int mapIcon_1				{ -1 };
	int mapIcon_2				{ -1 };
	int mapIcon_3				{ -1 };
	int mapIcon_4				{ -1 };
	int mapIcon_5				{ -1 };
	int buyBack					{ -1 };
	int productionBack			{ -1 };
	int saleBack				{ -1 };
	int reportBack				{ -1 };

	int skyBack					{ -1 };	
	int rockBack				{ -1 };
	int volcanoBack				{ -1 };

	// アイテムアイコン
	std::vector<int> itemIcons	{ NULL };
	std::vector<int> weaponIcons{ NULL };

	// 3Dモデル
	int Player					{ -1 };
	int fieldItem				{ -1 };

	int Terrain_Block_1			{ -1 };
	int Terrain_Block_2			{ -1 };
	int Terrain_Block_3			{ -1 };
	int Terrain_Block_4			{ -1 };

	int Branch_1				{ -1 };
	int Branch_2				{ -1 };
	int Branch_3				{ -1 };
	int Branch_4				{ -1 };
	int Branch_group			{ -1 };
	int Bush_1					{ -1 };
	int Bush_2					{ -1 };
	int Bush_3					{ -1 };
	int Bush_4					{ -1 };
	int Bush_large_1			{ -1 };
	int Bush_large_2			{ -1 };
	int Cliff_rock_1			{ -1 };
	int Cliff_rock_2			{ -1 };
	int Cliff_rock_3			{ -1 };
	int Cliff_rock_4			{ -1 };
	int Cliff_rock_5			{ -1 };
	int Crystal_1				{ -1 };
	int Crystal_2				{ -1 };
	int Crystal_3				{ -1 };
	int Crystal_4				{ -1 };
	int Crystal_5				{ -1 };
	int Rock_1					{ -1 };
	int Rock_2					{ -1 };
	int Rock_3					{ -1 };
	int Rock_4					{ -1 };
	int Rock_5					{ -1 };
	int Spruce_1				{ -1 };
	int Spruce_2				{ -1 };
	int Spruce_3				{ -1 };
	int Trunk					{ -1 };

	std::vector<int> ModelHandles;
};

#endif

