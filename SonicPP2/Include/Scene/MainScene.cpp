
#include "MainScene.h"
#include "../GameObject/BackObj.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "../Widget/CharacterHUD.h"
#include "../GameObject/TileMap.h"
#include "../GameObject/Sonic.h"
#include "../GameObject/RihnoBot.h"
#include "../GameObject/Tulippon.h"
#include "../GameObject/BgSky.h"
#include "../GameObject/BgTree.h"
#include "../GameObject/BgForest.h"
#include "../GameObject/Spring.h"
#include "../GameObject/Ring.h"
#include "../GameObject/EggBossFire.h"
#include "../GameObject/CircleMap.h"
#include "../GameObject/PlatForm.h"

CMainScene::CMainScene()
{
}

CMainScene::~CMainScene()
{
}

bool CMainScene::Init()
{
	m_DEBUG = false;

	CInput::GetInst()->SetMouseOn(false);

	CreateAnimationSequence();

	GetSceneResource()->LoadSound("BGM", "STAGE1ACT1BGM", true, "Act1BGM.mp3");
	GetSceneResource()->LoadSound("BGM", "Boss", true, "Boss.mp3");
	GetSceneResource()->LoadSound("Effect", "SpinDash", false, "SpinDash.WAV");
	GetSceneResource()->LoadSound("Effect", "Jump", false, "Jump.WAV");
	GetSceneResource()->LoadSound("Effect", "SmallBomb", false, "MonsterDie.WAV");
	GetSceneResource()->LoadSound("Effect", "RingGet", false, "RingGet.WAV");
	GetSceneResource()->LoadSound("Effect", "SonicStopping", false, "SonicStopping.WAV");
	GetSceneResource()->LoadSound("Effect", "GetHitRing", false, "GetHitRing.WAV");
	GetSceneResource()->LoadSound("Effect", "BounceUp", false, "BounceUp.WAV");
	GetSceneResource()->LoadSound("Effect", "Hit", false, "Hit.WAV");
	GetSceneResource()->LoadSound("BGM", "Clear", false, "Clear.WAV");
	
	
	GetSceneResource()->SoundPlay("STAGE1ACT1BGM");

	GetSceneResource()->SetVolume(30);

	GetCamera()->SetResolution(800.f, 480.f);
	//GetCamera()->SetWorldResolution(1880.f, 765.f);
	GetCamera()->SetWorldResolution(7488, 1536);
	GetCamera()->SetTargetPivot(0.4f, 0.7f);

	CBackObj* BackObj = CreateObject<CBackObj>("BackObj");
	CBgSky* BgSky = CreateObject<CBgSky>("BgSky");
	//CBgForest* BgForest = CreateObject<CBgForest>("BgFst");
	
	//Create Player: Sonic
	CSonic* Player = CreateObject<CSonic>("Player");

	SetPlayer(Player);

	GetCamera()->SetTarget(Player);


	//Create Monster
	//RihnoBot	
	CRihnoBot* Rihno = CreateObject<CRihnoBot>("Rihno");

	Rihno->SetPos(500.f, 160.f);

	//Tulippon
	GetSceneResource()->LoadTexture("TulipponBomb",
		TEXT("Stage1/Monster/Tulippon/Thorn.bmp"));

	CTulippon* Tulippon = CreateObject<CTulippon>("Tulippon");

	Tulippon->SetPos(580.f, 120.f);



	////////////////BOSS//////////////

	CEggBossFire* EggBossFire = CreateObject<CEggBossFire>("EggBossFire");

	EggBossFire->SetPos(8150.f, 613.f);



	////////////////MapObject////////////////
	
	//////Spring
	//CSpring* Spring1 = CreateObject<CSpring>("Spring");
	//Spring1->SetPos(720.f, 1056.f);
	//Spring1->SetObjectDir(EObject_Dir::Up);

	//1836 1053
	CSpring* Spring2 = CreateObject<CSpring>("Spring");
	Spring2->SetPos(1836.f, 1053.f);
	Spring2->SetObjectDir(EObject_Dir::Up);

	//5424 813
	CSpring* Spring3 = CreateObject<CSpring>("Spring");
	Spring3->SetPos(5424.f, 808.f);
	Spring3->SetObjectDir(EObject_Dir::Up);

	//6666 1120
	CSpring* Spring4 = CreateObject<CSpring>("Spring");
	Spring4->SetPos(6666.f, 1120.f);
	Spring4->SetObjectDir(EObject_Dir::Up);

	//4920 1308
	CSpring* Spring5 = CreateObject<CSpring>("Spring");
	Spring5->SetPos(4920.f, 1308.f);
	Spring5->SetObjectDir(EObject_Dir::Up);

	//////////////PlatForm
	CPlatForm* PlatForm1 = CreateObject<CPlatForm>("PlatForm");
	PlatForm1->SetPos(2104, 846);
	PlatForm1->SetMove();

	CPlatForm* PlatForm2 = CreateObject<CPlatForm>("PlatForm");
	PlatForm2->SetPos(4585, 900);

	//3512 980
	CPlatForm* PlatForm3 = CreateObject<CPlatForm>("PlatForm");
	PlatForm3->SetPos(3512, 990);


	////Ring
	CRing* Ring = CreateObject<CRing>("Ring"); Ring->SetPos(580.f, 994.f);
	CRing* Ring1 = CreateObject<CRing>("Ring"); Ring1->SetPos(620.f, 994.f);
	CRing* Ring2 = CreateObject<CRing>("Ring"); Ring2->SetPos(660.f, 994.f);
	CRing* Ring3 = CreateObject<CRing>("Ring"); Ring3->SetPos(700.f, 994.f);

	//2055 955
	CRing* Ring4 = CreateObject<CRing>("Ring"); Ring4->SetPos(2055.f, 955.f);
	CRing* Ring5 = CreateObject<CRing>("Ring"); Ring5->SetPos(2095.f, 955.f);
	CRing* Ring6 = CreateObject<CRing>("Ring"); Ring6->SetPos(2135.f, 955.f);



	//////////CircleMap
	//3840, 992
	CCircleMap* CircleMap1 = CreateObject<CCircleMap>("CircleMap");
	CircleMap1->SetPos(3968.f, 1090.f);
	CircleMap1->SetLine();

	//5632, 608 + 128 , 98
	CCircleMap* CircleMap2 = CreateObject<CCircleMap>("CircleMap");
	CircleMap2->SetPos(5760.f, 706.f);
	CircleMap2->SetLine();

	//6016, 736
	CCircleMap* CircleMap3 = CreateObject<CCircleMap>("CircleMap");
	CircleMap3->SetPos(6144.f, 834.f);
	CircleMap3->SetLine();

	//TileMap
	CTileMap* TileMap = CreateObject<CTileMap>("TileMap");

	//TileMap->LoadFileName("Map48.tmp", MAP_PATH);
	
	TileMap->LoadFileName("Test.tmp", MAP_PATH);


	CInput::GetInst()->AddBindFunction<CMainScene>("Cam1",
		Input_Type::Down, this, &CMainScene::Cam1Key, this);
	CInput::GetInst()->AddBindFunction<CMainScene>("DEBUG",
		Input_Type::Down, this, &CMainScene::Cam2Key, this);

	CreateWidgetWindow<CCharacterHUD>("CharacterHUD");

	return true;
}

