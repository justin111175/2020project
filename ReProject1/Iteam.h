#pragma once
#include "Obj.h"


enum class ITEAM_TYPE		
{
	��, 
	���j���[,
	�X�E�B�b�`,
	MAX
};
enum class ITEAM_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
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

	void Update(void) override;							// �X�V
	~Iteam();
private:
	void StoneMove(void);
	void Init(void);												// ������
	ITEAM_TYPE _type;												// ���


};

