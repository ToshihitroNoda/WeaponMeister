#include "SceneManager.h"
#include "Scene.h"

#include "Title.h"
#include "MainMenu.h"

#include "Adv.h"
#include "StageSelection.h"
#include "Collection.h"
#include "Buy.h"
#include "Production.h"
#include "Sale.h"
#include "Report.h"
#include "GameOver.h"
#include "GameClear.h"
#include "EndCredit.h"

void SceneManager::LoadScene(std::string sceneName, std::vector<std::string> options)
{
	// カメラ位置の初期化
	SetDrawScreen(GetActiveGraph());

	// 現在のシーンの終了処理
	if (currentScene != nullptr)
		currentScene->Final(); // 終了処理を呼び出す

	if (sceneName == "Title")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Title>();
	}
	else if (sceneName == "MainMenu")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<MainMenu>();
	}
	else if (sceneName == "Adv")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Adv>();
	}

	else if (sceneName == "StageSelection")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<StageSelection>();
	}
	else if (sceneName == "Collection")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Collection>();
	}
	else if (sceneName == "Buy")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Buy>();
	}
	else if (sceneName == "Production")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Production>();
	}
	else if (sceneName == "Sale")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Sale>();
	}
	else if (sceneName == "Report")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<Report>();
	}
	else if (sceneName == "GameOver")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<GameOver>();
	}
	else if (sceneName == "GameClear")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<GameClear>();
	}
	else if (sceneName == "EndCredit")
	{
		// 前のシーンを削除
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// 次のシーンの生成
		currentScene = std::make_shared<EndCredit>();
	}

	// 次のシーンの初期化
	currentScene->Init(); // 初期化を呼び出す
	prevScene = currentScene;
}