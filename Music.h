#ifndef MUSIC_H_
#define MUSIC_H_

#include <string>

class Music
{
public:
	Music()  = default;
	~Music() = default;

	static void Load();

	static int op;
	static int ed;
	static int stageselection_BGM;
	static int stage1_BGM;
	static int stage2_BGM;
	static int stage3_BGM;
	static int stage4_BGM;
	static int stage5_BGM;
	static int buy_BGM;
	static int production_BGM;
	static int sale_BGM;
	static int report_BGM;

	static int enter_SE;
	static int cursormove_SE;
	static int error_SE;
	static int cancel_SE;
	static int collectionstart_SE;
	static int collect_SE;
	static int run_SE;
	static int menuopen_SE;
	static int money_SE;
	static int production_SE;
	static int productionend_SE;
	static int reportenter_SE;
};

#endif