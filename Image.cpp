#include "Image.h"

int Image::ImageWidth				{ 0 };
int Image::ImageHeight				{ 0 };

// UI関係
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
int Image::collectionStart			{ -1 };

// 背景
int Image::titleBack				{ -1 };
int Image::titleLogo				{ -1 };
int Image::mainmenuBack				{ -1 };
int Image::buyBack					{ -1 };
int Image::productionBack			{ -1 };

int Image::skyBack					{ -1 };

// アイテムアイコン
std::vector<int> Image::itemIcons	{ NULL };
std::vector<int> Image::weaponIcons	{ NULL };

int Image::Player					{ -1 };
int Image::fieldItem				{ -1 };

int Image::Terrain_Block_1			{ -1 };
int Image::Terrain_Block_2			{ -1 };
int Image::Terrain_Block_3			{ -1 };
int Image::Terrain_Block_4			{ -1 };


int Image::Branch_1					{ -1 };
int Image::Branch_2					{ -1 };
int Image::Branch_3					{ -1 };
int Image::Branch_4					{ -1 };
int Image::Branch_group				{ -1 };
int Image::Bush_1					{ -1 };
int Image::Bush_2					{ -1 };
int Image::Bush_3					{ -1 };
int Image::Bush_4					{ -1 };
int Image::Bush_large_1				{ -1 };
int Image::Bush_large_2				{ -1 };
int Image::Cliff_rock_1				{ -1 };
int Image::Cliff_rock_2				{ -1 };
int Image::Cliff_rock_3				{ -1 };
int Image::Cliff_rock_4				{ -1 };
int Image::Cliff_rock_5				{ -1 };
int Image::Crystal_1				{ -1 };
int Image::Crystal_2				{ -1 };
int Image::Crystal_3				{ -1 };
int Image::Crystal_4				{ -1 };
int Image::Crystal_5				{ -1 };
int Image::Rock_1					{ -1 };
int Image::Rock_2					{ -1 };
int Image::Rock_3					{ -1 };
int Image::Rock_4					{ -1 };
int Image::Rock_5					{ -1 };
int Image::Spruce_1					{ -1 };
int Image::Spruce_2					{ -1 };
int Image::Spruce_3					{ -1 };
int Image::Trunk					{ -1 };

int Image::GetGraphSize(std::string ImageHandle, int CellSizeX, int CellSizeY)
{
	int imageHandle = LoadGraph(ImageHandle.c_str()); // 画像読み込み
	DxLib::GetGraphSize(imageHandle, &ImageWidth, &ImageHeight); // サイズ取得
	return (ImageWidth / CellSizeX) * (ImageHeight / CellSizeY); // 総数を返却
}

void Image::LoadDivGraph(std::string fileName, int allNum, int xNum, int yNum, int xSize, int ySize, int* hundleArray)
{
	DxLib::LoadDivGraph(fileName.c_str(), allNum, xNum, yNum, xSize, ySize, hundleArray);
}

