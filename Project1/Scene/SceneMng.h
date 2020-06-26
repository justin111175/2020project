#pragma once
#include <common\Vector2.h>
#include <vector>
#include <memory>
#include "BaseScene.h"
#include <tuple>										//要素が三つ以上を管理する時を使う
#include "Layer_id.h"
#include <map>
#include <InputState.h>
#include <Select.h>


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

using DrawQueT = std::tuple<int, Vector2Dbl, Vector2Dbl,Vector2Dbl, double,bool, int, LAYER>;

using TextQueT = std::tuple<const char*, Vector2Dbl, Vector2Dbl,int, LAYER>;



// デファイン
#define IpSceneMng SceneMng::GetInstance()

#define _mapPos SceneMng::GetInstance().mapPos
#define _Input SceneMng::GetInstance()._input

#define _select SceneMng::GetInstance().select



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
	
	int mapNow[50][50];


	bool AddDrawQue(DrawQueT dQue);								// 描画を増加する
	bool AddDrawQue(TextQueT tQue);								// 描画を増加する
	
	bool AddActQue(ActQueT aQue);								// 活動を増加する

	const Vector2 ScreenSize;									// 全画面サイズ
	const Vector2 GameScreenSize;								// 全画面サイズの4分の１

	Vector2Dbl mapPos;



	std::shared_ptr<InputState> _input;							// シェアポインタ-キー情報

	Select select;												//選択用

	int _blendCnt;												// ブレンド用カント
	

	const int frames(void)const;								// フレーム数のゲット関数
	
private:
	static SceneMng* sInstance;									// インスタンス
	// スマートポインタ
	unique_Base _activeScene;									// 今Sceneの位置

	void Draw(void);											// 描画
	int _frames;												// フレーム数
	int _layerGID;												// レイヤーID

	std::map<LAYER, int> _screenID;								
	
	std::vector<DrawQueT> _drawList;							// 描画リスト
	
	std::vector<TextQueT> _textList;							// 文字リスト
	
	std::vector<ActQueT> _actList;								// 活動リスト

	~SceneMng();
	SceneMng();
	bool SysInit(void);											// システム初期化
};



