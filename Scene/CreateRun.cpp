#include "CreateRun.h"
#include "Input.h"
#include "Music.h"
#include "Screen.h"
#include "MyMath.h"
#include <vector>
#include <algorithm>

void CreateRun::Update()
{
	if (MainSlectOk_)
	{
		// vector内容クリア前に品質を計算して保管しておく。
		// 一時的に保管してたgm.handlesとgm.mainの内容をクリアする。
		// gm.pouchとgm.lumberから持ち手リストに入ってるもの、
		// gm.pouchとgm.メイン部分のリストからメイン部分リストに入ってるものを消し、
		// waponIDの武器を一つ生成
		// gm.waponQualityに品質を代入

		int weaponQualityStorage = 0; // 品質保存用変数

		for (int i = 0; i < gm.handles.size(); i++)
		{
			weaponQualityStorage += (gm.handlesQuality[i] / ((i + 1) * 2)); // 全素材の品質を計算(持ち手部分)
		}
		for (int i = 0; i < gm.main.size(); i++)
		{
			weaponQualityStorage += (gm.mainQuality[i] / ((i + 1) * 2));	// 全素材の品質を計算(上で計算した持ち手部分 + メイン部分)
		}

		if (!animationEnd_ && !MakeEnd)
		{
			for (int i = 0; i < gm.handles.size(); i++)
				drawItemID_.push_back(gm.handles[i]);
			for (int i = 0; i < gm.main.size(); i++)
				drawItemID_.push_back(gm.main[i]);

			animationX_.resize(drawItemID_.size());
			animationY_.resize(drawItemID_.size());

			MakeEnd = true;
		}

		if (drawCounter_ > 0)
		{
			if (Input::GetKey(KEY_INPUT_SPACE))
				productAnimationSpeed_ = 3;
			else
				productAnimationSpeed_ = 1;

			if (animationSoundTimer_ >= animationSoundTime_)
			{
				PlaySoundMem(Music::production_SE, DX_PLAYTYPE_BACK);
				animationSoundTimer_ = 0;
			}
			for (int i = 0; i < drawItemID_.size(); i++)
			{
				animationX_[i] = (Screen::width / 2) + cos((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;
				animationY_[i] = (Screen::height / 2) + sin((std::abs(angle_) / drawItemID_.size()) * (i + 1) * MyMath::Deg2Rad) * distToCenter_;

				angle_ += 10;
			}
		}
		else
		{
			if (!playProductionEndSound_)
			{
				PlaySoundMem(Music::productionend_SE, DX_PLAYTYPE_BACK);
				playProductionEndSound_ = true;
			}
			if (Input::GetButtonDown(PAD_INPUT_1))
			{
				MakeEnd = false;
				animationEnd_ = false;
				playProductionEndSound_ = false;
				distToCenter_ = defaultDrawCount_;
				drawCounter_ = defaultDrawCount_;
				angle_ = defaultAngle_;
				productAnimationSpeed_ = 1;
				animationX_.clear();
				animationY_.clear();
				drawItemID_.clear();
			}
		}

		if (!MakeEnd)
		{
			/*----- 選択済み素材削除処理 -----*/

			/*　選択済みのアイテムのポーチにおける位置が入ってるvectorを　*/
			/*　　　　降順にソートしてgm.pouchの後ろから順にerase　 　　　*/

			std::sort(SelectItemPosOnThePouch_.begin(), SelectItemPosOnThePouch_.end(), std::greater<int>());
			for (int i = 0; i < SelectItemPosOnThePouch_.size(); i++)
			{
				gm.pouch.erase(gm.pouch.begin() + SelectItemPosOnThePouch_[i]);
				gm.pouchQuality.erase(gm.pouchQuality.begin() + SelectItemPosOnThePouch_[i]);

			}
			/*---------------*/

			gm.handles.clear();
			gm.handlesQuality.clear();
			gm.main.clear();
			gm.mainQuality.clear();

			gm.weapons.push_back(weaponID_);
			gm.weaponQuality.push_back(weaponQualityStorage);
		}
	}
	else
		shouldRetry_ = true;
	if (!MakeEnd)
	{// 初期化
		doAllFormat_ = true;
	}
}

void CreateRun::Draw()
{
	if (drawCounter_ > 0)
	{
		for (int i = 0; i < drawItemID_.size(); i++)
			DrawGraph(animationX_[i], animationY_[i], gm.image.itemIcons[drawItemID_[i]], TRUE);

		distToCenter_ -= productAnimationSpeed_;
		drawCounter_ -= productAnimationSpeed_;
		animationSoundTimer_++;
	}
	else
	{
		DrawGraph(Screen::width / 2, Screen::height / 2, gm.image.weaponIcons[weaponID_], TRUE);
		std::string drawMassege = "Zキーで次へ";
		int DrawWidth = GetDrawStringWidth(drawMassege.c_str(), -1);
		DrawString((Screen::width - DrawWidth) / 2, (Screen::height - (Screen::height / 4)), drawMassege.c_str(), gm.colorWhite);
	}
	
	SetFontSize(15);
	DrawString(MakeOptionMenuX_, OptionMenuY_, "SPACE : 早送り", gm.colorWhite);
	SetFontSize(gm.DefaultFontSize_);
}
