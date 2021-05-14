#include "Image.h"

int Image::ImageWidth				{ 0 };
int Image::ImageHeight				{ 0 };

// UIä÷åW
std::vector<int> Image::dayNum		{ NULL };
int Image::arrow					{ -1 };
int Image::pressStartButton			{ -1 };
int Image::menuCursor				{ -1 };
int Image::dayWindow				{ -1 };
int Image::itemIconWindow			{ -1 };
int Image::itemWindow				{ -1 };
int Image::shopWindow				{ -1 };
int Image::itemSelection			{ -1 };
int Image::recipeWindow				{ -1 };
int Image::recipeSelection			{ -1 };
int Image::detailWindow				{ -1 };
int Image::moneyWindow				{ -1 };
int Image::salePriceWindow			{ -1 };
int Image::selectItemWindow			{ -1 };
int Image::textWindow				{ -1 };
int Image::textCursor				{ -1 };
int Image::next						{ -1 };
int Image::nextCursor				{ -1 };
int Image::end						{ -1 };
int Image::buy						{ -1 };
int Image::sale						{ -1 };
int Image::mapIcon					{ -1 };
int Image::mapCursor				{ -1 };

// îwåi
int Image::titleBack				{ -1 };
int Image::titleLogo				{ -1 };
int Image::mainmenuBack				{ -1 };
int Image::buyBack					{ -1 };
int Image::productionBack			{ -1 };

int Image::skyBack					{ -1 };

// ÉAÉCÉeÉÄÉAÉCÉRÉì
std::vector<int> Image::itemIcons	{ NULL };
std::vector<int> Image::weaponIcons	{ NULL };

int Image::Player					{ -1 };
int Image::fieldItem				{ -1 };
int Image::Spruce_1					{ -1 };
int Image::Terrain_Block_1			{ -1 };

int Image::GetGraphSize(std::string ImageHandle, int CellSizeX, int CellSizeY)
{
	int imageHandle = LoadGraph(ImageHandle.c_str()); // âÊëúì«Ç›çûÇ›
	DxLib::GetGraphSize(imageHandle, &ImageWidth, &ImageHeight); // ÉTÉCÉYéÊìæ
	return (ImageWidth / CellSizeX) * (ImageHeight / CellSizeY); // ëçêîÇï‘ãp
}

void Image::LoadDivGraph(std::string fileName, int allNum, int xNum, int yNum, int xSize, int ySize, int* hundleArray)
{
	DxLib::LoadDivGraph(fileName.c_str(), allNum, xNum, yNum, xSize, ySize, hundleArray);
}

void Image::Load()
{
	// UIä÷åW
	dayNum.resize(GetGraphSize("Resource/Image/daynum.png", 255, 141));
	LoadDivGraph("Resource/Image/daynum.png", 15, 15, 1, 255, 141, &dayNum[0]);
	arrow					= LoadGraph("Resource/Image/arrow.png");
	pressStartButton		= LoadGraph("Resource/Image/pressstartbutton.png");
	menuCursor				= LoadGraph("Resource/Image/menucursor.png");
	dayWindow				= LoadGraph("Resource/Image/daywindow.png");
	itemIconWindow			= LoadGraph("Resource/Image/itemiconwindow.png");
	itemWindow				= LoadGraph("Resource/Image/itemwindow.png");
	shopWindow				= LoadGraph("Resource/Image/shopwindow.png");
	itemSelection			= LoadGraph("Resource/Image/itemselection.png");
	recipeWindow			= LoadGraph("Resource/Image/recipewindow.png");
	recipeSelection			= LoadGraph("Resource/Image/recipeselection.png");
	detailWindow			= LoadGraph("Resource/Image/detailwindow.png");
	moneyWindow				= LoadGraph("Resource/Image/moneywindow.png");
	salePriceWindow			= LoadGraph("Resource/Image/salepricewindow.png");
	selectItemWindow		= LoadGraph("Resource/Image/selectitemwindow.png");
	textWindow				= LoadGraph("Resource/Image/textwindow.png");
	textCursor				= LoadGraph("Resource/Image/textcursor.png");
	next					= LoadGraph("Resource/Image/next.png");
	nextCursor				= LoadGraph("Resource/Image/nextcursor.png");
	end						= LoadGraph("Resource/Image/end.png");
	buy						= LoadGraph("Resource/Image/buy.png");
	sale					= LoadGraph("Resource/Image/sale.png");
	mapIcon					= LoadGraph("Resource/Image/player.png");
	mapCursor				= LoadGraph("Resource/Image/cursor.png");

	// îwåi
	titleBack				= LoadGraph("Resource/Image/title.jpg");
	titleLogo				= LoadGraph("Resource/Image/titlelogo.png");
	mainmenuBack			= LoadGraph("Resource/Image/mainmenu.jpg");
	buyBack					= LoadGraph("Resource/Image/buy.jpg");
	productionBack			= LoadGraph("Resource/Image/production.jpg");

	skyBack				= LoadGraph("Resource/Image/skyback.jpg");

	// ÉAÉCÉeÉÄÉAÉCÉRÉì
	itemIcons.resize(GetGraphSize("Resource/Image/itemicons.png", 64, 64));
	LoadDivGraph("Resource/Image/itemicons.png", 28, 7, 4, 64, 64, &itemIcons[0]);
	weaponIcons.resize(GetGraphSize("Resource/Image/weaponicons.png", 64, 64));
	LoadDivGraph("Resource/Image/weaponicons.png", 28, 7, 4, 64, 64, &weaponIcons[0]);

	// 3DÉÇÉfÉã
	Player			= MV1LoadModel("Resource/Image/Model/curen.mv1");
	fieldItem		= MV1LoadModel("Resource/Image/Model/fielditem.mv1");
	Spruce_1		= MV1LoadModel("Resource/Image/Model/obj/spruce_01.mv1");
	Terrain_Block_1 = MV1LoadModel("Resource/Image/Model/terrain_block_1.mv1");

	// UIä÷åW
	assert(arrow != -1);
	assert(pressStartButton != -1);
	assert(menuCursor != -1);
	assert(dayWindow != -1);
	assert(itemIconWindow != -1);
	assert(itemWindow != -1);
	assert(shopWindow != -1);
	assert(itemSelection != -1);
	assert(recipeWindow != -1);
	assert(recipeSelection != -1);
	assert(detailWindow != -1);
	assert(moneyWindow != -1);
	assert(salePriceWindow != -1);
	assert(selectItemWindow != -1);
	assert(textWindow != -1);
	assert(textCursor != -1);
	assert(next != -1);
	assert(nextCursor != -1);
	assert(end != -1);
	assert(buy != -1);
	assert(sale != -1);
	assert(mapIcon != -1);
	assert(mapCursor != -1);

	// îwåi
	assert(titleBack != -1);
	assert(titleLogo != -1);
	assert(mainmenuBack != -1);
	assert(buyBack != -1);
	assert(productionBack != -1);
}
