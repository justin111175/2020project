#pragma once

enum class DIR_ID
{
	DOWN,						// â∫
	LEFT,						// ç∂
	RIGHT,						// âE
	UP,							// è„
	MAX
};


DIR_ID begin(DIR_ID);
DIR_ID end(DIR_ID);
DIR_ID operator*(DIR_ID& key);
DIR_ID operator++(DIR_ID& key);
