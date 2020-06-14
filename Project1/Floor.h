#pragma once
#include "Obj.h"
#include <Outside_A1_ID.h>

enum class FLOOR_TYPE		//床の描画のタイプ
{
	Outside_A1_ID,
};

enum class FLOOR_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	ID,
	MAX
};


using FloorState = std::tuple<FLOOR_TYPE, Vector2Dbl, Vector2Dbl, Outside_A1_ID>;

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
	Outside_A1_ID A1_ID;											//描画A1のID
};

