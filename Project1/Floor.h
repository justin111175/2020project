#pragma once
#include "Obj.h"
#include <Outside_A1_ID.h>

enum class FLOOR_TYPE
{
	Outside_A1_ID,
};

enum class FLOOR_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
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

	void Update(sharedObj plObj) override;							// �X�V
	~Floor();

private:
	void Init(void);												// ������
	FLOOR_TYPE _type;												// ���
	Outside_A1_ID A1_ID;
};

