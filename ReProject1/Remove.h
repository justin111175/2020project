#pragma once
#include "Obj.h"

enum class Remove_ID
{
	test1,
	test2,
	MAX

};

enum class Remove_State
{
	ID,
	座標,
	サイズ,
	MAX
};


using RemoveState = std::tuple < Remove_ID, Vector2Dbl, Vector2Dbl>;

class Remove:
	public Obj
{
public:
	Remove(RemoveState & state);
	~Remove();

	void Update(void) override;							// 更新


private:
	void Init(void);									// 初期化
	Remove_ID _id;
};
