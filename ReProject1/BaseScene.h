#pragma once
#include <memory>
#include<string>
#include "common/Vector2.h"



class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;							// スマートポインタ-BaseScene


class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;					// 純粋仮想関数

protected:
	void FadeInit(std::string fadeType);								// Fade初期化
	bool FadeUpdate(void);												// Fade更新
private:
	int _fadeScrID;														// Fade描画ID
	std::string _fadeType;												// Fadeタイプ
};


