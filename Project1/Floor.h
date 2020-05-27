#pragma once
#include "Obj.h"

enum class FLOOR_TYPE
{
	�h���S��_��_1,
	�h���S��_��_2,
	�h���S��_��_3,
	�h���S��_��_4,
	�h���S��_�E_1,
	�h���S��_�E_2,
	�h���S��_�E_3,
	�h���S��_�E_4,


};

enum class FLOOR_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
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

	void Update(sharedObj plObj) override;							// �X�V
	~Floor();

private:
	void Init(void);												// ������
	FLOOR_TYPE _type;												// ���
};

