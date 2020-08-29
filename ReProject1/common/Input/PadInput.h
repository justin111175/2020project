#pragma once
#include "Controller.h"


class PadInput :
    public Controller
{

	conType GetConType(void) override;
	bool SetUp(void) override;
	void Updata(void) override;
private:
	std::array<char, 256> _keyData;
	std::map<InputID, int> _inputTbl;



};


