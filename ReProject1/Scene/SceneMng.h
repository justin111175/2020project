#pragma once
#include "BaseScene.h"
#include "..\Layer_id.h"
#include "..\common\Vector2.h"
#include <map>
#include <vector>
#include "GameScene.h"

enum class DRAW_QUE
{
	IMAGE,										// イメージ
	POS,										// 座標
	SIZE,										// サイズ
	EXRATE,										// 拡大縮小率
	RAD,										// 角度
	TURN,
	ZODER,										// Zオーダー（レイヤーの前後順番-数値の低い方が奥）
	LAYER,										// レイヤーID（数値の低い方が奥）
};

enum class TEXT_QUE
{
	STRING,										// イメージ
	POS,										// 座標
	EXRATE,										// 拡大縮小率
	ZODER,										// Zオーダー（レイヤーの前後順番-数値の低い方が奥）
	LAYER										// レイヤーID（数値の低い方が奥）

};


class Obj;

using DrawQueT = std::tuple<int, Vector2, Vector2Dbl, Vector2Dbl, double, bool, int, LAYER>;

using TextQueT = std::tuple<const char*, Vector2, Vector2Dbl, int, LAYER>;

#define IpSceneMng SceneMng::GetInstance()


class SceneMng
{
public:
	// 動的シングルトン
	static SceneMng& GetInstance(void)							// ゲット-インスタンス
	{
		Create();
		return *sInstance;
	}
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}
	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	bool Run(void);



	bool AddDrawQue(DrawQueT dQue);								// 描画を増加する
	bool AddDrawQue(TextQueT tQue);								// 描画を増加する
	bool AddActQue(ActQueT aQue);								// 活動を増加する

	std::pair<CHIP_TYPE, CHIP_TYPE> _chipNo;
	bool _changeFlag;

	Vector2Dbl mapPos;
	Vector2 mapSize;
	std::map<int, int> _mapNow;


	std::vector<int> _dataBase;
	std::vector<int*> _data;


	int _blendCnt;												// ブレンド用カント
	const int frames(void)const;								// フレーム数のゲット関数
	const Vector2 ScreenSize;									// 全画面サイズ

private:
	static SceneMng* sInstance;									// インスタンス
	
	std::vector<DrawQueT> _drawList;							// 描画リスト

	std::vector<TextQueT> _textList;							// 文字リスト
	std::vector<ActQueT> _actList;								// 活動リスト


	std::map<LAYER, int> _screenID;


	void Draw(void);											// 描画

	// スマートポインタ
	unique_Base _activeScene;									// 今Sceneの位置
	int _frames;												// フレーム数


	SceneMng();
	~SceneMng();
	
	bool SysInit(void);											// システム初期化

};

