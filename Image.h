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

	// �^�C���摜�̉摜�������擾����B
	static int GetGraphSize(std::string ImageHandle, int CellSizeX, int CellSizeY);
	static int ImageWidth; // �����ۑ��p
	static int ImageHeight; // �c���ۑ��p

	// UI�֌W
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

	// �w�i
	static int titleBack;
	static int titleLogo;
	static int mainmenuBack;
	static int buyBack;
	static int productionBack;

	static int skyBack;

	// �A�C�e���A�C�R��
	static std::vector<int> itemIcons;
	static std::vector<int> weaponIcons;

	// 3D���f��
	static int Player;
	static int fieldItem;
	static int Spruce_1;
	static int Terrain_Block_1;
};

#endif

