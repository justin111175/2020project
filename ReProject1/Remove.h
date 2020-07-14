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
	���W,
	�T�C�Y,
	MAX
};


using RemoveState = std::tuple < Remove_ID, Vector2Dbl, Vector2Dbl>;

class Remove:
	public Obj
{
public:
	Remove(RemoveState & state);
	~Remove();

	void Update(void) override;							// �X�V


private:
	void Init(void);									// ������
	Remove_ID _id;
};
