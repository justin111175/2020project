#pragma once
#include "Obj.h"
#include <functional>

enum class FLOOR_TYPE		//���̕`��̃^�C�v
{
	�����蔻��,
	�`��
};

enum class FLOOR_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
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

	void Update(sharedObj plObj) override;							// �X�V
	~Floor();
private:
	void Init(void);												// ������
	FLOOR_TYPE _type;												// ���

	std::map<std::string, int> _id;
};

