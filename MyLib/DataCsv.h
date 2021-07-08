#ifndef DATACSV_H_
#define DATACSV_H_

#include <memory>
#include <vector>
#include <unordered_map> // �����n�b�V�������z��
#include <string>

#include <fstream> // �t�@�C���ǂݏo��ifstream�ɕK�v
#include <string> //������ɕK�v
#include <sstream> // ������X�g���[���ɕK�v

#include <assert.h> // �}�b�v�Ǎ��ݎ��s�\���p

// CSV�̃}�X�ڂ͖��Ȃ��Ƃɐ���������������������肤��̂ł��̞B��������������N���X
class CsvValue
{
public:

	CsvValue(int intData)
	{
		this->intData = intData;
		this->floatData = static_cast<float>(intData);
		this->stringData = std::to_string(intData);
	}

	CsvValue(float floatData)
	{
		this->intData = (int)floatData;
		this->floatData = floatData;
		this->stringData = std::to_string(floatData);
	}

	CsvValue(std::string stringData)
	{
		//this->intData = std::stoi(stringData);
		//this->floatData = std::stof(stringData);
		this->stringData = stringData;
	}

	~CsvValue()
	{

	}

	// �ϊ����Z�q�ɂ��CSV�̃Z����int�Ƃ��Ă�string�Ƃ��Ă�������悤��
	// https://programming-place.net/ppp/contents/cpp/language/019.html#conversion_op
	int intData;
	inline operator int() const
	{
		return intData;
	}

	float floatData;
	inline operator float() const
	{
		return floatData;
	}

	std::string stringData;
	inline operator std::string() const
	{
		return stringData;
	}
};

// CSV�t�@�C����Ǎ��ݕ��⍂���ƃf�[�^�{�̂�ێ�����f�[�^�^
struct DataCsv
{   // �Ǎ��񂾃f�[�^�t�@�C���̏��
	std::string FilePath = "";
	int Width = 0; // csv�t�@�C���̕\�̕�
	int Height = 0;// csv�t�@�C���̕\�̍���
	std::vector<std::vector<CsvValue>> Data;// csv�f�[�^
	// ���X���[�Y��[][]�ŃA�N�Z�X�ł���悤��[]���Z�q��Ǝ���`����
	// https://programming-place.net/ppp/contents/cpp/language/019.html#index_op
	std::vector<CsvValue>& operator[](std::size_t index) { // �� &�Q�Ƃɂ��Ȃ��Ƃ��������f�[�^�̃R�s�[��Ԃ��̂Œx���Ȃ��
		return Data[index]; // ��������
	}
	std::vector<CsvValue> operator[](std::size_t index) const { // ��const�͓Y����[]�ǂݎ��̏������`
		return Data[index]; // �ǂݎ��
	}

	std::size_t size()
	{   // size()�֐��̖��O��vector�Ɣ�点�邱�ƂŎg������vector�C��vector�̂܂܂̃R�[�h�Ŏg����
		return Data.size();
	}
	// �������R���X�g���N�^�Ńt�@�C�������w�肵�ď������Ɠ����Ƀt�@�C���Ǎ�
	DataCsv(std::string FilePath = "", std::string csvOption = "") :FilePath{ FilePath }
	{// csv�t�@�C���̓Ǎ��݁��y�������Ɠ����Ȃ̂Ńt�@�C���ƃf�[�^�^����S���̂Ŏg���₷���z
		if (FilePath != "" && (csvOption == "" || csvOption == "MAP"))
			LoadMap(FilePath); // �t�@�C���Ǎ���
		else if (FilePath != "" && csvOption == "DATA")
		{
			LoadData(FilePath);
		}
	}
	virtual ~DataCsv()
	{// ���z�f�X�g���N�^
		Data.clear();// 2�����z��f�[�^�̂��|��
	}

	// �f�[�^���N���A���ă�������ߖ񂷂�
	virtual void clear()
	{   // �f�[�^���N���A���ă�������ߖ񂷂�
		Data.clear();// 2�����z��f�[�^�̂��|��@
	}

	// csv�t�@�C���̓ǂݍ���
	void LoadMap(std::string filePath)
	{
		if (filePath == "") return; //�t�@�C�������Ȃ�
		FilePath = filePath; // �t�@�C������ۊ�
		Data.clear(); //�f�[�^����U�N���A
		// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
		std::ifstream ifs_csv_file(filePath);
		std::string line; //1�s�P�ʂ̓Ǎ��ݕ�����

		int readWidth = 0; //�Ǎ��݃f�[�^�̕�
		int maxWidth = 0; //������ǂݍ��񂾎���MAX�̕�
		int readHeight = 0; //������

		while (std::getline(ifs_csv_file, line)) // �t�@�C�����s���Ƃɓǂݍ���
		{
			std::vector<CsvValue> numlist; // 1�s�̐������X�g
			std::istringstream linestream(line); // �e�s�̕�����X�g���[��
			std::string splitted; // �J���}����������
			int widthCount = 0; //���̍s�̕����J�E���g
			while (std::getline(linestream, splitted, { ',' }))
			{
				std::istringstream ss; //������X�g���[���̏�����
				ss = std::istringstream(splitted); //������X�g���[��
				int num; // �����P��
				ss >> num; // ������X�g���[�����琔���ւ̕ϊ�
				numlist.push_back(CsvValue(num)); // �����𐔎��̃��X�g(1�s���X�g)�ɒǉ�
				widthCount++; //���̍s�̕����J�E���g�A�b�v
			}
			if (widthCount > maxWidth) maxWidth = widthCount; //�b��Max�����X�V

			// 1�s����vector�ɒǉ�
			if (numlist.size() != 0) Data.push_back(numlist);
			readHeight++; //�}�b�v�̍������J�E���g�A�b�v
		}
		readWidth = maxWidth; //MAX���̉��҂��m��

		assert(readWidth > 0); // �}�b�v������������
		assert(readHeight > 0); // �}�b�v��������������

		this->Width = readWidth; // �Ǎ��ݐ��������f�[�^�̕����L�^
		this->Height = readHeight; // �Ǎ��ݐ��������f�[�^�̍������L�^

		return;
	}

