#pragma once
#include "Obj.h"

enum class FLOOR_TYPE
{
	ドラゴン_左_1,
	ドラゴン_左_2,
	ドラゴン_左_3,
	ドラゴン_左_4,
	ドラゴン_右_1,
	ドラゴン_右_2,
	ドラゴン_右_3,
	ドラゴン_右_4,


};

enum class FLOOR_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	MAX
};


using FloorState = std::tuple<FLOOR_TYPE, Vector2Dbl, Vector2Dbl>;

class Floor;

class Floor :
	public Obj
{
public:
	Floor();
	Floor(FloorState& state);

	void Update(sharedObj plObj) override;							// 更新
	~Floor();

private:
	void Init(void);												// 初期化
	FLOOR_TYPE _type;												// 種類
};

