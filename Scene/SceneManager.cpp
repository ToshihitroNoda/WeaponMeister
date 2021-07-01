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
	// �J�����ʒu�̏�����
	SetDrawScreen(GetActiveGraph());

	// ���݂̃V�[���̏I������
	if (currentScene != nullptr)
		currentScene->Final(); // �I���������Ăяo��

	if (sceneName == "Title")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Title>();
	}
	else if (sceneName == "MainMenu")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<MainMenu>();
	}
	else if (sceneName == "Adv")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Adv>();
	}

	else if (sceneName == "StageSelection")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<StageSelection>();
	}
	else if (sceneName == "Collection")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Collection>();
	}
	else if (sceneName == "Buy")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Buy>();
	}
	else if (sceneName == "Production")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Production>();
	}
	else if (sceneName == "Sale")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Sale>();
	}
	else if (sceneName == "Report")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<Report>();
	}
	else if (sceneName == "GameOver")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<GameOver>();
	}
	else if (sceneName == "GameClear")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<GameClear>();
	}
	else if (sceneName == "EndCredit")
	{
		// ���̃V�[���̐���
		currentScene = std::make_shared<EndCredit>();
	}

	// ���̃V�[���̏�����
	currentScene->Init(); // ���������Ăяo��
	prevScene = currentScene;
}