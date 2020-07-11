#include "GameScene.h"
#include <Dxlib.h>
#include "common/ImageMng.h"

GameScene::GameScene()
{
	IpImageMng.GetID("1", "image/1.png", { 2400,2400 }, { 1,1 });

	_mapState=std::make_unique<MapState>(Vector2{2400,2400});
	_player = std::make_unique<Player>(std::move(Vector2(0, 0)));

	for (int x = 0; x < 75; x++)
	{
		for (int y = 0; y < 75; y++)
		{
			chip[x][y] = 0;
		}
	}


	//chip[1][0] = 1;


	//for (int x = 0; x < 75; x++)
	//{
	//	for (int y = 0; y < 75; y++)
	//	{


	//	}
	//}


}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{

	Draw();



	_mapState->Run();
	

	_player->Run();

	CameraUpdata();
	
	
	////�}�b�v�̑���
	//if (CheckHitKey(KEY_INPUT_W)) mapPos.y -= 4;
	//if (CheckHitKey(KEY_INPUT_S)) mapPos.y += 4;
	//if (CheckHitKey(KEY_INPUT_A)) mapPos.x -= 4;
	//if (CheckHitKey(KEY_INPUT_D)) mapPos.x += 4;



	return std::move(own);
}

void GameScene::Draw(void)
{
	ClsDrawScreen();

	_mapState->Draw();
	
	_player->Draw();

	SetDrawScreen(DX_SCREEN_BACK);

	//SetDrawScreen(DX_SCREEN_BACK);


	DrawGraph(-mapPos.x, -mapPos.y, _mapState->GetScreenId(), true);
	//DrawGraph(-mapPos.x, -mapPos.y, _player->GetScreenId(), true);
	
	for (int y = 0; y < 75; y++)
	{
		for (int x = 0; x < 75; x++)
		{
			//��ʂɃ}�X��`�悷��
			DrawBox(-mapPos.x + x * 32, -mapPos.y + y * 32			//����
				, -mapPos.x + (x + 1) * 32, -mapPos.y + (y + 1) * 32  //�E��
				, GetColor(128, 128, 128)   //���̐F
				, false);   //�h��Ԃ��H

			//��ʂɃ}�X�̔ԍ���`�悷��
			DrawFormatString(-mapPos.x + x * 32 + 1
				, -mapPos.y + y * 32
				, GetColor(0, 128, 0)
				, "%02X", x + y * 32);
		}
	}

	//�v���C���[�̕\��
	//DrawCircle(-mapPos.x + playerPos.x
	//	, -mapPos.y + playerPos.y
	//	, CHIP_SIZE_X / 2
	//	, GetColor(0, 255, 255)
	//	, true);


	ScreenFlip();


}

void GameScene::CameraUpdata(void)
{

	if (_player->_pos.x - mapPos.x > 1280 / 2)
	{
		if (mapPos.x < 2400 - 1280)
		{
			mapPos.x += 4;
		}
		else
		{

			mapPos.x = 75 * 32 - 1280;
		}
	}
	if (_player->_pos.x - mapPos.x < 1280 / 2)
	{
		if (mapPos.x > 0)
		{
			mapPos.x -= 4;
		}
		else
		{
			mapPos.x = 0;
		}
	}

	if (_player->_pos.y - mapPos.y > 800 / 2)
	{
		if (mapPos.y < 2400 - 800)
		{
			mapPos.y += 4;
		}
		else
		{

			mapPos.y = 75 * 32 - 800;
		}
	}
	if (_player->_pos.y - mapPos.y < 800 / 2)
	{
		if (mapPos.y > 0)
		{
			mapPos.y -= 4;
		}
		else
		{
			mapPos.y = 0;
		}
	}
}

