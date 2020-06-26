#include "TimeCount.h"
#include "Scene/SceneMng.h"

void TimeCount::Run(void)
{
	auto type = [&](const char* string) {	
		if (_flag[string])
		{
			if (_cnt[string] > 0)
			{
				_cnt[string]--;
			}
			else
			{
				_flag[string] = false;
			}
		}
	};
	
	type("’e");
	type("ŽaŒ‚");

}

bool TimeCount::Set(const char* string,bool flag, double cnt)
{
	_flag[string] = flag;
	_cnt[string] = cnt*60;

	return true;
}

const bool TimeCount::GetFlag(const char* string)
{
	return _flag[string];
}

TimeCount::TimeCount()
{
	_flag.try_emplace("’e", false);
	_cnt.try_emplace("’e", 0);
	
	_flag.try_emplace("ŽaŒ‚", false);
	_cnt.try_emplace("ŽaŒ‚", 0);
}

TimeCount::~TimeCount()
{
}
