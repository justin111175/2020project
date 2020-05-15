#pragma once
#include <map>
#include "INPUT_ID.h"


using KeyPair = std::pair<int, int>;				// キー今の情報、オルト情報
using KeyMap = std::map<INPUT_ID, KeyPair>;			// インプットID、（キー今の情報、オルトの情報）

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update(void) =0;

	const KeyMap& state(void)const;					// ゲット関数
	const KeyPair& state(INPUT_ID id)const;
	bool state(INPUT_ID id, int data);				// 今のINPUTキー情報のセット関数
	void SetOld(void);								// オルトのINPUTキー情報のセット関数
private:
	KeyMap _state;
};

