#pragma once
#include "Obj.h"


enum class ITEAM_TYPE		
{
	石, 
	メニュー,
	スウィッチ,
	ドラゴン床,
	MAX
};
enum class ITEAM_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	ID,
	MAX
};

using IteamState = std::tuple < ITEAM_TYPE, Vector2, Vector2>;


class Iteam :
    public Obj
{
public:
	Iteam();
	Iteam(IteamState& state);

	void Update(sharedObj& plObj) override;							// 更新
	~Iteam();
private:
	void StoneMove(void);
	void Init(void);												// 初期化
	ITEAM_TYPE _type;												// 種類

};

