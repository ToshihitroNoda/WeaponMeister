#ifndef SINGLETON_H_
#define SINGLETON_H_

// �e���v���[�gT�^�V���O���g��Singleton<�`> �`�ɂȂ�ł��w�肵�ėB�ꕨ�ɂł���
// ��Singleton<T>�^�́y�K���B��ŕ����s�z(�g����:�ǂ�����ł��A�N�Z�X���ϐ������L����N���X����)
// ���Q�[�����́y�ǂ�����A�N�Z�X���Ă����ꐫ���ۂ����z(�B�ꂾ����)�u�N���X���Ǝ��̂���v�v
template<class T>
class Singleton
{
public:
    // GetInstance��ʂ��āy�����zT�^�N���X������Ȃ������ɁA
    // ����������̂́y���Ȃ炸�B��ŕ����s�z
    // ���ꂪ�y�V���O���g���^�z�I
    // �Q�[�����ŗB��ŕ����s�ɂ������y�Q�[�����ꗥ�Ǘ�����N���X�z�ȂǂɍœK�I
    // https://teratail.com/questions/17416
    // http://rudora7.blog81.fc2.com/blog-entry-393.html
    // �A�������֐��̒�`�̓v���O�����S�̂łP��������������܂���B(static�֐����͔��Ȃ�)
    static inline T& GetInstance()
    {   //�@���֐��̒��Œ�`���ꂽstatic�ϐ��́A�֐��̒�`���ɂP�̈悪�m�ۂ���܂��B
        static T instance; //���������static�ϐ��m��(�Â��ɏ�ɑҋ@����instance)
        return instance; //�@=(�풓)�A=(�B��) �@�ƇA����������instance�́y��������ɗB��z
    }

protected:
    Singleton() {} // �O���ł̃C���X�^���X�쐬�͋֎~(protected:�������J�A�O���֎~)
    virtual ~Singleton() {} // ���z�f�X�g���N�^(�V���O���g�����y�p�����邽�߂ɂ͖Y�ꂿ��_���z)

private:
    void operator=(const Singleton& obj) {} // ������Z�q�֎~
    Singleton(const Singleton& obj) {} // �R�s�[�R���X�g���N�^�֎~(�R�s�[�ł��Ȃ��y�B��z)
    static T* instance; // private:������O���A�N�Z�X�ł��Ȃ��yGetInstance()�o�R���������z
};

// ����cpp�ŏ�����static�ϐ������������yT�e���v���[�g�N���X�����炷�ׂ�.h�w�b�_�ɂ܂Ƃ߂ď������z
template< class T >
T* Singleton< T >::instance = 0; //cpp�ł̒�`��.h���ɏ�����(static�ϐ���class���ŏ������ł��Ȃ�����)

#endif // !SINGLETON_H_
