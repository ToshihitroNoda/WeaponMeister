#ifndef DATACSV_H_
#define DATACSV_H_

#include <memory>
#include <vector>
#include <unordered_map> // 高速ハッシュ辞書配列
#include <string>

#include <fstream> // ファイル読み出しifstreamに必要
#include <string> //文字列に必要
#include <sstream> // 文字列ストリームに必要

#include <assert.h> // マップ読込み失敗表示用

// CSVのマス目は厄介なことに整数も小数も文字列もありうるのでその曖昧さを解消するクラス
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

	// 変換演算子によりCSVのセルをintとしてもstringとしても扱えるように
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

// CSVファイルを読込み幅や高さとデータ本体を保持するデータ型
struct DataCsv
{   // 読込んだデータファイルの情報
	std::string FilePath = "";
	int Width = 0; // csvファイルの表の幅
	int Height = 0;// csvファイルの表の高さ
	std::vector<std::vector<CsvValue>> Data;// csvデータ
	// ★スムーズに[][]でアクセスできるように[]演算子を独自定義する
	// https://programming-place.net/ppp/contents/cpp/language/019.html#index_op
	std::vector<CsvValue>& operator[](std::size_t index) { // ★ &参照にしないといちいちデータのコピーを返すので遅くなるよ
		return Data[index]; // 書き込み
	}
	std::vector<CsvValue> operator[](std::size_t index) const { // ★constは添え字[]読み取りの処理を定義
		return Data[index]; // 読み取り
	}

	std::size_t size()
	{   // size()関数の名前をvectorと被らせることで使う側はvectorインvectorのままのコードで使える
		return Data.size();
	}
	// 初期化コンストラクタでファイル名を指定して初期化と同時にファイル読込
	DataCsv(std::string FilePath = "", std::string csvOption = "") :FilePath{ FilePath }
	{// csvファイルの読込み★【初期化と同時なのでファイルとデータ型が一心同体で使いやすい】
		if (FilePath != "" && (csvOption == "" || csvOption == "MAP"))
			LoadMap(FilePath); // ファイル読込み
		else if (FilePath != "" && csvOption == "DATA")
		{
			LoadData(FilePath);
		}
	}
	virtual ~DataCsv()
	{// 仮想デストラクタ
		Data.clear();// 2次元配列データのお掃除
	}

	// データをクリアしてメモリを節約する
	virtual void clear()
	{   // データをクリアしてメモリを節約する
		Data.clear();// 2次元配列データのお掃除@
	}

	// csvファイルの読み込み
	void LoadMap(std::string filePath)
	{
		if (filePath == "") return; //ファイル名がない
		FilePath = filePath; // ファイル名を保管
		Data.clear(); //データを一旦クリア
		// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
		std::ifstream ifs_csv_file(filePath);
		std::string line; //1行単位の読込み文字列

		int readWidth = 0; //読込みデータの幅
		int maxWidth = 0; //今から読み込んだ時のMAXの幅
		int readHeight = 0; //初期化

		while (std::getline(ifs_csv_file, line)) // ファイルを行ごとに読み込む
		{
			std::vector<CsvValue> numlist; // 1行の数字リスト
			std::istringstream linestream(line); // 各行の文字列ストリーム
			std::string splitted; // カンマ分割文字列
			int widthCount = 0; //この行の幅をカウント
			while (std::getline(linestream, splitted, { ',' }))
			{
				std::istringstream ss; //文字列ストリームの初期化
				ss = std::istringstream(splitted); //文字列ストリーム
				int num; // 数字単体
				ss >> num; // 文字列ストリームから数字への変換
				numlist.push_back(CsvValue(num)); // 数字を数字のリスト(1行リスト)に追加
				widthCount++; //この行の幅をカウントアップ
			}
			if (widthCount > maxWidth) maxWidth = widthCount; //暫定Max幅を更新

			// 1行分をvectorに追加
			if (numlist.size() != 0) Data.push_back(numlist);
			readHeight++; //マップの高さをカウントアップ
		}
		readWidth = maxWidth; //MAX幅の王者を確定

		assert(readWidth > 0); // マップ幅がおかしい
		assert(readHeight > 0); // マップ高さがおかしい

		this->Width = readWidth; // 読込み成功したデータの幅を記録
		this->Height = readHeight; // 読込み成功したデータの高さを記録

		return;
	}

