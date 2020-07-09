#include "LoadScene.h"
#include <ImageMng.h>
#include "Scene/SceneMng.h"
#include <Player.h>
#include <Enemy.h>
#include <Number.h>
#include <Floor.h>
#include "GameScene.h"

//LoadScene::LoadScene()
//{
//	IpImageMng.GetID("ÉvÉåÉCÉÑÅ[ï‡Ç≠", "image/Player/walk.png", { 32,32 }, { 3,4 });
//	IpImageMng.GetID("ÉvÉåÉCÉÑÅ[éÄÇ ", "image/Player/dead.png", { 50,55 }, { 3,1 });
//
//	IpImageMng.GetID("ÉÇÉìÉXÉ^Å[ï‡Ç≠", "image/Monsters/walk.png", { 48,48 }, { 3,32 });
//
//	IpImageMng.GetID("íe", "image/shot.png", { 43,11 }, { 1,1 });
//	IpImageMng.GetID("éaåÇ", "image/slash.png", { 39,37 }, { 1,1 });
//
//	IpImageMng.GetID("éaåÇ1", "image/slash1.png", { 37,38 }, { 1,1 });
//	IpImageMng.GetID("éaåÇ2", "image/slash2.png", { 37,49 }, { 1,1 });
//
//	IpImageMng.GetID("weapons", "image/weapons.png", { 98,65 }, { 3,4 });
//
//
//
//	IpImageMng.GetID("ÉÅÉjÉÖÅ[", "image/mean.png", { 1280,720 }, { 1,1 });
//	IpImageMng.GetID("ÉÅÉbÉZÅ[ÉW", "image/messagecursor.png", { 50,78 }, { 1,1 });
//	IpImageMng.GetID("ÉXÉeÅ[É^ÉX", "image/status.png", { 1280,720 }, { 1,1 });
//
//
//	IpImageMng.GetID("ëïîı", "image/Equipment.png", { 1280,720 }, { 1,1 });
//	IpImageMng.GetID("â¡å∏", "image/1.png", { 186,50 }, { 1,1 });
//	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });
//
//	IpImageMng.GetID("Bar", "image/bar.png", { 510,66 }, { 1,1 });
//
//	IpImageMng.GetID("HP", "image/gaugeB.png", { 325,22 }, { 1,1 });
//	IpImageMng.GetID("MP", "image/gaugeB (1).png", { 325,22 }, { 1,1 });
//	IpImageMng.GetID("ìGHP", "image/EnemyHp.png", { 60,18 }, { 1,1 });
//	IpImageMng.GetID("ìGHP_BAR", "image/EnemyHpBar.png", { 60,18 }, { 1,1 });
//
//
//
//	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });
//
//	IpImageMng.GetID("UP1", "image/levelUp1.png", { 250,150 }, { 1,8 });
//
//	IpImageMng.GetID("ï∂éö", "image/letter.png", { 1280,720 }, { 1,1 });
//
//	IpImageMng.GetID("UIîwåi", "image/UI_back.png", { 480,480 }, { 1,1 });
//	MapInit();
//
//	IpSceneMng._chipType.first = CHIP_TYPE::êX1;
//
//	_Init[IpSceneMng._chipType.first]();
//
//}
//
//LoadScene::~LoadScene()
//{
//}
//
//
//
//
//
//// ÉNÉâÉX1
//void LoadScene::MapInit(void)
//{
//
//	_Init.try_emplace(CHIP_TYPE::êX1, [&]() {
//		IpSceneMng.mapSize = { 2880,2880 };
//		// ï`âÊÇì«Ç›çûÇﬁ
//		for (int x = 0; x < 90 * 90; x++)
//		{
//			IpSceneMng._mapNow.try_emplace(x, NULL);
//		}
//
//		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
//		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });
//
//		IpImageMng.GetID("êX1", "image/chip/êX1.png", { 2880,2880 }, { 1,1 });
//
//		// csvÉtÉ@ÉCÉãÇì«Ç›çûÇﬁ
//		int type = NULL;
//		int y = 0;
//		int x = 0;
//
//		FILE* fp = NULL;
//		fopen_s(&fp, "csv/êX1.csv", "rb");
//		while (fscanf_s(fp, "%d", &type) != EOF)
//		{
//			IpSceneMng._mapNow[x] = type;
//			x++;
//		}
//
//		FloorState Flrdata;
//
//		MoveState tmpMoveState;
//
//		for (int x = 0; x < 90 * 90; x++)
//		{
//			if (IpSceneMng._mapNow[x] == 0)
//			{
//				Flrdata = { FLOOR_TYPE::ìñÇΩÇËîªíË,{32.0 * (x % 90),32.0 * (x / 90)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//			}
//
//			if (IpSceneMng._mapNow[x] == 1)
//			{
//				_objList.emplace_back(new Player({ 32.0 * (x % 90),32.0 * (x / 90) }, { 32,32 }, { 1.0f,1.0f }));
//
//			}
//
//			if (IpSceneMng._mapNow[x] == 10)
//			{
//				Flrdata = { FLOOR_TYPE::ì`ëó,{32.0 * (x % 90),32.0 * (x / 90)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//
//			}
//
//		}
//
//
//		//ìGëùâ¡Å|ÉâÉÄÉ_éÆ
//		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
//			MoveState tmpMoveState;
//			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });
//
//			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
//			_objList.emplace_back(new Enemy(data));
//		};
//
//		for (int x = 0; x < 1; x++)
//		{
//			for (int y = 0; y < 1; y++)
//			{
//				EnemyAdd(ENEMY_TYPE::ÉRÉEÉÇÉä, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
//			}
//		}
//		return true;
//
//
//	});
//
//
//	_Init.try_emplace(CHIP_TYPE::êX2, [&]() {
//		IpSceneMng.mapSize = { 3840,2432 };
//
//
//
//		// ï`âÊÇì«Ç›çûÇﬁ
//		for (int x = 0; x < 120 * 76; x++)
//		{
//			IpSceneMng._mapNow.try_emplace(x, NULL);
//		}
//
//		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
//		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });
//
//		IpImageMng.GetID("êX2", "image/chip/êX2.png", { 3840,2432 }, { 1,1 });
//
//		// csvÉtÉ@ÉCÉãÇì«Ç›çûÇﬁ
//		int type = NULL;
//		int y = 0;
//		int x = 0;
//
//		FILE* fp = NULL;
//		fopen_s(&fp, "csv/êX2.csv", "rb");
//		while (fscanf_s(fp, "%d", &type) != EOF)
//		{
//			IpSceneMng._mapNow[x] = type;
//			x++;
//		}
//
//		FloorState Flrdata;
//
//		MoveState tmpMoveState;
//
//		for (int x = 0; x < 120 * 76; x++)
//		{
//			if (IpSceneMng._mapNow[x] == 0)
//			{
//				Flrdata = { FLOOR_TYPE::ìñÇΩÇËîªíË,{32.0 * (x % 120),32.0 * (x / 120)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//			}
//
//			if (IpSceneMng._mapNow[x] == 1)
//			{
//				_objList.emplace_back(new Player({ 32.0 * (x % 120),32.0 * (x / 120) }, { 32,32 }, { 1.0f,1.0f }));
//
//			}
//
//			if (IpSceneMng._mapNow[x] == 10)
//			{
//				Flrdata = { FLOOR_TYPE::ì`ëó,{32.0 * (x % 120),32.0 * (x / 120)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//
//			}
//
//		}
//
//		//ìGëùâ¡Å|ÉâÉÄÉ_éÆ
//		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
//			MoveState tmpMoveState;
//			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });
//
//			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
//			_objList.emplace_back(new Enemy(data));
//		};
//
//		for (int x = 0; x < 1; x++)
//		{
//			for (int y = 0; y < 1; y++)
//			{
//				EnemyAdd(ENEMY_TYPE::ÉRÉEÉÇÉä, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
//			}
//		}
//
//		return true;
//
//
//	});
//
//
//	_Init.try_emplace(CHIP_TYPE::êX3, [&]() {
//		IpSceneMng.mapSize = { 1440,1440 };
//
//
//
//		// ï`âÊÇì«Ç›çûÇﬁ
//		for (int x = 0; x < 45 * 45; x++)
//		{
//			IpSceneMng._mapNow.try_emplace(x, NULL);
//		}
//
//		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
//		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });
//
//		IpImageMng.GetID("êX3", "image/chip/êX3.png", { 1440,1440 }, { 1,1 });
//
//		// csvÉtÉ@ÉCÉãÇì«Ç›çûÇﬁ
//		int type = NULL;
//		int y = 0;
//		int x = 0;
//
//		FILE* fp = NULL;
//		fopen_s(&fp, "csv/êX3.csv", "rb");
//		while (fscanf_s(fp, "%d", &type) != EOF)
//		{
//			IpSceneMng._mapNow[x] = type;
//			x++;
//		}
//
//		FloorState Flrdata;
//
//		MoveState tmpMoveState;
//
//		for (int x = 0; x < 45 * 45; x++)
//		{
//			if (IpSceneMng._mapNow[x] == 0)
//			{
//				Flrdata = { FLOOR_TYPE::ìñÇΩÇËîªíË,{32.0 * (x % 45),32.0 * (x / 45)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//			}
//
//			if (IpSceneMng._mapNow[x] == 1)
//			{
//				_objList.emplace_back(new Player({ 32.0 * (x % 45),32.0 * (x / 45) }, { 32,32 }, { 1.0f,1.0f }));
//
//			}
//
//			if (IpSceneMng._mapNow[x] == 10)
//			{
//				Flrdata = { FLOOR_TYPE::ì`ëó,{32.0 * (x % 45),32.0 * (x / 45)},{32.0,32.00} };
//				_objList.emplace_back(new Floor(Flrdata));
//
//			}
//
//		}
//
//		//ìGëùâ¡Å|ÉâÉÄÉ_éÆ
//		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
//			MoveState tmpMoveState;
//			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
//			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });
//
//			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
//			_objList.emplace_back(new Enemy(data));
//		};
//
//		for (int x = 0; x < 1; x++)
//		{
//			for (int y = 0; y < 1; y++)
//			{
//				EnemyAdd(ENEMY_TYPE::ÉRÉEÉÇÉä, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
//			}
//		}
//		
//		
//		return true;
//
//	});
//
//
//
//}