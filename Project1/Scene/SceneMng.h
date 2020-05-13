#pragma once
#include <common\Vector2.h>
#include <vector>
#include <memory>
#include "BaseScene.h"
#include <tuple>										//要素が三つ以上を管理する時を使う
#include "Layer_id.h"
#include <map>

enum class DRAW_QUE
{
	IMAGE,										// イメージ
	X,											// 座標X
	Y,											// 座標Y
	SIZE_X,										// サイズX
	SIZE_Y,										// サイズY
	RAD,										// 角度
	ZODER,										// Zオーダー（レイヤーの前後順番-数値の低い方が奥）
	LAYER,										// レイヤーID（数値の低い方が奥）
};

//enum TRG
//{
//	TRG_NOW,									// 現在
//	TRG_OLD,									// １フレーム前
//	TRG_MAX
//};

//struct Key										// キー情報セット
//{
//	bool up[TRG_MAX];
//	bool right[TRG_MAX];
//	bool down[TRG_MAX];
//	bool left[TRG_MAX];
//	bool Y[TRG_MAX];
//	bool B[TRG_MAX];
//	bool A[TRG_MAX];
//	bool X[TRG_MAX];
//};

class Obj;

using DrawQueT = std::tuple<int, double, double, int,int, double, int, LAYER>;

// デファイン
#define IpSceneMng SceneMng::GetInstance()

//#define _mapPos SceneMng::GetInstance().MapPos
//#define _mapSize SceneMng::GetInstance().MapSize
//#define _Input SceneMng::GetInstance()._input


class SceneMng
{
public:
	// 動的シングルトン
	static SceneMng &GetInstance(void)							// ゲット-インスタンス
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
	void Run(void);


	bool AddDrawQue(DrawQueT dQue);								// 描画を増加する
	bool AddActQue(ActQueT aQue);								// 活動を増加する

	const Vector2 ScreenSize;									// 全画面サイズ
	const Vector2 GameScreenSize;								// 全画面サイズの4分の１


	int _blendCnt;												// ブレンド用カント

	const int frames(void)const;								// フレーム数のゲット関数

private:
	static SceneMng* sInstance;									// インスタンス
	// スマートポインタ
	unique_Base _activeScene;									// 今Sceneの位置

	void Draw(void);											// 描画
	int _frames;												// フレーム数
	int _layerGID;												// レイヤーID

	std::map<LAYER, int> _screenID;								// 
	std::vector<DrawQueT> _drawList;							// 描画リスト
	std::vector<ActQueT> _actList;								// 活動リスト

	~SceneMng();
	SceneMng();
	bool SysInit(void);											// システム初期化
};



