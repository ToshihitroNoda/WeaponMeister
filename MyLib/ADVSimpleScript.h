#ifndef ADVSIMPLESCRIPT_H_
#define ADVSIMPLESCRIPT_H_

#include <DxLib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

class ADVSimpleScript
{
public:
	ADVSimpleScript()  = default;
	~ADVSimpleScript() = default;

	static void Init();
	static void Final();
	static void Load(std::string filePath);
	static void Update();
	static void ImageDraw();
	static void MessageDraw(int MassegeColor, int FontSize = 30, int DefaultFontSize = 20);

	static int MessageCount;
	static std::vector<std::string> messageList;

	static bool LoadEnd_;

private:
	static int lineWidth_;
	static std::string filePath_;

	static std::vector<int> ResourceNums_;
	static std::vector<int> CX_;
	static std::vector<int> CY_;
	static std::vector<int> CDrawID_;
	static std::vector<std::string> ResourcePath_;
	static std::vector<std::string> ResourceType_;
	static std::vector<std::string> Commands_;
	static int ResourceNum_;
	static int MessageX_;
	static int MessageY_;
	static int StringX_;
	static int StringY_;
	static int BGX_;
	static int BGY_;
	static int BGID_;
	static int CDrawCount_;
	static int BreakCount_;
	static int PrevPlayMusic;
	static std::string CName_;
	static bool NowBreak_;
	static bool DrawSkip_;
	static bool is_message_text_;
};

#endif