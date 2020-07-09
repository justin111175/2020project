#pragma once
#include "Obj.h"
#include <functional>

enum class FLOOR_TYPE		//床の描画のタイプ
{
	当たり判定,
	伝送
};

enum class FLOOR_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	ID,
	MAX
};

using FloorState = std::tuple < FLOOR_TYPE, Vector2Dbl, Vector2Dbl> ;

class Floor;

class Floor :
	public Obj
{
public:
	Floor();
	Floor(FloorState& state);

	void Update(void) override;							// 更新
	~Floor();
private:
	void Init(void);												// 初期化
	FLOOR_TYPE _type;												// 種類

	std::map<std::string, int> _id;
};

