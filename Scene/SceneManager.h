#ifndef SCNENEMANAGER_H_
#define SCNENEMANAGER_H_

#include <vector>
#include <memory>
#include <string>

#include "../MyLib/Singleton.h"

class Scene; //�N���X�錾������

class SceneManager : public Singleton<SceneManager>//��<�`>�Ƃ��Čp������ƗB��̃V���O���g���^�^�C�v�ƂȂ�
{
public:
    friend class Singleton<SceneManager>; // Singleton �ł̃C���X�^���X�쐬�͋���

    std::string selectStage = "stage1"; // �I�𒆂̃X�e�[�W(�^�C�g���ł̃f�t�H���g�I���Ȃǂ��}�l�[�W���ɕێ��ł���)

    // �}�l�[�W���́y�ǂ�����ł��A�N�Z�X���₷���u�ϐ��̌f���v�Ƃ��ċC�y�Ɏg���Ă��悢�z
    int scoreMax = -1; // �V�[�����܂����X�R�A�Ȃǂ̓}�l�[�W���ɒ�`����΃V�[���`�F���W��������Ȃ�

    std::shared_ptr<Scene> prevScene{ nullptr }; // ��O�̃V�[��
    std::shared_ptr<Scene> currentScene{ nullptr }; // ���݂̃V�[��
    // �V�[�����`�F���W���J�ڂ���(�O�̃V�[���̃��Z�b�g����������) options�̓X�e�[�Wcsv�Ȃǂ̎w��Ɏg����
    void LoadScene(std::string sceneName, std::vector<std::string> options = { "" });

protected:
    SceneManager() = default; // �O������̃C���X�^���X�쐬�͋֎~
    virtual ~SceneManager() = default; //�O������̃C���X�^���X�j�����֎~
};

#endif