	void LoadData(std::string filePath)
	{
		if (filePath == "") return; //ファイル名がない
		FilePath = filePath; // ファイル名を保管
		Data.clear(); //データを一旦クリア
		// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
		std::ifstream ifs_csv_file(filePath);
		std::string line; //1行単位の読込み文字列

		int readWidth = 0; //読込みデータの幅
		int maxWidth = 0; //今から読み込んだ時のMAXの幅
		int readHeight = 0; //初期化

		while (std::getline(ifs_csv_file, line)) // ファイルを行ごとに読み込む
		{

			bool intFlg = false;
			bool floatFlg = false;
			bool stringFlg = false;

			std::string stringModelName[3]{ "int","float","string" }; // 型名配列
			bool modelNameFlg[3]{ intFlg,floatFlg,stringFlg }; // どの型名で読み込むかのフラグ配列。型名配列と対応させる

			std::vector<CsvValue> cellList; // 1行のCSVのセルリスト
			std::istringstream linestream(line); // 各行の文字列ストリーム
			std::string splitted; // カンマ分割文字列
			int widthCount = 0; //この行の幅をカウント
			while (std::getline(linestream, splitted, { ',' }))
			{
				if (widthCount < 2)
				{// データの表の基礎情報読み込み【仕様書に説明任せます】
					std::istringstream ss; //文字列ストリームの初期化
					ss = std::istringstream(splitted); //文字列ストリーム
					std::string stringValue;
					ss >> stringValue;
					cellList.push_back(CsvValue(stringValue));

					for (unsigned int i = 0; i < stringModelName->size(); i++) // 型名配列の数だけfor文
					{	//二列目まではCSVの(0列目:)カテゴリ(1列目:)型タイプ【intなど】読み込み
						if (stringValue == stringModelName[i]) // 読み込んだ文字列が型名だったら
						{
							modelNameFlg[i] = true; // その型名を読み込む
						}
						else
						{
							modelNameFlg[2] = true; // 型名がなかったらstring
						}
					}
				}
				else
				{	//実データ読み込み
					std::istringstream ss; //文字列ストリームの初期化
					ss = std::istringstream(splitted); //文字列ストリーム

					if (modelNameFlg[0])
					{
						int intnum; // 数字単体
						ss >> intnum; // 文字列ストリームから数字への変換
						cellList.push_back(CsvValue(intnum)); // 数字を数字のリスト(1行リスト)に追加
					}
					else if (modelNameFlg[1])
					{
						float floatnum; // 数字単体
						ss >> floatnum; // 文字列ストリームから数字への変換
						cellList.push_back(CsvValue(floatnum)); // 数字を数字のリスト(1行リスト)に追加
					}
					else if (modelNameFlg[2])
					{
						std::string stringValue; // 文字単体
						ss >> stringValue; // 文字列ストリームから数字への変換
						cellList.push_back(CsvValue(stringValue)); // 文字を文字のリスト(1行リスト)に追加
					}
				}
				widthCount++; //この行の幅をカウントアップ
			}
			if (widthCount > maxWidth) maxWidth = widthCount; //暫定Max幅を更新

			// 1行分をvectorに追加
			if (cellList.size() != 0) Data.push_back(cellList);
			readHeight++; //マップの高さをカウントアップ
		}
		readWidth = maxWidth; //MAX幅の王者を確定

		assert(readWidth > 0); // マップ幅がおかしい
		assert(readHeight > 0); // マップ高さがおかしい

		this->Width = readWidth; // 読込み成功したデータの幅を記録
		this->Height = readHeight; // 読込み成功したデータの高さを記録

		return;
	}
};

#endif
