#include "Image.h"

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

void Image::Final()
{
	InitGraph();
	MV1InitModel();
}

void Image::Load(std::string SceneName)
{
	if (SceneName == "Title")
	{
		titleBack        = LoadGraph("Resource/Image/title.jpg");
		titleLogo        = LoadGraph("Resource/Image/titlelogo.png");
		pressStartButton = LoadGraph("Resource/Image/pressstartbutton.png");
	}
	else if (SceneName == "MainMenu")
	{
		mainmenuBack = LoadGraph("Resource/Image/mainmenu.jpg");
		menuCursor   = LoadGraph("Resource/Image/menucursor.png");
	}
	else if (SceneName == "Adv")
	{
		textWindow = LoadGraph("Resource/Image/textwindow.png");
		textCursor = LoadGraph("Resource/Image/textcursor.png");
	}
	else if (SceneName == "StageSelection")
	{
		dayNum.resize(GetGraphSize("Resource/Image/daynum.png", 255, 141));
		LoadDivGraph("Resource/Image/daynum.png", 15, 15, 1, 255, 141, &dayNum[0]);

		dayWindow = LoadGraph("Resource/Image/daywindow.png");
		worldMap  = LoadGraph("Resource/Image/worldmap.jpg");
		mapIcon_1 = LoadGraph("Resource/Image/mapicon_1.png");
		mapIcon_2 = LoadGraph("Resource/Image/mapicon_2.png");
		mapIcon_3 = LoadGraph("Resource/Image/mapicon_3.png");
		mapIcon_4 = LoadGraph("Resource/Image/mapicon_4.png");
		mapIcon_5 = LoadGraph("Resource/Image/mapicon_5.png");

		Player    = MV1LoadModel("Resource/Image/Model/curen.mv1");
	}
	else if (SceneName == "Collection")
	{
		itemIcons.resize(GetGraphSize("Resource/Image/itemicons.png", 64, 64));
		LoadDivGraph("Resource/Image/itemicons.png", 28, 7, 4, 64, 64, &itemIcons[0]);

		skyBack         = LoadGraph("Resource/Image/skyback.jpg");
		rockBack        = LoadGraph("Resource/Image/rockback.jpg");
		volcanoBack     = LoadGraph("Resource/Image/volcanoback.jpg");

		itemIconWindow  = LoadGraph("Resource/Image/itemiconwindow.png");
		itemWindow      = LoadGraph("Resource/Image/itemwindow.png");
		itemSelection   = LoadGraph("Resource/Image/itemselection.png");
		collectionStart = LoadGraph("Resource/Image/collectionstart.png");
		collectionEnd   = LoadGraph("Resource/Image/collectionend.png");
		detailWindow    = LoadGraph("Resource/Image/detailwindow.png");
		watchBase       = LoadGraph("Resource/Image/watchbase.png");
		watchPointer    = LoadGraph("Resource/Image/watchpointer.png");

		// 3Dモデル
		Player          = MV1LoadModel("Resource/Image/Model/curen.mv1");
		fieldItem       = MV1LoadModel("Resource/Image/Model/fielditem.mv1");

		Terrain_Block_1 = MV1LoadModel("Resource/Image/Model/terrain_block_1.mv1");
		Terrain_Block_2 = MV1LoadModel("Resource/Image/Model/terrain_block_2.mv1");
		Terrain_Block_3 = MV1LoadModel("Resource/Image/Model/terrain_block_3.mv1");
		Terrain_Block_4 = MV1LoadModel("Resource/Image/Model/terrain_block_4.mv1");

		Branch_1        = MV1LoadModel("Resource/Image/Model/obj/branch_1.mv1");
		Branch_2        = MV1LoadModel("Resource/Image/Model/obj/branch_2.mv1");
		Branch_3        = MV1LoadModel("Resource/Image/Model/obj/branch_3.mv1");
		Branch_4        = MV1LoadModel("Resource/Image/Model/obj/branch_4.mv1");
		Branch_group    = MV1LoadModel("Resource/Image/Model/obj/branch_group_1.mv1");
		Bush_1          = MV1LoadModel("Resource/Image/Model/obj/bush_1.mv1");
		Bush_2          = MV1LoadModel("Resource/Image/Model/obj/bush_2.mv1");
		Bush_3          = MV1LoadModel("Resource/Image/Model/obj/bush_3.mv1");
		Bush_4          = MV1LoadModel("Resource/Image/Model/obj/bush_4.mv1");
		Bush_large_1    = MV1LoadModel("Resource/Image/Model/obj/bush_large_1.mv1");
		Bush_large_2    = MV1LoadModel("Resource/Image/Model/obj/bush_large_2.mv1");
		Cliff_rock_1    = MV1LoadModel("Resource/Image/Model/obj/cliff_rock_1.mv1");
		Cliff_rock_2    = MV1LoadModel("Resource/Image/Model/obj/cliff_rock_2.mv1");
		Cliff_rock_3    = MV1LoadModel("Resource/Image/Model/obj/cliff_rock_3.mv1");
		Cliff_rock_4    = MV1LoadModel("Resource/Image/Model/obj/cliff_rock_4.mv1");
		Cliff_rock_5    = MV1LoadModel("Resource/Image/Model/obj/cliff_rock_5.mv1");
		Crystal_1       = MV1LoadModel("Resource/Image/Model/obj/crystal_node_1.mv1");
		Crystal_2       = MV1LoadModel("Resource/Image/Model/obj/crystal_node_2.mv1");
		Crystal_3       = MV1LoadModel("Resource/Image/Model/obj/crystal_node_3.mv1");
		Crystal_4       = MV1LoadModel("Resource/Image/Model/obj/crystal_node_4.mv1");
		Crystal_5       = MV1LoadModel("Resource/Image/Model/obj/crystal_node_5.mv1");
		Rock_1          = MV1LoadModel("Resource/Image/Model/obj/rock_1.mv1");
		Rock_2          = MV1LoadModel("Resource/Image/Model/obj/rock_2.mv1");
		Rock_3          = MV1LoadModel("Resource/Image/Model/obj/rock_3.mv1");
		Rock_4          = MV1LoadModel("Resource/Image/Model/obj/rock_4.mv1");
		Rock_5          = MV1LoadModel("Resource/Image/Model/obj/rock_5.mv1");
		Spruce_1        = MV1LoadModel("Resource/Image/Model/obj/spruce_01.mv1");
		Spruce_2        = MV1LoadModel("Resource/Image/Model/obj/spruce_03.mv1");
		Spruce_3        = MV1LoadModel("Resource/Image/Model/obj/spruce_05.mv1");
		Trunk           = MV1LoadModel("Resource/Image/Model/obj/spruce_trunk_fallen.mv1");
	}
	else if (SceneName == "Buy")
	{
		itemIcons.resize(GetGraphSize("Resource/Image/itemicons.png", 64, 64));
		LoadDivGraph("Resource/Image/itemicons.png", 28, 7, 4, 64, 64, &itemIcons[0]);

		buyBack         = LoadGraph("Resource/Image/buy.jpg");
		moneyWindow     = LoadGraph("Resource/Image/moneywindow.png");
		salePriceWindow = LoadGraph("Resource/Image/salepricewindow.png");
		itemWindow      = LoadGraph("Resource/Image/itemwindow.png");
		shopWindow      = LoadGraph("Resource/Image/shopwindow.png");
		arrow           = LoadGraph("Resource/Image/arrow.png");
		buy             = LoadGraph("Resource/Image/buy.png");
		nextCursor      = LoadGraph("Resource/Image/nextcursor.png");
		itemSelection   = LoadGraph("Resource/Image/itemselection.png");
		detailWindow    = LoadGraph("Resource/Image/detailwindow.png");
	}
	else if (SceneName == "Production")
	{
		itemIcons.resize(GetGraphSize("Resource/Image/itemicons.png", 64, 64));
		LoadDivGraph("Resource/Image/itemicons.png", 28, 7, 4, 64, 64, &itemIcons[0]);
		weaponIcons.resize(GetGraphSize("Resource/Image/weaponicons.png", 64, 64));
		LoadDivGraph("Resource/Image/weaponicons.png", 28, 7, 4, 64, 64, &weaponIcons[0]);

		productionBack   = LoadGraph("Resource/Image/production.jpg");
		itemWindow       = LoadGraph("Resource/Image/itemwindow.png");
		selectItemWindow = LoadGraph("Resource/Image/selectitemwindow.png");
		next             = LoadGraph("Resource/Image/next.png");
		nextCursor       = LoadGraph("Resource/Image/nextcursor.png");
		itemSelection    = LoadGraph("Resource/Image/itemselection.png");
		detailWindow     = LoadGraph("Resource/Image/detailwindow.png");
		end              = LoadGraph("Resource/Image/end.png");
		recipeWindow     = LoadGraph("Resource/Image/recipewindow.png");
		recipeSelection  = LoadGraph("Resource/Image/recipeselection.png");
		productionArrow  = LoadGraph("Resource/Image/productionArrow.png");
	}
	else if (SceneName == "Sale")
	{
		weaponIcons.resize(GetGraphSize("Resource/Image/weaponicons.png", 64, 64));
		LoadDivGraph("Resource/Image/weaponicons.png", 28, 7, 4, 64, 64, &weaponIcons[0]);

		detailWindow  = LoadGraph("Resource/Image/detailwindow.png");
		moneyWindow   = LoadGraph("Resource/Image/moneywindow.png");
		itemWindow    = LoadGraph("Resource/Image/itemwindow.png");
		sale          = LoadGraph("Resource/Image/sale.png");
		nextCursor    = LoadGraph("Resource/Image/nextcursor.png");
		itemSelection = LoadGraph("Resource/Image/itemselection.png");
		saleBack      = LoadGraph("Resource/Image/saleback.jpg");
	}
	else if (SceneName == "Report")
	{
		reportBack = LoadGraph("Resource/Image/reportback.jpg");
	}
	else if (SceneName == "GameClear")
	{
		scores.resize(GetGraphSize("Resource/Image/scores.png", 200, 200));
		LoadDivGraph("Resource/Image/scores.png", 8, 8, 1, 200, 200, &scores[0]);
		weaponIcons.resize(GetGraphSize("Resource/Image/weaponicons.png", 64, 64));
		LoadDivGraph("Resource/Image/weaponicons.png", 28, 7, 4, 64, 64, &weaponIcons[0]);

		textWindow     = LoadGraph("Resource/Image/textwindow.png");
		textCursor     = LoadGraph("Resource/Image/textcursor.png");
		reportBack     = LoadGraph("Resource/Image/reportback.jpg");
		itemIconWindow = LoadGraph("Resource/Image/itemiconwindow.png");
		rank           = LoadGraph("Resource/Image/rank.png");
	}
	else if (SceneName == "GameOver")
	{
		textWindow = LoadGraph("Resource/Image/textwindow.png");
		textCursor = LoadGraph("Resource/Image/textcursor.png");
		reportBack = LoadGraph("Resource/Image/reportback.jpg");
	}
	else if (SceneName == "EndCredit")
	{
		endCredit = LoadGraph("Resource/Image/endcredit.png");
    }
}
