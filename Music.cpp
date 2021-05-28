#include "Music.h"
#include <DxLib.h>

int Music::op                { -1 };
int Music::ed                { -1 };
int Music::stageselection_BGM{ -1 };
int Music::stage1_BGM        { -1 };
int Music::stage2_BGM        { -1 };
int Music::stage3_BGM        { -1 };
int Music::stage4_BGM        { -1 };
int Music::stage5_BGM        { -1 };
int Music::buy_BGM           { -1 };
int Music::production_BGM    { -1 };
int Music::sale_BGM          { -1 };
int Music::report_BGM        { -1 };

int Music::enter_SE          { -1 };
int Music::cursormove_SE     { -1 };
int Music::error_SE          { -1 };
int Music::cancel_SE         { -1 };
int Music::collectionstart_SE{ -1 };
int Music::collect_SE        { -1 };
int Music::run_SE            { -1 };
int Music::menuopen_SE       { -1 };
int Music::money_SE          { -1 };
int Music::production_SE     { -1 };
int Music::productionend_SE  { -1 };
int Music::reportenter_SE    { -1 };

void Music::Load()
{
	op                 = LoadSoundMem("Resource/Music/OP.wav");
	ed                 = LoadSoundMem("Resource/Music/ED.wav");
	stageselection_BGM = LoadSoundMem("Resource/Music/StageSelection.wav");
	stage1_BGM         = LoadSoundMem("Resource/Music/stage1.wav");
	stage2_BGM         = LoadSoundMem("Resource/Music/stage2.wav");
	stage3_BGM         = LoadSoundMem("Resource/Music/stage3.wav");
	stage4_BGM         = LoadSoundMem("Resource/Music/stage4.wav");
	stage5_BGM         = LoadSoundMem("Resource/Music/stage5.wav");
	buy_BGM            = LoadSoundMem("Resource/Music/Buy.wav");
	production_BGM     = LoadSoundMem("Resource/Music/Production.wav");
	sale_BGM           = LoadSoundMem("Resource/Music/Sale.wav");
	report_BGM         = LoadSoundMem("Resource/Music/Report.wav");

	ChangeVolumeSoundMem(110, op);
	ChangeVolumeSoundMem(110, ed);
	ChangeVolumeSoundMem(110, stageselection_BGM);
	ChangeVolumeSoundMem(110, stage1_BGM);
	ChangeVolumeSoundMem(110, stage2_BGM);
	ChangeVolumeSoundMem(110, stage3_BGM);
	ChangeVolumeSoundMem(110, stage4_BGM);
	ChangeVolumeSoundMem(110, stage5_BGM);
	ChangeVolumeSoundMem(110, buy_BGM);
	ChangeVolumeSoundMem(110, production_BGM);
	ChangeVolumeSoundMem(110, sale_BGM);
	ChangeVolumeSoundMem(110, report_BGM);

	enter_SE           = LoadSoundMem("Resource/Music/Other_Enter_SE.wav");
	cursormove_SE      = LoadSoundMem("Resource/Music/Cursor_Move_SE.wav");
	error_SE           = LoadSoundMem("Resource/Music/Error_SE.wav");
	cancel_SE          = LoadSoundMem("Resource/Music/Cancel_SE.wav");
	collectionstart_SE = LoadSoundMem("Resource/Music/Collection_Start_SE.wav");
	collect_SE         = LoadSoundMem("Resource/Music/collect_SE.wav");
	run_SE             = LoadSoundMem("Resource/Music/Run_SE.wav");
	menuopen_SE        = LoadSoundMem("Resource/Music/MenuOpen.wav");
	money_SE           = LoadSoundMem("Resource/Music/Buy_Sale_Next_SE.wav");
	production_SE      = LoadSoundMem("Resource/Music/Production_SE.wav");
	productionend_SE   = LoadSoundMem("Resource/Music/Production_end_SE.wav");
	reportenter_SE     = LoadSoundMem("Resource/Music/Report_Enter_SE.wav");

	ChangeVolumeSoundMem(110, enter_SE);
	ChangeVolumeSoundMem(110, cursormove_SE);
	ChangeVolumeSoundMem(110, error_SE);
	ChangeVolumeSoundMem(110, cancel_SE);
	ChangeVolumeSoundMem(110, collectionstart_SE);
	ChangeVolumeSoundMem(150, collect_SE);
	ChangeVolumeSoundMem(150, run_SE);
	ChangeVolumeSoundMem(110, menuopen_SE);
	ChangeVolumeSoundMem(110, money_SE);
	ChangeVolumeSoundMem(110, production_SE);
	ChangeVolumeSoundMem(110, productionend_SE);
	ChangeVolumeSoundMem(110, reportenter_SE);
}
