#include "ProductionSectionBase.h"

bool ProductionSectionBase::canWoodSword_ = true;
bool ProductionSectionBase::canJawaSword_ = true;
bool ProductionSectionBase::canEnriSword_ = false;
bool ProductionSectionBase::canKeinSword_ = false;
bool ProductionSectionBase::canShizukuSword_ = false;
bool ProductionSectionBase::canSaintSword_ = false;
bool ProductionSectionBase::canGodWoodSword_ = false;

bool ProductionSectionBase::canStoneSword_ = true;
bool ProductionSectionBase::canIronOreSword_ = true;
bool ProductionSectionBase::canJadeSword_ = false;
bool ProductionSectionBase::canDiamondSword_ = false;
bool ProductionSectionBase::canCarbonadeSword_ = false;
bool ProductionSectionBase::canOrichalcumSword_ = false;
bool ProductionSectionBase::canGodStoneSword_ = false;

int ProductionSectionBase::cursorX_ = 0;
int ProductionSectionBase::cursorY_ = 0;
int ProductionSectionBase::prevCursorY_ = 0;

int ProductionSectionBase::selectIconNum_ = 0;
int ProductionSectionBase::scrollCount_ = 0;
int ProductionSectionBase::weaponID_ = 0;
int ProductionSectionBase::ItemType_ = 0;

bool ProductionSectionBase::weaponMakeAssert_ = false;
bool ProductionSectionBase::itemDetail_ = false;
bool ProductionSectionBase::cursorInit_ = true;
bool ProductionSectionBase::shouldWeaponMainCreate_ = false;
bool ProductionSectionBase::MainSlectOk_ = false;
bool ProductionSectionBase::doAllFormat_ = false;
bool ProductionSectionBase::shouldRetry_ = false;
bool ProductionSectionBase::HandleSlectOk_ = false;
bool ProductionSectionBase::shouldCreate_ = false;

std::vector<int> ProductionSectionBase::itemForWeaponMake_;
std::vector<int> ProductionSectionBase::itemQualityForWeaponMake_;
std::vector<int> ProductionSectionBase::ItemPosOnThePouch_;
std::vector<int> ProductionSectionBase::SelectItemPosOnThePouch_;
std::vector<int> ProductionSectionBase::PouchDrawErea_;
std::vector<int> ProductionSectionBase::NowDrawPosOnPouch_;

std::vector<bool> ProductionSectionBase::canWeaponMake_
{ canWoodSword_     , canJawaSword_      , canEnriSword_    , canKeinSword_,
  canShizukuSword_  , canSaintSword_     , canGodWoodSword_ ,
  canStoneSword_    , canIronOreSword_   , canJadeSword_    , canDiamondSword_,
  canCarbonadeSword_, canOrichalcumSword_, canGodStoneSword_ };

void ProductionSectionBase::GetHandleForWeaponMake()
{
	PouchDrawErea_.clear();
	NowDrawPosOnPouch_.clear();

	for (int i = 0; i < gm.pouch.size(); i++)
	{
		if ((int)gm.itemData[CsvTypeCheckFine_][gm.pouch[i] + CsvSkipCell_] == lumberNum_)
		{
			itemForWeaponMake_.push_back(gm.pouch[i]);
			itemQualityForWeaponMake_.push_back(gm.pouchQuality[i]);
			ItemPosOnThePouch_.push_back(i);
			if (PouchDrawErea_.size() < DrawMaxPouchSize_)
				PouchDrawErea_.push_back(gm.pouch[i]);
			if (NowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
				NowDrawPosOnPouch_.push_back(i);
		}
	}
}

void ProductionSectionBase::GetMainForWeaponMake(int ItemType)
{
	PouchDrawErea_.clear();
	NowDrawPosOnPouch_.clear();

	for (int i = 0; i < gm.pouch.size(); i++)
	{
		if ((int)gm.itemData[CsvTypeCheck_][gm.pouch[i] + CsvSkipCell_] == ItemType)
		{
			itemForWeaponMake_.push_back(gm.pouch[i]);
			itemQualityForWeaponMake_.push_back(gm.pouchQuality[i]);
			ItemPosOnThePouch_.push_back(i);
			if (PouchDrawErea_.size() < DrawMaxPouchSize_)
				PouchDrawErea_.push_back(gm.pouch[i]);
			if (NowDrawPosOnPouch_.size() < DrawMaxPouchSize_)
				NowDrawPosOnPouch_.push_back(i);
		}
	}
}

bool ProductionSectionBase::AlreadySecectItem(int ItemPosOnPouch)
{
	for (int i = 0; i < (unsigned)SelectItemPosOnThePouch_.size(); i++)
	{
		if (ItemPosOnPouch == SelectItemPosOnThePouch_[i])
			return true;
	}
	return false;
}
