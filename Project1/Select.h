#pragma once
#include <iostream>
#include <InputState.h>

struct S_ID
{
	int Title;
	int Mean;
	int GameOver;

};
enum class SceneSel
{
	TITLE,
	Mean,
	GameOver,
	MAX
};


struct Select
{
public:
	void Updata(std::weak_ptr<InputState> keyData, const INPUT_ID id, SceneSel sceneSel, int max,int move);
	
	S_ID s_id;


};