	void LoadData(std::string filePath)
	{
		if (filePath == "") return; //�t�@�C�������Ȃ�
		FilePath = filePath; // �t�@�C������ۊ�
		Data.clear(); //�f�[�^����U�N���A
		// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
		std::ifstream ifs_csv_file(filePath);
		std::string line; //1�s�P�ʂ̓Ǎ��ݕ�����

		int readWidth = 0; //�Ǎ��݃f�[�^�̕�
		int maxWidth = 0; //������ǂݍ��񂾎���MAX�̕�
		int readHeight = 0; //������

		while (std::getline(ifs_csv_file, line)) // �t�@�C�����s���Ƃɓǂݍ���
		{

			bool intFlg = false;
			bool floatFlg = false;
			bool stringFlg = false;

			std::string stringModelName[3]{ "int","float","string" }; // �^���z��
			bool modelNameFlg[3]{ intFlg,floatFlg,stringFlg }; // �ǂ̌^���œǂݍ��ނ��̃t���O�z��B�^���z��ƑΉ�������

			std::vector<CsvValue> cellList; // 1�s��CSV�̃Z�����X�g
			std::istringstream linestream(line); // �e�s�̕�����X�g���[��
			std::string splitted; // �J���}����������
			int widthCount = 0; //���̍s�̕����J�E���g
			while (std::getline(linestream, splitted, { ',' }))
			{
				if (widthCount < 2)
				{// �f�[�^�̕\�̊�b���ǂݍ��݁y�d�l���ɐ����C���܂��z
					std::istringstream ss; //������X�g���[���̏�����
					ss = std::istringstream(splitted); //������X�g���[��
					std::string stringValue;
					ss >> stringValue;
					cellList.push_back(CsvValue(stringValue));

					for (unsigned int i = 0; i < stringModelName->size(); i++) // �^���z��̐�����for��
					{	//���ڂ܂ł�CSV��(0���:)�J�e�S��(1���:)�^�^�C�v�yint�Ȃǁz�ǂݍ���
						if (stringValue == stringModelName[i]) // �ǂݍ��񂾕����񂪌^����������
						{
							modelNameFlg[i] = true; // ���̌^����ǂݍ���
						}
						else
						{
							modelNameFlg[2] = true; // �^�����Ȃ�������string
						}
					}
				}
				else
				{	//���f�[�^�ǂݍ���
					std::istringstream ss; //������X�g���[���̏�����
					ss = std::istringstream(splitted); //������X�g���[��

					if (modelNameFlg[0])
					{
						int intnum; // �����P��
						ss >> intnum; // ������X�g���[�����琔���ւ̕ϊ�
						cellList.push_back(CsvValue(intnum)); // �����𐔎��̃��X�g(1�s���X�g)�ɒǉ�
					}
					else if (modelNameFlg[1])
					{
						float floatnum; // �����P��
						ss >> floatnum; // ������X�g���[�����琔���ւ̕ϊ�
						cellList.push_back(CsvValue(floatnum)); // �����𐔎��̃��X�g(1�s���X�g)�ɒǉ�
					}
					else if (modelNameFlg[2])
					{
						std::string stringValue; // �����P��
						ss >> stringValue; // ������X�g���[�����琔���ւ̕ϊ�
						cellList.push_back(CsvValue(stringValue)); // �����𕶎��̃��X�g(1�s���X�g)�ɒǉ�
					}
				}
				widthCount++; //���̍s�̕����J�E���g�A�b�v
			}
			if (widthCount > maxWidth) maxWidth = widthCount; //�b��Max�����X�V

			// 1�s����vector�ɒǉ�
			if (cellList.size() != 0) Data.push_back(cellList);
			readHeight++; //�}�b�v�̍������J�E���g�A�b�v
		}
		readWidth = maxWidth; //MAX���̉��҂��m��

		assert(readWidth > 0); // �}�b�v������������
		assert(readHeight > 0); // �}�b�v��������������

		this->Width = readWidth; // �Ǎ��ݐ��������f�[�^�̕����L�^
		this->Height = readHeight; // �Ǎ��ݐ��������f�[�^�̍������L�^

		return;
	}
};

#endif
