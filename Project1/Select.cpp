#include "Select.h"

void Select::Updata(std::weak_ptr<InputState> keyData, const INPUT_ID id, SceneSel sceneSel, int max,int move)
{

	if (!keyData.expired())
	{
		if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
		{
			switch (sceneSel)
			{
			case SceneSel::TITLE:
				if (id == INPUT_ID::UP)
				{
					if (s_id.Title > 0)
					{
						s_id.Title = s_id.Title +move;
					}
					else
					{
						s_id.Title = max;
					}
				}
			
				if (id == INPUT_ID::DOWN)
				{
					if (s_id.Title < max)
					{
						s_id.Title =s_id.Title+ move;
					}
					else
					{
						s_id.Title = 0;
					}
				}
				break;
			case SceneSel::Mean:

				if (id == INPUT_ID::LEFT)
				{
					if (s_id.Mean > 0)
					{
						s_id.Mean = s_id.Mean + move;
					}
					else
					{
						s_id.Mean = max;
					}
				}

				if (id == INPUT_ID::RIGHT)
				{
					if (s_id.Mean < max)
					{
						s_id.Mean = s_id.Mean + move;
					}
					else
					{
						s_id.Mean = 0;
					}
				}


				break;
			case SceneSel::GameOver:
				
				if (id == INPUT_ID::UP)
				{
					if (s_id.GameOver > 0)
					{
						s_id.GameOver = s_id.GameOver + move;
					}
					else
					{
						s_id.GameOver = max;
					}
				}

				if (id == INPUT_ID::DOWN)
				{
					if (s_id.GameOver < max)
					{
						s_id.GameOver = s_id.GameOver + move;
					}
					else
					{
						s_id.GameOver = 0;
					}
				}


				break;
			default:
				break;
			}

		}
	}

	



}
