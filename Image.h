#ifndef IMAGE_H_
#define IMAGE_H_

#include "DxLib.h"
#include <string>
#include <assert.h>
#include <vector>

class Image
{
public:
	Image() {};
	~Image() {}; 

	static void Load();
	
	static void LoadDivGraph(std::string fileName, int allNum, int xNum, int yNum, int xSize, int ySize, int* hundleArray);

	// タイル画像の画像総数を取得する。
	static int GetGraphSize(std::string ImageHandle, int CellSizeX, int CellSizeY);
	static int ImageWidth; // 横幅保存用
	static int ImageHeight; // 縦幅保存用

	// UI関係
	static std::vector<int> dayNum;
	static int arrow;
	static int pressStartButton;
	static int menuCursor;
	static int dayWindow;
	static int itemIconWindow;
	static int itemWindow;
	static int shopWindow;
	static int itemSelection;
	static int recipeWindow;
	static int recipeSelection;
	static int detailWindow;
	static int moneyWindow;
	static int salePriceWindow;
	static int selectItemWindow;
	static int textWindow;
	static int textCursor;
	static int next;
	static int nextCursor;
	static int end;
	static int buy;
	static int sale;
	static int mapIcon;
	static int mapCursor;
	static int collectionStart;

	// 背景
	static int titleBack;
	static int titleLogo;
	static int mainmenuBack;
	static int buyBack;
	static int productionBack;

	static int skyBack;

	// アイテムアイコン
	static std::vector<int> itemIcons;
	static std::vector<int> weaponIcons;

	// 3Dモデル
	static int Player;
	static int fieldItem;
	static int Spruce_1;
	static int Terrain_Block_1;
};

#endif

