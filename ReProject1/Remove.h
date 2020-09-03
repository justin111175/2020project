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


using RemoveState = std::tuple < Remove_ID, Vector2, Vector2>;

class Remove:
	public Obj
{
public:
	Remove(RemoveState & state);
	~Remove();

	void Update(sharedObj& plObj) override;							// 更新


private:
	void Init(void);									// 初期化
	Remove_ID _id;
};
