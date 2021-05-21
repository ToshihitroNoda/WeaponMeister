#include "Collection.h"

#include "GameObject.h"
#include "Player.h"
#include "Map.h"
#include "Camera.h"
#include "DataCsv.h"
#include "FieldItem.h"
#include "MyRandom.h"
#include "Input.h"
#include "Screen.h"

void Collection::Init()
{
	gm.image.Load(tag);
	gm.mapData.Load("Resource/Datas/MapData.csv");
	gm.itemData.Load("Resource/Datas/ItemData.csv");

	SetUseZBuffer3D(TRUE);
	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	gm.map	  = std::make_shared<Map>(0, "Map3"/* + std::to_string(StageSelection::stageNum)*/);
	gm.player = std::make_shared<Player>
				(gm.mapData[3][StageSelection::stageNum - 1 + CsvSkipCell_],
				 gm.mapData[4][StageSelection::stageNum - 1 + CsvSkipCell_],
				 gm.mapData[5][StageSelection::stageNum - 1 + CsvSkipCell_]);

	gm.player->Init();

	gm.map->LoadTerrain(); // マップの描画
	gm.map->LoadObjects(); // オブジェクトの描画

	// アイテム配列の行数を取得
	int n1	  = gm.itemData[0].size();

	// 行数分for文回してItemDataファイルの2,3列目のmap番号と現在いるmapが等しいものだけ取り出す
	for (int i = 0; i < n1; i++)
	{
		if ((int)gm.itemData[CsvCanGetMap1_][i] == StageSelection::stageNum - 1||
			(int)gm.itemData[CsvCanGetMap2_][i] == StageSelection::stageNum - 1)
			possibilityToGetItem_.push_back(gm.itemData[CsvItemID_][i]); // アイテムIDを獲得できるアイテムリストに格納
	}
}

void Collection::Final()
{
	gm.mapObjects.clear();
	gm.mapObjects.shrink_to_fit();
	gm.fieldItems.clear();
	gm.fieldItems.shrink_to_fit();
	gm.mapTerrain.clear();
	gm.mapTerrain.shrink_to_fit();
	gm.map.reset();
	gm.player.reset();
	gm.image.Final();
	sm.currentScene.reset();
}