void Image::Load()
{
	// UI関係
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
	collectionStart		    = LoadGraph("Resource/Image/collectionstart.png");

	// 背景
	titleBack				= LoadGraph("Resource/Image/title.jpg");
	titleLogo				= LoadGraph("Resource/Image/titlelogo.png");
	mainmenuBack			= LoadGraph("Resource/Image/mainmenu.jpg");
	buyBack					= LoadGraph("Resource/Image/buy.jpg");
	productionBack			= LoadGraph("Resource/Image/production.jpg");

	skyBack				= LoadGraph("Resource/Image/skyback.jpg");

	// アイテムアイコン
	itemIcons.resize(GetGraphSize("Resource/Image/itemicons.png", 64, 64));
	LoadDivGraph("Resource/Image/itemicons.png", 28, 7, 4, 64, 64, &itemIcons[0]);
	weaponIcons.resize(GetGraphSize("Resource/Image/weaponicons.png", 64, 64));
	LoadDivGraph("Resource/Image/weaponicons.png", 28, 7, 4, 64, 64, &weaponIcons[0]);

	// 3Dモデル
	Player			= MV1LoadModel("Resource/Image/Model/curen.mv1");
	fieldItem		= MV1LoadModel("Resource/Image/Model/fielditem.mv1");

	Terrain_Block_1 = MV1LoadModel("Resource/Image/Model/terrain_block_1.mv1");
	Terrain_Block_2 = MV1LoadModel("Resource/Image/Model/terrain_block_2.mv1");
	Terrain_Block_3 = MV1LoadModel("Resource/Image/Model/terrain_block_3.mv1");
	Terrain_Block_4 = MV1LoadModel("Resource/Image/Model/terrain_block_4.mv1");

	Branch_1		= MV1LoadModel("Resource/Image/Model/obj/branch_1.mv1");
	Branch_2		= MV1LoadModel("Resource/Image/Model/obj/branch_2.mv1");
	Branch_3		= MV1LoadModel("Resource/Image/Model/obj/branch_3.mv1");
	Branch_4		= MV1LoadModel("Resource/Image/Model/obj/branch_4.mv1");
	Branch_group	= MV1LoadModel("Resource/Image/Model/obj/branch_group_1.mv1");
	Bush_1			= MV1LoadModel("Resource/Image/Model/obj/bush_1.mv1");
	Bush_2			= MV1LoadModel("Resource/Image/Model/obj/bush_2.mv1");
	Bush_3			= MV1LoadModel("Resource/Image/Model/obj/bush_3.mv1");
	Bush_4			= MV1LoadModel("Resource/Image/Model/obj/bush_4.mv1");
	Bush_large_1	= MV1LoadModel("Resource/Image/Model/obj/bush_large_1.mv1");
	Bush_large_2	= MV1LoadModel("Resource/Image/Model/obj/bush_large_2.mv1");
	Cliff_rock_1	= MV1LoadModel("Resource/Image/Model/obj/cliff_rock_1.mv1");
	Cliff_rock_2	= MV1LoadModel("Resource/Image/Model/obj/cliff_rock_2.mv1");
	Cliff_rock_3	= MV1LoadModel("Resource/Image/Model/obj/cliff_rock_3.mv1");
	Cliff_rock_4	= MV1LoadModel("Resource/Image/Model/obj/cliff_rock_4.mv1");
	Cliff_rock_5	= MV1LoadModel("Resource/Image/Model/obj/cliff_rock_5.mv1");
	Crystal_1		= MV1LoadModel("Resource/Image/Model/obj/crystal_node_1.mv1");
	Crystal_2		= MV1LoadModel("Resource/Image/Model/obj/crystal_node_2.mv1");
	Crystal_3		= MV1LoadModel("Resource/Image/Model/obj/crystal_node_3.mv1");
	Crystal_4		= MV1LoadModel("Resource/Image/Model/obj/crystal_node_4.mv1");
	Crystal_5		= MV1LoadModel("Resource/Image/Model/obj/crystal_node_5.mv1");
	Rock_1			= MV1LoadModel("Resource/Image/Model/obj/rock_1.mv1");
	Rock_2			= MV1LoadModel("Resource/Image/Model/obj/rock_2.mv1");
	Rock_3			= MV1LoadModel("Resource/Image/Model/obj/rock_3.mv1");
	Rock_4			= MV1LoadModel("Resource/Image/Model/obj/rock_4.mv1");
	Rock_5			= MV1LoadModel("Resource/Image/Model/obj/rock_5.mv1");
	Spruce_1		= MV1LoadModel("Resource/Image/Model/obj/spruce_01.mv1");
	Spruce_2		= MV1LoadModel("Resource/Image/Model/obj/spruce_03.mv1");
	Spruce_3		= MV1LoadModel("Resource/Image/Model/obj/spruce_05.mv1");
	Trunk			= MV1LoadModel("Resource/Image/Model/obj/spruce_trunk_fallen.mv1");
}
