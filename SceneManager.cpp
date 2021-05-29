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
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Title>();
	}
	else if (sceneName == "MainMenu")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<MainMenu>();
	}
	else if (sceneName == "Adv")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Adv>();
	}

	else if (sceneName == "StageSelection")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<StageSelection>();
	}
	else if (sceneName == "Collection")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Collection>();
	}
	else if (sceneName == "Buy")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Buy>();
	}
	else if (sceneName == "Production")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Production>();
	}
	else if (sceneName == "Sale")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Sale>();
	}
	else if (sceneName == "Report")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<Report>();
	}
	else if (sceneName == "GameOver")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<GameOver>();
	}
	else if (sceneName == "GameClear")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<GameClear>();
	}
	else if (sceneName == "EndCredit")
	{
		// �O�̃V�[�����폜
		if (prevScene != nullptr)
		{
			prevScene.reset();
		}
		// ���̃V�[���̐���
		currentScene = std::make_shared<EndCredit>();
	}

	// ���̃V�[���̏�����
	currentScene->Init(); // ���������Ăяo��
	prevScene = currentScene;
}