void CMainScene::CreateAnimationSequence()
{
	/////////////////////////SONIC ANIMATION START/////////////////////////
	//Idle
	GetSceneResource()->CreateAnimationSequence("SonicRightIdle",
		"SonicRightIdle", TEXT("Character/Sonic/RightIdle.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SonicRightIdle", 0.f, 0.f,
			48.f, 48.f);
	GetSceneResource()->SetColorKey("SonicRightIdle", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftIdle",
		"SonicLeftIdle", TEXT("Character/Sonic/LeftIdle.bmp"), TEXTURE_PATH);

	GetSceneResource()->AddAnimationFrame("SonicLeftIdle", 0.f, 0.f,
			48.f, 48.f);

	GetSceneResource()->SetColorKey("SonicLeftIdle", 13, 72, 7);
	
	//Board
	GetSceneResource()->CreateAnimationSequence("SonicRightBoard",
		"SonicRightBoard", TEXT("Character/Sonic/Idle/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightBoard", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightBoard", 13, 72, 7);
	
	GetSceneResource()->CreateAnimationSequence("SonicLeftBoard",
		"SonicLeftBoard", TEXT("Character/Sonic/Idle/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 9; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftBoard", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftBoard", 13, 72, 7);

	//SpinDash
	GetSceneResource()->CreateAnimationSequence("SonicRightSpinDash",
		"SonicRightSpinDash", TEXT("Character/Sonic/SpinDash/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightSpinDash", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightSpinDash", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftSpinDash",
		"SonicLeftSpinDash", TEXT("Character/Sonic/SpinDash/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 10; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftSpinDash", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftSpinDash", 13, 72, 7);

	//Crouching
	GetSceneResource()->CreateAnimationSequence("SonicRightCrouching",
		"SonicRightCrouching", TEXT("Character/Sonic/Crouching/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightCrouching", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightCrouching", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftCrouching",
		"SonicLeftCrouching", TEXT("Character/Sonic/Crouching/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftCrouching", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftCrouching", 13, 72, 7);

	//Rolling //Jump
	GetSceneResource()->CreateAnimationSequence("SonicRightRolling",
		"SonicRightRolling", TEXT("Character/Sonic/Rolling/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightRolling", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightRolling", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftRolling",
		"SonicLeftRolling", TEXT("Character/Sonic/Rolling/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftRolling", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftRolling", 13, 72, 7);

	//LookingUp
	GetSceneResource()->CreateAnimationSequence("SonicRightLookingUp",
		"SonicRightLookingUp", TEXT("Character/Sonic/LookingUp/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightLookingUp", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightLookingUp", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftLookingUp",
		"SonicLeftLookingUp", TEXT("Character/Sonic/LookingUp/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftLookingUp", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftLookingUp", 13, 72, 7);

	//Stop
	GetSceneResource()->CreateAnimationSequence("SonicRightStop",
		"SonicRightStop", TEXT("Character/Sonic/Stop/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightStop", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightStop", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftStop",
		"SonicLeftStop", TEXT("Character/Sonic/Stop/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftStop", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftStop", 13, 72, 7);

	//BasicMotion
	GetSceneResource()->CreateAnimationSequence("SonicRightWalk",
		"SonicRightWalk", TEXT("Character/Sonic/BasicMotion/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightWalk", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightWalk", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftWalk",
		"SonicLeftWalk", TEXT("Character/Sonic/BasicMotion/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftWalk", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftWalk", 13, 72, 7);

	//FullSpeed
	GetSceneResource()->CreateAnimationSequence("SonicRightFullSpeed",
		"SonicRightFullSpeed", TEXT("Character/Sonic/FullSpeed/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightFullSpeed", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightFullSpeed", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftFullSpeed",
		"SonicLeftFullSpeed", TEXT("Character/Sonic/FullSpeed/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftFullSpeed", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftFullSpeed", 13, 72, 7);

	//Stand
	GetSceneResource()->CreateAnimationSequence("SonicRightStand",
		"SonicRightStand", TEXT("Character/Sonic/Stand/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightStand", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightStand", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftStand",
		"SonicLeftStand", TEXT("Character/Sonic/Stand/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftStand", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftStand", 13, 72, 7);

	//BounceUp
	GetSceneResource()->CreateAnimationSequence("SonicRightBounceUp",
		"SonicRightBounceUp", TEXT("Character/Sonic/BounceUp/Right.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SonicRightBounceUp", 0.f, 0.f,
		48.f, 52.f);
	GetSceneResource()->SetColorKey("SonicRightBounceUp", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftBounceUp",
		"SonicLeftBounceUp", TEXT("Character/Sonic/BounceUp/Left.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SonicLeftBounceUp", 0.f, 0.f,
		48.f, 52.f);
	GetSceneResource()->SetColorKey("SonicLeftBounceUp", 13, 72, 7);

	//Pushing
	GetSceneResource()->CreateAnimationSequence("SonicRightPush",
		"SonicRightPush", TEXT("Character/Sonic/Pushing/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicRightPush", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicRightPush", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftPush",
		"SonicLeftPush", TEXT("Character/Sonic/Pushing/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SonicLeftPush", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("SonicLeftPush", 13, 72, 7);

	////Hit
	GetSceneResource()->CreateAnimationSequence("SonicRightHit",
		"SonicRightHit", TEXT("Character/Sonic/Hurt/Right.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SonicRightHit", 0.f, 0.f,
			48.f, 48.f);
	GetSceneResource()->SetColorKey("SonicRightHit", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("SonicLeftHit",
		"SonicLeftHit", TEXT("Character/Sonic/Hurt/Left.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SonicLeftHit", 0.f, 0.f,
			48.f, 48.f);
	GetSceneResource()->SetColorKey("SonicLeftHit", 13, 72, 7);
	
	/////////////Angle//////////

	/////////Basic
	////BasicUp
	GetSceneResource()->CreateAnimationSequence("BasicUpRight",
		"BasicUpRight", TEXT("Character/Sonic/BasicAngled/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicUpRight", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicUpRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("BasicUpLeft",
		"BasicUpLeft", TEXT("Character/Sonic/BasicAngled/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicUpLeft", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicUpLeft", 13, 72, 7);

	////BasicDown
	GetSceneResource()->CreateAnimationSequence("BasicDownRight",
		"BasicDownRight", TEXT("Character/Sonic/BasicDown/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicDownRight", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicDownRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("BasicDownLeft",
		"BasicDownLeft", TEXT("Character/Sonic/BasicDown/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicDownLeft", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicDownLeft", 13, 72, 7);

	////BasicUpReverse
	GetSceneResource()->CreateAnimationSequence("BasicUpReverseRight",
		"BasicUpReverseRight", TEXT("Character/Sonic/BasicUpReverse/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicUpReverseRight", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicUpReverseRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("BasicUpReverseLeft",
		"BasicUpReverseLeft", TEXT("Character/Sonic/BasicUpReverse/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicUpReverseLeft", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicUpReverseLeft", 13, 72, 7);

	////BasicDownReverse
	GetSceneResource()->CreateAnimationSequence("BasicDownReverseRight",
		"BasicDownReverseRight", TEXT("Character/Sonic/BasicDownReverse/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicDownReverseRight", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicDownReverseRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("BasicDownReverseLeft",
		"BasicDownReverseLeft", TEXT("Character/Sonic/BasicDownReverse/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 8; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BasicDownReverseLeft", 48.f * i, 0.f,
			48.f, 55.f);
	}
	GetSceneResource()->SetColorKey("BasicDownReverseLeft", 13, 72, 7);

	//////FullSpeed
	//FSpdUp
	GetSceneResource()->CreateAnimationSequence("FullSpdAngledRight",
		"FullSpdAngledRight", TEXT("Character/Sonic/FullSpdAngled/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FullSpdAngledRight", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FullSpdAngledRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FullSpdAngledLeft",
		"FullSpdAngledLeft", TEXT("Character/Sonic/FullSpdAngled/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FullSpdAngledLeft", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FullSpdAngledLeft", 13, 72, 7);

	//FSpdDown
	GetSceneResource()->CreateAnimationSequence("FullSpdDownRight",
		"FullSpdDownRight", TEXT("Character/Sonic/FullSpdDown/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FullSpdDownRight", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FullSpdDownRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FullSpdDownLeft",
		"FullSpdDownLeft", TEXT("Character/Sonic/FullSpdDown/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FullSpdDownLeft", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FullSpdDownLeft", 13, 72, 7);

	//FSpdUpReverse
	GetSceneResource()->CreateAnimationSequence("FSpdUpReverseRight",
		"FSpdUpReverseRight", TEXT("Character/Sonic/FSpdUpReverse/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FSpdUpReverseRight", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FSpdUpReverseRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FSpdUpReverseLeft",
		"FSpdUpReverseLeft", TEXT("Character/Sonic/FSpdUpReverse/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FSpdUpReverseLeft", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FSpdUpReverseLeft", 13, 72, 7);

	//FSpdDownReverse
	GetSceneResource()->CreateAnimationSequence("FSpdDownReverseRight",
		"FSpdDownReverseRight", TEXT("Character/Sonic/FSpdDownReverse/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FSpdDownReverseRight", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FSpdDownReverseRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FSpdDownReverseLeft",
		"FSpdDownReverseLeft", TEXT("Character/Sonic/FSpdDownReverse/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FSpdDownReverseLeft", 48.f * i, 0.f,
			48.f, 51.f);
	}
	GetSceneResource()->SetColorKey("FSpdDownReverseLeft", 13, 72, 7);

	//Clear
	GetSceneResource()->CreateAnimationSequence("ClearSonic",
		"ClearSonic", TEXT("Character/Sonic/Clear.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("ClearSonic", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("ClearSonic", 13, 72, 7);

	/////////////////////////SONIC ANIMATION END/////////////////////////

	/////////////////////////RhinoBot ANIMATION START/////////////////////////

	//Idle
	GetSceneResource()->CreateAnimationSequence("RihnoRightIdle",
		"RihnoRightIdle", TEXT("Monster/RihnoBot/RightIdle.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("RihnoRightIdle", 0.f, 0.f,
		48.f, 32.f);
	GetSceneResource()->SetColorKey("RihnoRightIdle", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("RihnoLeftIdle",
		"RihnoLeftIdle", TEXT("Monster/RihnoBot/LeftIdle.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("RihnoLeftIdle", 0.f, 0.f,
		48.f, 32.f);
	GetSceneResource()->SetColorKey("RihnoLeftIdle", 13, 72, 7);

	//Move
	GetSceneResource()->CreateAnimationSequence("RihnoRightMove",
		"RihnoRightMove", TEXT("Monster/RihnoBot/Move/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RihnoRightMove", 56.f * i, 0.f,
			56.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RihnoRightMove", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("RihnoLeftMove",
		"RihnoLeftMove", TEXT("Monster/RihnoBot/Move/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RihnoLeftMove", 56.f * i, 0.f,
			56.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RihnoLeftMove", 13, 72, 7);

	//Turn
	GetSceneResource()->CreateAnimationSequence("RihnoRightTurn",
		"RihnoRightTurn", TEXT("Monster/RihnoBot/Turn/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RihnoRightTurn", 40.f * i, 0.f,
			40.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RihnoRightTurn", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("RihnoLeftTurn",
		"RihnoLeftTurn", TEXT("Monster/RihnoBot/Turn/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RihnoLeftTurn", 40.f * i, 0.f,
			40.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RihnoLeftTurn", 13, 72, 7);
	
	/////////////////////////RhinoBot ANIMATION END/////////////////////////

	/////////////////////////Tulippon ANIMATION START/////////////////////////
	//Idle
	GetSceneResource()->CreateAnimationSequence("TulipponIdle",
		"TulipponIdle", TEXT("Monster/Tulippon/Idle.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("TulipponIdle", 0.f, 0.f,
		48.f, 48.f);
	GetSceneResource()->SetColorKey("TulipponIdle", 13, 72, 7);

	//FireBomb
	GetSceneResource()->CreateAnimationSequence("TulipponFireThorn",
		"TulipponFireThorn", TEXT("Monster/Tulippon/FireThorn.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("TulipponFireThorn", 48.f * i, 0.f,
			48.f, 56.f);
	}
	GetSceneResource()->SetColorKey("TulipponFireThorn", 13, 72, 7);
	/////////////////////////Tulippon ANIMATION END/////////////////////////



	/////////////////////////MapObject ANIMATION START/////////////////////////
	
	////Spring Yellow
	GetSceneResource()->CreateAnimationSequence("SpringYellowIdle",
		"SpringYellowIdle", TEXT("Stage1/MapObject/Spring/Yellow.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SpringYellowIdle", 32.f, 0.f,
		32.f, 16.f);
	GetSceneResource()->SetColorKey("SpringYellowIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("SpringYellowBounce",
		"SpringYellowBounce", TEXT("Stage1/MapObject/Spring/Yellow.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SpringYellowBounce", 32.f * i, 0.f,
			32.f, 16.f);
	}
	GetSceneResource()->SetColorKey("SpringYellowBounce", 255, 0, 255);

	////Spring Yellow Left
	GetSceneResource()->CreateAnimationSequence("LeftYellowIdle",
		"LeftYellowIdle", TEXT("Stage1/MapObject/Spring/YellowLeft.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("LeftYellowIdle", 16.f, 0.f,
		16.f, 32.f);
	GetSceneResource()->SetColorKey("LeftYellowIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("LeftYellowBounce",
		"LeftYellowBounce", TEXT("Stage1/MapObject/Spring/YellowLeft.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftYellowBounce", 16.f * i, 0.f,
			16.f, 32.f);
	}
	GetSceneResource()->SetColorKey("LeftYellowBounce", 255, 0, 255);

	////Spring Yellow Right
	GetSceneResource()->CreateAnimationSequence("RightYellowIdle",
		"RightYellowIdle", TEXT("Stage1/MapObject/Spring/YellowRight.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("RightYellowIdle", 16.f, 0.f,
		16.f, 32.f);
	GetSceneResource()->SetColorKey("RightYellowIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("RightYellowBounce",
		"RightYellowBounce", TEXT("Stage1/MapObject/Spring/YellowRight.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightYellowBounce", 32.f * i, 0.f,
			16.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RightYellowBounce", 255, 0, 255);


	////Spring Red
	GetSceneResource()->CreateAnimationSequence("SpringRedIdle",
		"SpringRedIdle", TEXT("Stage1/MapObject/Spring/Red.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SpringRedIdle", 32.f, 0.f,
		32.f, 32.f);
	GetSceneResource()->SetColorKey("SpringRedIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("SpringRedBounce",
		"SpringRedBounce", TEXT("Stage1/MapObject/Spring/Red.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SpringRedBounce", 32.f * i, 0.f,
			32.f, 32.f);
	}
	GetSceneResource()->SetColorKey("SpringRedBounce", 255, 0, 255);


	////Spring Red Left
	GetSceneResource()->CreateAnimationSequence("LeftRedIdle",
		"LeftRedIdle", TEXT("Stage1/MapObject/Spring/RedLeft.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("LeftRedIdle", 32.f, 0.f,
		32.f, 32.f);
	GetSceneResource()->SetColorKey("LeftRedIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("LeftRedBounce",
		"LeftRedBounce", TEXT("Stage1/MapObject/Spring/RedLeft.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftRedBounce", 32.f * i, 0.f,
			32.f, 32.f);
	}
	GetSceneResource()->SetColorKey("LeftRedBounce", 255, 0, 255);


	//Spring Red Right
	GetSceneResource()->CreateAnimationSequence("RightRedIdle",
		"RightRedIdle", TEXT("Stage1/MapObject/Spring/RedRight.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("RightRedIdle", 32.f, 0.f,
		32.f, 32.f);
	GetSceneResource()->SetColorKey("RightRedIdle", 255, 0, 255);

	//Bounce
	GetSceneResource()->CreateAnimationSequence("RightRedBounce",
		"RightRedBounce", TEXT("Stage1/MapObject/Spring/RedRight.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightRedBounce", 32.f * i, 0.f,
			32.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RightRedBounce", 255, 0, 255);


	////Ring
	GetSceneResource()->CreateAnimationSequence("RingIdle",
		"RingIdle", TEXT("CommonObject/Ring.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RingIdle", 32.f * i, 0.f,
			32.f, 32.f);
	}
	GetSceneResource()->SetColorKey("RingIdle", 255, 0, 255);

	//RingEffect
	GetSceneResource()->CreateAnimationSequence("RingEffect",
		"RingEffect", TEXT("CommonObject/RingEffect.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RingEffect", 16.f * i, 0.f,
			16.f, 14.f);
	}
	GetSceneResource()->SetColorKey("RingEffect", 255, 0, 255);
	
	//BoardSpin
	GetSceneResource()->CreateAnimationSequence("BoardSpin",
		"BoardSpin", TEXT("Stage1/MapObject/BoardSpin.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 3; ++i)
	{
		GetSceneResource()->AddAnimationFrame("BoardSpin", 32.f * i, 0.f,
			32.f, 48.f);
	}
	GetSceneResource()->SetColorKey("BoardSpin", 255, 0, 255);

	//SpinBoard
	GetSceneResource()->CreateAnimationSequence("SpinBoard",
		"SpinBoard", TEXT("Stage1/MapObject/SpinBoard.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("SpinBoard", 0.f, 0.f,
		48.f, 48.f);
	GetSceneResource()->SetColorKey("SpinBoard", 255, 0, 255);

	/////////////////////////MapObject ANIMATION END/////////////////////////


	/////////////////////////Effect ANIMATION START/////////////////////////

	////SpinDash Effect 
	GetSceneResource()->CreateAnimationSequence("RightSpinDashEffet",
		"RightSpinDashEffet", TEXT("Effect/SpinDash/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightSpinDashEffet", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("RightSpinDashEffet", 255, 0, 255);

	GetSceneResource()->CreateAnimationSequence("LeftSpinDashEffet",
		"LeftSpinDashEffet", TEXT("Effect/SpinDash/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 7; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftSpinDashEffet", 48.f * i, 0.f,
			48.f, 48.f);
	}
	GetSceneResource()->SetColorKey("LeftSpinDashEffet", 255, 0, 255);

	//Dust Effect
	GetSceneResource()->CreateAnimationSequence("DustEffect",
		"DustEffect", TEXT("Effect/Dust.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("DustEffect", 16.f * i, 0.f,
			16.f, 16.f);
	}
	GetSceneResource()->SetColorKey("DustEffect", 255, 0, 255);



	//Small Bomb
	GetSceneResource()->CreateAnimationSequence("SmallBombEffet",
		"SmallBombEffet", TEXT("Effect/SmallBomb.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("SmallBombEffet", 32.f * i, 0.f,
			32.f, 32.f);
	}
	GetSceneResource()->SetColorKey("SmallBombEffet", 255, 0, 255);


	/////////////////////////Effect ANIMATION END/////////////////////////

	/////////////////////////Boss ANIMATION START/////////////////////////

	////EggFire
	//Idle
	GetSceneResource()->CreateAnimationSequence("EFBodyRightIdle",
		"EFBodyRightIdle", TEXT("Monster/Boss/EggFire/Body/IdleRight.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFBodyRightIdle", 0.f, 0.f,
		112.f, 64.f);	
	GetSceneResource()->SetColorKey("EFBodyRightIdle", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("EFBodyLeftIdle",
		"EFBodyLeftIdle", TEXT("Monster/Boss/EggFire/Body/IdleLeft.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFBodyLeftIdle", 0.f, 0.f,
		112.f, 64.f);
	GetSceneResource()->SetColorKey("EFBodyLeftIdle", 13, 72, 7);

	//Attack Angle
	GetSceneResource()->CreateAnimationSequence("RightAttackBasic",
		"RightAttackBasic", TEXT("Monster/Boss/EggFire/Body/AttackBasic/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightAttackBasic", 112.f * i, 0.f,
			112.f, 64.f);
	}
	GetSceneResource()->SetColorKey("RightAttackBasic", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("LeftAttackBasic",
		"LeftAttackBasic", TEXT("Monster/Boss/EggFire/Body/AttackBasic/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 5; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftAttackBasic", 112.f * i, 0.f,
			112.f, 64.f);
	}
	GetSceneResource()->SetColorKey("LeftAttackBasic", 13, 72, 7);

	//Attack Down
	GetSceneResource()->CreateAnimationSequence("RightAttackDown",
		"RightAttackDown", TEXT("Monster/Boss/EggFire/Body/AttackDown/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("RightAttackDown", 112.f * i, 0.f,
			112.f, 64.f);
	}
	GetSceneResource()->SetColorKey("RightAttackDown", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("LeftAttackDown",
		"LeftAttackDown", TEXT("Monster/Boss/EggFire/Body/AttackDown/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("LeftAttackDown", 112.f * i, 0.f,
			112.f, 64.f);
	}
	GetSceneResource()->SetColorKey("LeftAttackDown", 13, 72, 7);

	//Head Idle
	GetSceneResource()->CreateAnimationSequence("EFHeadRightIdle",
		"EFHeadRightIdle", TEXT("Monster/Boss/EggFire/Head/IdleRight.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFHeadRightIdle", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFHeadRightIdle", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("EFHeadLeftIdle",
		"EFHeadLeftIdle", TEXT("Monster/Boss/EggFire/Head/IdleLeft.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFHeadLeftIdle", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFHeadLeftIdle", 13, 72, 7);
	
	//Head Hurt
	GetSceneResource()->CreateAnimationSequence("EFHurtRight",
		"EFHurtRight", TEXT("Monster/Boss/EggFire/Head/HurtRight.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFHurtRight", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFHurtRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("EFHurtLeft",
		"EFHurtLeft", TEXT("Monster/Boss/EggFire/Head/HurtLeft.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFHurtLeft", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFHurtLeft", 13, 72, 7);
	
	//Die
	GetSceneResource()->CreateAnimationSequence("EFDieRight",
		"EFDieRight", TEXT("Monster/Boss/EggFire/Die/Right.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFDieRight", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFDieRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("EFDieLeft",
		"EFDieLeft", TEXT("Monster/Boss/EggFire/Die/Left.bmp"), TEXTURE_PATH);
	GetSceneResource()->AddAnimationFrame("EFDieLeft", 0.f, 0.f,
		56.f, 24.f);
	GetSceneResource()->SetColorKey("EFDieLeft", 13, 72, 7);

	//Fire Angle 
	GetSceneResource()->CreateAnimationSequence("FireAngleRight",
		"FireAngleRight", TEXT("Monster/Boss/EggFire/Fire/Angle/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FireAngleRight", 40.f * i, 0.f,
			40.f, 40.f);
	}
	GetSceneResource()->SetColorKey("FireAngleRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FireAngleLeft",
		"FireAngleLeft", TEXT("Monster/Boss/EggFire/Fire/Angle/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 4; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FireAngleLeft", 40.f * i, 0.f,
			40.f, 40.f);
	}
	GetSceneResource()->SetColorKey("FireAngleLeft", 13, 72, 7);

	//Fire Ground
	GetSceneResource()->CreateAnimationSequence("FireGroundRight",
		"FireGroundRight", TEXT("Monster/Boss/EggFire/Fire/Ground/Right.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FireGroundRight", 48.f * i, 0.f,
			48.f, 24.f);
	}
	GetSceneResource()->SetColorKey("FireGroundRight", 13, 72, 7);

	GetSceneResource()->CreateAnimationSequence("FireGroundLeft",
		"FireGroundLeft", TEXT("Monster/Boss/EggFire/Fire/Ground/Left.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FireGroundLeft", 48.f * i, 0.f,
			48.f, 24.f);
	}
	GetSceneResource()->SetColorKey("FireGroundLeft", 13, 72, 7);

	//Fire Down
	GetSceneResource()->CreateAnimationSequence("FireDown",
		"FireDown", TEXT("Monster/Boss/EggFire/Fire/Down.bmp"), TEXTURE_PATH);
	for (int i = 0; i < 2; ++i)
	{
		GetSceneResource()->AddAnimationFrame("FireDown", 24.f * i, 0.f,
			24.f, 48.f);
	}
	GetSceneResource()->SetColorKey("FireDown", 13, 72, 7);

	/////////////////////////Boss ANIMATION END/////////////////////////
}


void CMainScene::Cam1Key()
{
	GetCamera()->SetTarget(m_Player);
}

void CMainScene::Cam2Key()
{
	if (m_DEBUG)
		m_DEBUG = false;
	else if (!m_DEBUG)
		m_DEBUG = true;
}