void Collection::Update()
{
	if (startCount_ < 0)
	{
		if (collectTimer_ > 0)
		{
			if (!menuInit)
				gm.player->Update(); // プレイヤの更新

			// フィールドアイテムの更新
			for (const auto& fI : gm.fieldItems)
			{
				fI->Update();
			}

			if (!menuInit)
			{
				// プレイヤーとフィールドアイテムとの当たり判定
				for (int i = 0; i < (signed)gm.fieldItems.size(); i++)
				{
					if (MyMath::RectRectIntersect(
						gm.player->GetLeft(), gm.player->GetBack(), gm.player->GetRight(), gm.player->GetForward(),
						gm.fieldItems[i]->GetLeft(), gm.fieldItems[i]->GetBack(), gm.fieldItems[i]->GetRight(), gm.fieldItems[i]->GetForward()
					))
					{
						gm.player->OnCollision(gm.fieldItems[i]);
						gm.fieldItems[i]->OnCollision(gm.player);
						ItemGet();
					}
				}
				// プレイヤーとマップオブジェクトの当たり判定
				for (int i = 0; i < (signed)gm.mapObjects.size(); i++)
				{
					if (MyMath::RectRectIntersect(
						gm.player->GetLeft(), gm.player->GetBack(), gm.player->GetRight(), gm.player->GetForward(),
						gm.mapObjects[i]->GetLeft(), gm.mapObjects[i]->GetBack(), gm.mapObjects[i]->GetRight(), gm.mapObjects[i]->GetForward()
					))
					{
						gm.player->OnCollision(gm.mapObjects[i]);
						gm.mapObjects[i]->OnCollision(gm.player);
					}
				}
			}
			if (getItemFlg_)
				getItemDrawCounter_++;

			if (getItemDrawCounter_ >= 120 || (getItemDrawCounter_ >= 5 && Input::GetButtonDown(PAD_INPUT_1)))
			{
				getItemFlg_ = false; // 手に入れたアイテム表示を消す
				getItemDrawCounter_ = 0;
				DrawGetItem_.clear();
			}

			gm.EraseRemoveIf(gm.fieldItems,
				[](std::shared_ptr<FieldItem>& ptr) { return ptr->isDead; });

			if (Input::GetButtonDown(PAD_INPUT_2))
			{
				if (menuOpen_)
				{
					menuOpen_ = false;
					menuInit = false;
					PouchDrawErea_.clear();
				}
				else // でばっぐ
				{
					clsDx();
					sm.LoadScene("Buy"); 
				}
			}

			if (!menuOpen_ && Input::GetButtonDown(PAD_INPUT_3))
			{
				menuOpen_ = true;
				int cursorX_ = CursorX_Min_ItemSelect_;
				int cursorY_ = CursorY_Min_ItemSelect_;
			}

			if (menuOpen_)
			{
				if (!menuInit)
				{
					for (int i = 0; i < DrawMaxPouchSize; i++)
					{
						if (gm.pouch.size() > i)
							PouchDrawErea_.push_back(gm.pouch[i]);
					}
					menuInit = true;
				}
				/*----- カーソル移動 -----*/

				if (Input::GetButtonDown(PAD_INPUT_RIGHT))
				{
					if (cursorX_ < CursorX_Max_ItemSelect_)
					{
						cursorX_ += CursorX_MoveVerticalWidth_ItemSelect_;
						selectIconNum_++; // 選択されてる箇所のアイテムの番号を取得
					}
				}
				if (Input::GetButtonDown(PAD_INPUT_LEFT))
				{
					if (cursorX_ > CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
					{
						cursorX_ -= CursorX_MoveVerticalWidth_ItemSelect_;
						selectIconNum_--;
					}
				}
				if (Input::GetButtonDown(PAD_INPUT_DOWN))
				{
					if (cursorY_ != CursorY_Max_ItemSelect_)
					{
						cursorY_ += CursorY_MoveVerticalWidth_ItemSelect_;
						selectIconNum_ += WaponID_ByLineBreak_ItemSelect_;
					}
					else
					{
						if (gm.pouch.size() > DrawMaxPouchSize)
						{
							if (PouchDrawErea_.size() > WindowX_CellSize_)
							{
								// 一行スクロール
								scrollCount_++;
								// 描画するアイテムのvectorの最初の一行を削除し、後ろに一行足す
								// まず先頭の一行の削除
								PouchDrawErea_.erase(PouchDrawErea_.begin(), PouchDrawErea_.begin() + WindowX_CellSize_);
								// 後ろに一行追加。
								/// iの初期値		: 表示できる最大数 + 追加する列数 - 列数
								/// for文の回る条件 : 表示できる最大数 + 追加する列数まで
								for (int i = DrawMaxPouchSize + (scrollCount_ * WindowX_CellSize_) - WindowX_CellSize_;
									i < DrawMaxPouchSize + (scrollCount_ * WindowX_CellSize_);
									i++)
								{
									if (i < gm.pouch.size())
									{
										PouchDrawErea_.push_back(gm.pouch[i]);
									}
								}
							}
						}
					}
				}
				if (Input::GetButtonDown(PAD_INPUT_UP))
				{
					if (cursorY_ != CursorY_Min_ItemSelect_)
					{
						cursorY_ -= CursorY_MoveVerticalWidth_ItemSelect_;
						selectIconNum_ -= WaponID_ByLineBreak_ItemSelect_;
					}
					else
					{
						if (scrollCount_ > 0)
						{
							scrollCount_--;
							if (PouchDrawErea_.size() == DrawMaxPouchSize)		// 描画されてるウィンドウが埋まってる場合
							{
								PouchDrawErea_.erase(PouchDrawErea_.end() - WindowX_CellSize_, PouchDrawErea_.end());
								// 描画するアイテムのvectorの最初に描画されてない一行分追加
								for (int i = WindowX_CellSize_; i > 0; i--)
									PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
							}
							else if (PouchDrawErea_.size() > DrawMaxPouchSize - WindowX_CellSize_ &&
								PouchDrawErea_.size() < DrawMaxPouchSize)	// 描画されてるウィンドウの最後の一行に空きがある場合
							{
								PouchDrawErea_.erase(PouchDrawErea_.end() - (PouchDrawErea_.size() % WindowX_CellSize_), PouchDrawErea_.end());
								// 描画するアイテムのvectorの最初に描画されてない一行分追加
								for (int i = WindowX_CellSize_; i > 0; i--)
									PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
							}
							else												// 描画されてるウィンドウの下何行かが空いている場合
							{
								// 描画するアイテムのvectorの最初に描画されてない一行分追加
								for (int i = WindowX_CellSize_; i > 0; i--)
									PouchDrawErea_.begin() = PouchDrawErea_.insert(PouchDrawErea_.begin(), gm.pouch[scrollCount_ * WindowX_CellSize_ + i - 1]);
							}
						}
					}
				}

				/*---------------*/
			}
			collectTimer_--;
			watchPointerAngle_ += plusPointerAngle_;
		}
		else
		{
			collectionEnd_ = true;
			if (endCount_ < 0)
			{
				if (Input::GetButtonDown(PAD_INPUT_1))
				{
					clsDx();
					sm.LoadScene("Buy");
				}
			}
			endCount_--;
		}
	}

	startCount_--;
}

void Collection::ItemGet()
{
	// 初期化
	getItemCount_   = 0;
	getItem_		= 0;
	qualityStorage_ = 0;

	// アイテム取得
	if (Input::GetButtonDown(PAD_INPUT_1))
	{
		if (gm.pouch.size() != MaxPouchSize_) // バッグがいっぱいじゃなかったら
		{
			getItemFlg_ = true; // 手に入れたアイテムを表示
			// もし手に入れられるアイテムが最大数分手に入った時バッグの容量を越えたら
			if ((signed)MaxPouchSize_ < gm.pouch.size() + getItemCountMax_)
			{
				getItemCountMax_--; // 最大値を減らす
				return; // もう一度チェック
			}

			// 手に入れられるアイテム数をランダムで決定
			getItemCount_ = MyRandom::RangeInt(1, getItemCountMax_); 

			for (int i = 0; i < getItemCount_; i++)
			{
				// マップに応じたランダム品質を保管
				// 手に入れられるアイテムをランダムで取得
				// 実際にアイテムを手に入れる
				
				// Draw用に手に入れたアイテムをvectorに格納
				// pouchにpush_buck
				// 品質用vectorに品質を代入

				qualityStorage_ = MyRandom::RangeInt(gm.mapData[1][StageSelection::stageNum + CsvSkipCell_], gm.mapData[2][StageSelection::stageNum - 1 + CsvSkipCell_]);
				int randItems = MyRandom::RangeInt(0, possibilityToGetItem_.size() - 1);
				getItem_ = possibilityToGetItem_[randItems];
				
				DrawGetItem_.push_back(getItem_); 
				gm.pouch.push_back(getItem_);
				gm.pouchQuality.push_back(qualityStorage_);
			}
		}
	}
}

void Collection::Draw()
{
	DrawGraph(gm.player->backX, 0, gm.image.skyBack, TRUE);
	DrawGraph(gm.player->backX - gm.player->BackImageWidth, 0, gm.image.skyBack, TRUE);

	// 地形
	for (auto& mT : gm.mapTerrain)
	{
		mT->Draw();
	}

	gm.player->Draw(); // プレイヤーの描画

	// フィールドアイテム
	for (const auto& fI : gm.fieldItems)
	{
		fI->Draw();
	}

	// オブジェクト
	for (const auto& mO : gm.mapObjects)
	{
		mO->Draw();
	}

	gm.player->DrawHitBox(); // 当たり判定の描画 
	
	DrawRotaGraph(WatchX_, WatchY_, 1.0f, 0.0f, gm.image.watchBase, TRUE);
	DrawRotaGraph(WatchX_, WatchY_, 1.0f, watchPointerAngle_ * MyMath::Deg2Rad, gm.image.watchPointer, TRUE);

	if (getItemFlg_)
	{
		for (int i = 0; i < getItemCount_; i++)
		{
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, gm.image.itemIconWindow, TRUE);
			DrawGraph(DrawGetItemX_ + i * DrawGetItemX_Width_, DrawGetItemY_, gm.image.itemIcons[DrawGetItem_[i]], TRUE);
		}
	}


	for (int i = 0; i < gm.fieldItems.size(); i++)
	{
		if (gm.fieldItems[i]->isOnCollisionPlayer)
			DrawString(Screen::width / 2, Screen::height / 2, "Zキーで採取", gm.colorWhite);
	}
	if (gm.pouch.size() == MaxPouchSize_)
		DrawString
		(DrawAssertPouchSizeOverFlow_X_,
		 DrawAssertPouchSizeOverFlow_Y_,
		 "ポーチがいっぱいです",
		 gm.colorWhite);

	if (menuOpen_)
	{
		DrawGraph(WindowX_, WindowY_, gm.image.itemWindow, TRUE);

		for (int y = 0; y < WindowY_CellSize_; y++)
		{
			for (int x = 0; x < WindowX_CellSize_; x++)
			{
				if ((signed)(x + (y * WindowX_CellSize_)) < PouchDrawErea_.size())
				{
					DrawGraph(itemX_ + x * WindowCellSize_X_, itemY_ + y * WindowCellSize_Y_, gm.image.itemIcons[PouchDrawErea_[x + (y * WindowX_CellSize_)]], TRUE);
				}
			}
		}

		if (cursorX_ >= CursorX_Min_ItemSelect_ && cursorX_ <= CursorX_Max_ItemSelect_)
			DrawGraph(cursorX_, cursorY_, gm.image.itemSelection, TRUE);

		if (PouchDrawErea_.size() > (signed)selectIconNum_)
		{
			DrawGraph(DetailWindowX_, DetailWindowY_, gm.image.detailWindow, TRUE);
			DrawString(ItemNameX_, ItemNameY_, gm.itemData[0][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
			std::stringstream ss;
			ss << gm.pouchQuality[selectIconNum_];
			DrawString(ItemQualityX_, ItemNameY_, ("品質 : " + ss.str()).c_str(), gm.colorWhite);								
			DrawString(ItemInfoX_, ItemInfoY_, gm.itemData[1][PouchDrawErea_[selectIconNum_] + CsvSkipCell_].stringData.c_str(), gm.colorWhite);
		}	

	}

	if (startCount_ >= 0)
		DrawGraph(0, 0, gm.image.collectionStart, TRUE);

	if (collectionEnd_)
		DrawGraph(0, 0, gm.image.collectionEnd, TRUE);
}