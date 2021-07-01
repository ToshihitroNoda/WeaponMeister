#ifndef SCENE_H_
#define SCENE_H_

#include <string>

// �V�[���̊��N���X
class Scene
{
public:
	std::string tag = ""; // �V�[���̎�ނ̔��ʂɎg��

	// �R���X�g���N�^
	Scene() = default;
	// �f�X�g���N�^
	virtual ~Scene() = default;

	// ����������
	virtual void Init()   = 0;

	// �I������
	virtual void Final()  = 0;

	// �X�V����
	virtual void Update() = 0;

	// �V�[���؂�ւ�����
	virtual void Change() = 0;

	// �`�揈��
	virtual void Draw()   = 0;

	bool isDead = false;
};

#endif