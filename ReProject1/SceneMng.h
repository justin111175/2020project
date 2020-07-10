#pragma once
#include "BaseScene.h"


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





	int _blendCnt;												// ブレンド用カント
	const int frames(void)const;								// フレーム数のゲット関数
	const Vector2 ScreenSize;									// 全画面サイズ

private:
	static SceneMng* sInstance;									// インスタンス
	
	void Draw(void);											// 描画
															// スマートポインタ
	unique_Base _activeScene;									// 今Sceneの位置
	int _frames;												// フレーム数


	SceneMng();
	~SceneMng();
	
	bool SysInit(void);											// システム初期化

};

