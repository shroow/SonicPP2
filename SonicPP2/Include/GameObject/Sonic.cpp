#include "Sonic.h"
#include "../Input.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Collision/CollisionManager.h"
#include "../Widget/CharacterHUD.h"
#include "SpinDash.h"
#include "Dust.h"

CSonic::CSonic() :
	m_CheckInput{false}
{
	SetTypeID<CSonic>();
}

CSonic::CSonic(const CSonic& Obj) :
	CCharacter(Obj)
{
}

CSonic::~CSonic()
{
}

void CSonic::SetClear()
{
	m_Board = true;
}

bool CSonic::Init()
{
	CGameObject::Init();

	m_MoveSpeed = 0.f;
	m_MaxSpeed = 500.f;
	m_HitSpeed = 0.f;
	m_Ground = false;
	m_Jump = false;
	m_Crouching = false;
	m_Rolling = false;
	m_JumpRolling = false;
	m_Stopping= false;
	m_LookingUp = false;
	m_Bounce = false;
	m_Board = false;
	m_Bottom = false;
	m_HitCount = 0;
	m_RingCount = 0;
	m_SpinDash = 0;
	m_CharDir = { 1.f, 0.f };
	m_Hit = true;
	m_Boss = false;

	SetJumpVelocity(55.f);

	SetPos(120.f, 570.f);
	SetSize(40.f, 40.f);
	SetPivot(0.5f, 0.5f);

	//SetAnimation
	{
		CreateAnimation();
		AddAnimation("SonicRightIdle", false);
		AddAnimation("SonicLeftIdle", false);
		AddAnimation("SonicRightBoard", true, 2.f);
		AddAnimation("SonicLeftBoard", true, 2.f);
		AddAnimation("SonicRightWalk");
		AddAnimation("SonicLeftWalk");
		AddAnimation("SonicRightFullSpeed", true, 0.4f);
		AddAnimation("SonicLeftFullSpeed", true, 0.4f);
		AddAnimation("SonicRightStop", false, 0.7f);
		AddAnimation("SonicLeftStop", false, 0.7f);
		AddAnimation("SonicRightRolling", true, 0.7f);
		AddAnimation("SonicLeftRolling", true, 0.7f);
		AddAnimation("SonicRightSpinDash", true, 0.7f);
		AddAnimation("SonicLeftSpinDash", true, 0.7f);
		AddAnimation("SonicRightLookingUp", false, 0.5f);
		AddAnimation("SonicLeftLookingUp", false, 0.5f);
		AddAnimation("SonicRightCrouching", false, 0.5f);
		AddAnimation("SonicLeftCrouching", false, 0.5f);
		AddAnimation("SonicRightBounceUp", false);
		AddAnimation("SonicLeftBounceUp", false);
		AddAnimation("SonicRightPush");
		AddAnimation("SonicLeftPush");
		AddAnimation("SonicRightHit");
		AddAnimation("SonicLeftHit");

		AddAnimation("ClearSonic", false, 1.2f);
		
		///Angled
		AddAnimation("BasicUpRight");
		AddAnimation("BasicUpLeft");
		AddAnimation("BasicDownRight");
		AddAnimation("BasicDownLeft");
		AddAnimation("BasicUpReverseRight");
		AddAnimation("BasicUpReverseLeft");
		AddAnimation("BasicDownReverseRight");
		AddAnimation("BasicDownReverseLeft");

		AddAnimation("FullSpdAngledRight", true, 0.4f);
		AddAnimation("FullSpdAngledLeft", true, 0.4f);
		AddAnimation("FullSpdDownRight", true, 0.4f);
		AddAnimation("FullSpdDownLeft", true, 0.4f);
		AddAnimation("FSpdUpReverseRight", true, 0.4f);
		AddAnimation("FSpdUpReverseLeft", true, 0.4f);
		AddAnimation("FSpdDownReverseRight", true, 0.4f);
		AddAnimation("FSpdDownReverseLeft", true, 0.4f);

		SetEndFunction<CSonic>("SonicRightStop", this, &CSonic::StopMove);
		SetEndFunction<CSonic>("SonicLeftStop", this, &CSonic::StopMove);

		AddNotify<CSonic>("SonicRightStop", 0,  this, &CSonic::StartStop);
		AddNotify<CSonic>("SonicRightStop", 0, this, &CSonic::StartStop);

		//	SetEndFunction<CSonic>("SonicRightStand", this, &CSonic::Board);
		//	SetEndFunction<CSonic>("SonicLeftStand", this, &CSonic::Board);

		//	AddNotify<CSonic>("SonicRightStop", 4, this, &CSonic::StopMove);
		//	AddNotify<CSonic>("SonicLeftStop", 4, this, &CSonic::StopMove);

		//Right
		m_vecSequenceKey[0].push_back("SonicRightIdle");
		m_vecSequenceKey[0].push_back("SonicRightWalk");
		m_vecSequenceKey[0].push_back("SonicRightFullSpeed");
		m_vecSequenceKey[0].push_back("SonicRightStop");
		m_vecSequenceKey[0].push_back("SonicRightRolling");

		m_vecSequenceKey[0].push_back("SonicRightCrouching");
		m_vecSequenceKey[0].push_back("SonicRightSpinDash");
		m_vecSequenceKey[0].push_back("SonicRightLookingUp");
		m_vecSequenceKey[0].push_back("SonicRightBoard");
		m_vecSequenceKey[0].push_back("SonicRightBounceUp");

		m_vecSequenceKey[0].push_back("SonicRightPush");
		m_vecSequenceKey[0].push_back("SonicRightHit");
		m_vecSequenceKey[0].push_back("BasicUpRight"); //Angled
		m_vecSequenceKey[0].push_back("BasicDownRight");
		m_vecSequenceKey[0].push_back("BasicUpReverseRight");

		m_vecSequenceKey[0].push_back("BasicDownReverseRight");
		m_vecSequenceKey[0].push_back("FullSpdAngledRight");
		m_vecSequenceKey[0].push_back("FullSpdDownRight");
		m_vecSequenceKey[0].push_back("FSpdUpReverseRight");
		m_vecSequenceKey[0].push_back("FSpdDownReverseRight");



		//Left
		m_vecSequenceKey[1].push_back("SonicLeftIdle");
		m_vecSequenceKey[1].push_back("SonicLeftWalk");
		m_vecSequenceKey[1].push_back("SonicLeftFullSpeed");
		m_vecSequenceKey[1].push_back("SonicLeftStop");
		m_vecSequenceKey[1].push_back("SonicLeftRolling");

		m_vecSequenceKey[1].push_back("SonicLeftCrouching");
		m_vecSequenceKey[1].push_back("SonicLeftSpinDash");
		m_vecSequenceKey[1].push_back("SonicLeftLookingUp");
		m_vecSequenceKey[1].push_back("SonicLeftBoard");
		m_vecSequenceKey[1].push_back("SonicLeftBounceUp");

		m_vecSequenceKey[1].push_back("SonicLeftPush");
		m_vecSequenceKey[1].push_back("SonicLeftHit");
		m_vecSequenceKey[1].push_back("BasicDownLeft");
		m_vecSequenceKey[1].push_back("BasicUpLeft"); //Angled
		m_vecSequenceKey[1].push_back("BasicDownReverseLeft");

		m_vecSequenceKey[1].push_back("BasicUpReverseLeft");
		m_vecSequenceKey[1].push_back("FullSpdDownLeft");
		m_vecSequenceKey[1].push_back("FullSpdAngledLeft");
		m_vecSequenceKey[1].push_back("FSpdDownReverseLeft");
		m_vecSequenceKey[1].push_back("FSpdUpReverseLeft");
	}

	CColliderBox* Box = AddCollider<CColliderBox>("Player");
	
	Box->SetExtent(40.f, 40.f);
	Box->SetOffset(0.f, 4.f);
	Box->SetCollisionProfile("Player");

	Box->SetCollisionBeginFunction<CSonic>(this, &CSonic::CollisionBegin);
	Box->SetCollisionOnFunction<CSonic>(this, &CSonic::CollisionOn);
	Box->SetCollisionEndFunction<CSonic>(this, &CSonic::CollisionEnd);
	
	//SetInput
	{
		CInput::GetInst()->AddBindFunction<CSonic>("MoveRight",
			Input_Type::Down, this, &CSonic::StartMoveRight, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveRight",
			Input_Type::Push, this, &CSonic::MoveRight, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveRight",
			Input_Type::Up, this, &CSonic::EndMoveRight, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveLeft",
			Input_Type::Down, this, &CSonic::StartMoveLeft, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveLeft",
			Input_Type::Push, this, &CSonic::MoveLeft, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveLeft",
			Input_Type::Up, this, &CSonic::EndMoveLeft, m_Scene);

		CInput::GetInst()->AddBindFunction<CSonic>("MoveUp",
			Input_Type::Down, this, &CSonic::StartMoveUp, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveUp",
			Input_Type::Push, this, &CSonic::MoveUp, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveUp",
			Input_Type::Up, this, &CSonic::EndMoveUp, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveDown",
			Input_Type::Down, this, &CSonic::StartMoveDown, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveDown",
			Input_Type::Push, this, &CSonic::MoveDown, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("MoveDown",
			Input_Type::Up, this, &CSonic::EndMoveDown, m_Scene);

		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey",
			Input_Type::Down, this, &CSonic::StartJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey1",
			Input_Type::Down, this, &CSonic::StartJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey2",
			Input_Type::Down, this, &CSonic::StartJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey3",
			Input_Type::Down, this, &CSonic::StartJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey",
			Input_Type::Push, this, &CSonic::Jumpkey, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey1",
			Input_Type::Push, this, &CSonic::Jumpkey1, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey2",
			Input_Type::Push, this, &CSonic::Jumpkey2, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey3",
			Input_Type::Push, this, &CSonic::Jumpkey3, m_Scene);

		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey1",
			Input_Type::Up, this, &CSonic::EndJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey2",
			Input_Type::Up, this, &CSonic::EndJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("Jumpkey3",
			Input_Type::Up, this, &CSonic::EndJump, m_Scene);
		CInput::GetInst()->AddBindFunction<CSonic>("EnterKey",
			Input_Type::Down, this, &CSonic::EnterKey, m_Scene);
	}

	SetPhysicsSimulate(true);
	SetSideWallCheck(true);

	m_SpinEffect = m_Scene->CreateObject<CSpinDash>("Spin");

	return true;
}

void CSonic::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Board)
		return;

	if (m_Hit && m_Ground)
		m_Hit = false;

	if (m_Rolling && m_Jump && !m_Bounce)
		m_JumpRolling = true;

	//m_Push 초기화
	if (m_Push && m_Move.x || m_Jump)
		m_Push = false;

	//링 갯수 정해주기
	m_Scene->FindWidget<CCharacterHUD>("CharacterHUD")->SetRing(m_RingCount);


	if (m_CheckInput[0] == false && m_CheckInput[1] == false)
	{
		m_MoveSpeed -= 300 * DELTA_TIME * m_TimeScale;
		if (m_MoveSpeed <= 0.f)
			m_MoveSpeed = 0.f;
	}

	//IsAngle
	if (m_IsAngle)
	{
		MoveAngle(m_CharDir.x);
	}
	else
	{
		m_Pos += m_HitSpeed + m_CharDir * m_MoveSpeed * DELTA_TIME * m_TimeScale;
	}
}

void CSonic::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);

	if (m_Board)
	{
		ChangeAnimation("ClearSonic");
		return;
	}

	if (m_Pos.x >= 7803.f && !m_Boss)
	{
		m_Boss = true;
		m_Scene->GetSceneResource()->SoundStop("STAGE1ACT1BGM");
		m_Scene->GetSceneResource()->SoundPlay("Boss");
	}
	/*
	 Vector2 zero = { 0, 10 };
	 Vector2 A = { 20, 0 };
	 Vector2 B = { 30, 40 };

	 float lengthA = zero.Distance(A);
	 float lengthB = zero.Distance(B);
	 Vector2 Result;
	 float zeroToA = zero.Angle(A);
	 float zeroToB = zero.Angle(B);

	 Result.x = zero.x + cosf(DegreeToRadian(zeroToA)) * lengthA;
	 Result.y = zero.y + sinf(DegreeToRadian(zeroToA)) * lengthA;

	 MoveToEx(m_hDC, (int)zero.x, (int)zero.y, nullptr);
	 LineTo(m_hDC, (int)Result.x, (int)Result.y);
	 */

	int	AnimDirIndex = 0;

	if (m_CharDir.x == -1.f)
		AnimDirIndex = 1;

	if (m_Hit)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][11]);

	else if (m_Bounce)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][9]);

	else if (m_Push)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][10]);

	else if (m_Rolling)
	{
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][4]);

		if (m_JumpRolling & m_Ground)
		{
			m_Rolling = false;
			m_JumpRolling = false;
		}
		
		if (m_MoveSpeed == 0.f)
			m_Rolling = false;
	}
	else if (m_Stopping)
		ChangeAnimation(m_vecSequenceKey[AnimDirIndex][3]);

	else if (m_MoveSpeed > 0.f && m_IsAngle)
	{
		if (m_Angle >= 25.f && m_Angle <= 90.f)
		{
			if (m_MoveSpeed >= m_MaxSpeed)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][17]);
			else if (m_MoveSpeed < m_MaxSpeed)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][13]);
		}

		else if (m_Angle >= 270.f && m_Angle <= 335.f)
		{
			//LUpRDown
			if (m_MoveSpeed >= m_MaxSpeed)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][16]);
			else if (m_MoveSpeed < m_MaxSpeed)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][12]);
		}
		else
		{
			if (m_Bounce)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][9]);
			else if (m_Jump)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][4]);
			else
			{
				if (m_MoveSpeed >= m_MaxSpeed)
					ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
				else if (m_MoveSpeed < m_MaxSpeed)
					ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
			}
		}
	}

	else if (m_SetMoveRound && !m_PhysicsSimulate)
	{
		if (m_MoveRoundDir == 1.f)
		{
			if (m_MoveRoundAngle <= 90.f && m_MoveRoundAngle >= 0.f)
				ChangeAnimation(m_vecSequenceKey[0][16]);

			else if (m_MoveRoundAngle >= 270.f && m_MoveRoundAngle <= 360.f)
				ChangeAnimation(m_vecSequenceKey[0][14]);
			
			else if (m_MoveRoundAngle >= 180.f && m_MoveRoundAngle < 270.f)
				ChangeAnimation(m_vecSequenceKey[0][19]);

			else if (m_MoveRoundAngle < 180.f && m_MoveRoundAngle > 90.f)
				ChangeAnimation(m_vecSequenceKey[0][17]);

			else
				ChangeAnimation(m_vecSequenceKey[0][16]);
		}
		
		else if (m_MoveRoundDir == -1.f)
		{
			if (m_MoveRoundAngle > 90.f && m_MoveRoundAngle <= 180.f)
				ChangeAnimation(m_vecSequenceKey[1][17]);

			else if (m_MoveRoundAngle > 180.f && m_MoveRoundAngle <= 270.f)
				ChangeAnimation(m_vecSequenceKey[1][15]);

			else if (m_MoveRoundAngle > 270.f && m_MoveRoundAngle <= 360.f)
				ChangeAnimation(m_vecSequenceKey[1][18]);

			else if (m_MoveRoundAngle >= 0.f && m_MoveRoundAngle <= 90.f)
				ChangeAnimation(m_vecSequenceKey[1][16]);

			else
				ChangeAnimation(m_vecSequenceKey[1][16]);
		}
	}
	else if (m_MoveSpeed > 0.f)
	{
		if (m_MoveSpeed >= m_MaxSpeed)
		{
			if(m_Bounce)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][9]);
			else if (m_Jump)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][4]);
			else
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][2]);
		}
		else if (m_MoveSpeed < m_MaxSpeed)
		{
			if (m_Bounce)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][9]);
			else if (m_Jump)
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][4]);
			else
				ChangeAnimation(m_vecSequenceKey[AnimDirIndex][1]);
		}
	}

	else
	{
		if (m_Jump)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][4]);
		
		else if (m_SpinDash)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][6]);
		
		else if (m_Crouching)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][5]);
		
		else if (m_LookingUp)
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][7]);
		
		else
			ChangeAnimation(m_vecSequenceKey[AnimDirIndex][0]);
		
	}
}

void CSonic::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CSonic::StartMoveRight()
{
	m_CheckInput[(int)EPlayer_Input::Right] = true;

	if (m_SpinDash)
		return;

	if (m_CharDir.x == 1.f)
	{
		m_CharDir.x = 1.f;
	}
	else if (m_CharDir.x == -1)
	{
		if (m_MoveSpeed >= 300.f)
		{
			if (m_Ground && m_MoveSpeed > 100.f)
			{
				m_Stopping = true;
				CDust* Dust1 = m_Scene->CreateObject<CDust>("Dust");
				Dust1->SetPos(m_Pos.x, m_Pos.y + 17.f);

				CDust* Dust2 = m_Scene->CreateObject<CDust>("Dust");
				Dust2->SetPos(m_Pos.x + 7.f, m_Pos.y + 17.f);

				m_Scene->GetSceneResource()->SoundPlay("SonicStopping");
			}

			m_MoveSpeed -= 300.f;
			if (m_MoveSpeed < 0.f)
			{
				m_MoveSpeed = 0.f;
				m_CharDir = 1.f;
				m_Stopping = false;

				if (m_Rolling)
					m_Rolling = false;
			}
		}

		else if (m_MoveSpeed < 300.f)
		{
			m_MoveSpeed = 30.f;
			m_CharDir.x = 1.f;
			m_Stopping = false;

			if (m_Rolling)
				m_Rolling = false;
		}
	}
}

void CSonic::MoveRight()
{
	if (m_SpinDash)
		return;

	if (m_SetMoveRound)
	{
		if (m_MoveRoundAngle <= 340.f && m_MoveRoundAngle >= 250.f)
			m_MoveRoundAngle -= 200.f * DELTA_TIME;
		else
			m_MoveRoundAngle -= 330.f * DELTA_TIME;

		if (m_MoveRoundAngle < 0.f)
			m_MoveRoundAngle += 360.f;


		if(MoveRound(m_MoveRoundPos, 1.f))
			return;
	}

	if (m_CharDir.x == 1.f)
	{
		m_MoveSpeed += 300.f * DELTA_TIME;
		if (m_MoveSpeed >= m_MaxSpeed)
			m_MoveSpeed = m_MaxSpeed;
	}
	else if (m_CharDir.x == -1.f)
	{
		if (m_Ground && m_MoveSpeed > 100.f)
			m_Stopping = true;


		if (m_Rolling)
			m_Rolling = false;

		m_MoveSpeed -= 300 * DELTA_TIME;
		if (m_MoveSpeed <= 10.f)
		{
			m_CharDir.x = 1.f;
			m_Stopping = false;
		}
	}
}

void CSonic::EndMoveRight()
{
	m_CheckInput[(int)EPlayer_Input::Right] = false;
}

void CSonic::StartMoveLeft()
{
	m_CheckInput[(int)EPlayer_Input::Left] = true;
	
	if (m_SpinDash)
		return;

	if (m_CharDir.x == -1.f)
	{
		m_CharDir.x = -1.f;
	}
	else if (m_CharDir.x == 1)
	{
		if (m_MoveSpeed >= 300.f)
		{
			if (m_Ground && m_MoveSpeed > 100.f)
			{
				m_Stopping = true;
				CDust* Dust1 = m_Scene->CreateObject<CDust>("Dust");
				Dust1->SetPos(m_Pos.x, m_Pos.y + 17.f);

				CDust* Dust2 = m_Scene->CreateObject<CDust>("Dust");
				Dust2->SetPos(m_Pos.x - 7.f, m_Pos.y + 17.f);

				m_Scene->GetSceneResource()->SoundPlay("SonicStopping");
			}

			m_MoveSpeed -= 300.f;
			if (m_MoveSpeed < 0.f)
			{
				m_MoveSpeed = 0.f;
				m_CharDir = -1.f;
				m_Stopping = false;

				if (m_Rolling)
					m_Rolling = false;

			}
		}

		else if (m_MoveSpeed < 300.f)
		{
			m_MoveSpeed = 30.f;
			m_CharDir.x = -1.f;
			m_Stopping = false;

			if (m_Rolling)
				m_Rolling = false;
		}
	}
} 

void CSonic::MoveLeft()
{
	if (m_SpinDash)
		return;

	if (m_SetMoveRound)
	{
		if (m_MoveRoundAngle < 300.f && m_MoveRoundAngle > 205.f)
			m_MoveRoundAngle += 200.f * DELTA_TIME;
		else
			m_MoveRoundAngle += 330.f * DELTA_TIME;

		if (m_MoveRoundAngle > 360.f)
			m_MoveRoundAngle -= 360.f;


		if(MoveRound(m_MoveRoundPos, -1.f))
			return;
	}

	if (m_CharDir.x == -1.f)
	{
		m_MoveSpeed += 300.f * DELTA_TIME;
		if (m_MoveSpeed >= m_MaxSpeed)
			m_MoveSpeed = m_MaxSpeed;
	}
	else if (m_CharDir.x == 1.f)
	{
		if (m_Ground && m_MoveSpeed > 100.f)
			m_Stopping = true;


		if (m_Rolling)
			m_Rolling = false;

		m_MoveSpeed -= 300 * DELTA_TIME;
		if (m_MoveSpeed <= 10.f)
		{
			m_CharDir.x = -1.f;
			m_Stopping = false;
		}
	}
}

void CSonic::EndMoveLeft()
{
	m_CheckInput[(int)EPlayer_Input::Left] = false;

	if (m_SetMoveRound)
	{
		SetPhysicsSimulate(true);
	}
}

void CSonic::StartMoveUp()
{
	m_CheckInput[(int)EPlayer_Input::Up] = true;

	if (m_MoveSpeed == 0.f && m_Ground)
		m_LookingUp = true;
}

void CSonic::MoveUp()
{
	
}

void CSonic::EndMoveUp()
{
	m_CheckInput[(int)EPlayer_Input::Up] = false;

	
	m_LookingUp = false;
}

void CSonic::StartMoveDown()
{
	m_CheckInput[(int)EPlayer_Input::Down] = true;

}

void CSonic::MoveDown()
{
	if (m_Ground && m_MoveSpeed == 0.f)
		m_Crouching = true;
	else if (m_Ground && m_MoveSpeed > 100.f)
		m_Rolling = true;
}

void CSonic::EndMoveDown()
{
	m_CheckInput[(int)EPlayer_Input::Down] = false;
	
	m_Crouching = false;

	if (m_SpinDash != 0)
	{
		m_Rolling = true;
		m_MoveSpeed = 300.f * m_SpinDash;
		m_SpinDash = false;

		m_SpinEffect->SetEnable(false);
	}
}

void CSonic::StartJump()
{
	if (!m_Fall)
	{
		SonicJump();
		m_Fall = false;
	}
}

void CSonic::EndJump()
{
	//FIX
	//StartFall
	if (m_Jump && !m_Fall)
	{
		if (m_FallTime > 3.f)
			m_Fall = false;
		else
		{
			m_Fall = true;
			m_FallTime = 0.f;
			m_FallStartY = m_Pos.y;
		}
	}
}

void CSonic::Jumpkey()
{
}

void CSonic::Jumpkey1()
{
}

void CSonic::Jumpkey2()
{
}

void CSonic::Jumpkey3()
{
}

void CSonic::EnterKey()
{
	SetPos(7400, 725);

	//(5517.f, 550.f), (7550, 920)
} 

void CSonic::SetBottom(Vector2 Pos)
{
	m_Pos.x = Pos.x - m_Pivot.x * m_Size.x;
	m_Pos.y = Pos.y - m_Pivot.y * m_Size.y;
}

void CSonic::Crouching()
{
}

void CSonic::Spinning()
{
	m_SpinDash = true;
}

void CSonic::StartMove()
{
}

void CSonic::StartStop()
{
}

void CSonic::StopMove()
{

	m_Stopping = false;
}

void CSonic::SonicJump()
{
	if (m_SpinDash > 0)
	{
		if (m_SpinDash < 2)
			m_SpinDash++;
		m_Scene->GetSceneResource()->SoundPlay("SpinDash");
	}
	else if (m_Crouching)
	{
		m_SpinEffect->SetEnable(true);
		m_SpinEffect->SetDir(m_CharDir.x);
		m_SpinEffect->SetPos(m_Pos);

		Spinning();
		m_Scene->GetSceneResource()->SoundPlay("SpinDash");
	}
	else if (m_Ground)
	{
		m_Rolling = true;
		Jump();
		m_Scene->GetSceneResource()->SoundPlay("Jump");
	}
}

void CSonic::Board()
{
	m_Board = true;
}

bool CSonic::InflictDamage(bool Damage)
{

	return CCharacter::InflictDamage(Damage);
}

void CSonic::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
	if (m_Ground)
	{
		m_Bounce = true;
		m_Jump = true;
		m_Ground = false;
	}
}
//내적의 특징
//	동일한 벡터의 내적은 벡터의 길이의 제곱
//	
//단위 벡터 끼리의 내적은 두 벡터 간 각도의 코사인
//	결과값이 0이라면, 두 벡터는 직각이다.
//	결과값이 0보다 크다면 두 벡터간 각도는 예각이다.
//	결과값이 0보다 작다면 두 벡터간 각도는 둔각이다.
// 
//즉 단위 벡터 B와 내적한 결과는 벡터 A의 종점에서 아래로 수선을 
//	내렸을 때 형성되는 삼각형의 밑변 y가 된다는 의미가 된다.
void CSonic::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	//FIX
	//반사벡터를 이용해서 대각선으로 장애물에 부딪혔을 경우의 정확한 위치를 구하기
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		if (Dest->GetProfile()->Channel == ECollision_Channel::MapObject)
		{
			std::string Name = Dest->GetName();

			if (Name == "Ring")
			{
				++m_RingCount;
				m_Scene->GetSceneResource()->SoundPlay("RingGet");
				return;
			}

			else if (Name == "SpringUp")
			{
				Bounce();
				m_Scene->GetSceneResource()->SoundPlay("BounceUp");
				return;
			}
		}
		else if (Dest->GetProfile()->Channel == ECollision_Channel::Monster)
		{
			std::string Name = Dest->GetName();

			if (Name == "EggBossFire")
			{
				m_CharDir.x *= -1.f;
				m_Scene->GetSceneResource()->SoundPlay("Hit");
				return;
			}
		}


		if (Dest->GetProfile()->Channel == ECollision_Channel::TileMap)
		{
			//좌우이동
			if (m_Move.x != 0.f && m_SideWallCheck)
			{
				// 오른쪽으로 이동할때
				if (m_Move.x > 0.f)
				{
					Vector2	LT = m_Pos - m_Pivot * m_Size;
					Vector2	RB = LT + m_Size;

					Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
					Vector2	PrevRB = PrevLT + m_Size;

					Vector2	ResultLT, ResultRB;

					ResultRB = RB;

					ResultLT.x = PrevRB.x;
					ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

					ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;

					Vector2 BoxLT = Dest->GetPoint();
					Vector2 BoxRB = Dest->GetSize();
					if (BoxLT == -1.f || BoxRB == -1.f)
						break;

					///충돌체 위치까지 빼주기
					if (PrevLT.y < BoxRB.y && PrevRB.y > BoxLT.y)
					{
						m_Pos.x = BoxLT.x - (1.f - m_Pivot.x) * m_Size.x - 0.0001f;
						m_Move.x = 0.f;

						if (m_Ground)
							m_Push = true;
					}
				}

				// 왼쪽으로 이동할때
				else
				{
					Vector2	LT = m_Pos - m_Pivot * m_Size;
					Vector2	RB = LT + m_Size;

					Vector2	PrevLT = m_PrevPos - m_Pivot * m_Size;
					Vector2	PrevRB = PrevLT + m_Size;

					Vector2	ResultLT, ResultRB;

					ResultLT = LT;

					ResultLT.y = LT.y < PrevLT.y ? LT.y : PrevLT.y;

					ResultRB.x = PrevLT.x;
					ResultRB.y = RB.y > PrevRB.y ? RB.y : PrevRB.y;

					Vector2 BoxLT = Dest->GetPoint();
					Vector2 BoxRB = Dest->GetSize();
					if (BoxLT == -1.f || BoxRB == -1.f)
						break;

					///충돌체 위치까지 빼주기
					if (PrevLT.y < BoxRB.y && PrevRB.y > BoxLT.y )
					{
						m_Pos.x = BoxRB.x + (1.f - m_Pivot.x) * m_Size.x + 0.0001f;
						m_Move.x = 0.f;

						if (m_Ground)
							m_Push = true;
					}

				}
			}
			
			// 바닥에 착지시킨다.
			if (m_PhysicsSimulate && m_Move.y >= 0.f)
			{
				float	PrevBottom = m_PrevPos.y + (1.f - m_Pivot.y) * m_Size.y;
				float	CurBottom = m_Pos.y + (1.f - m_Pivot.y) * m_Size.y;

				float	PrevLeft = m_PrevPos.x - m_Pivot.x * m_Size.x;
				float	CurLeft = m_Pos.x - m_Pivot.x * m_Size.x;

				float	PrevRight = m_PrevPos.x + (1.f - m_Pivot.x) * m_Size.x;
				float	CurRight = m_Pos.x + (1.f - m_Pivot.x) * m_Size.x;

				float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
				float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
				float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
				float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

				Vector2 BoxLT = Dest->GetPoint();
				Vector2 BoxRB = Dest->GetSize();
				if (BoxLT == -1.f || BoxRB == -1.f)
					break;

				bool Check = false;

				///충돌체 위치까지 빼주기
				if (PrevBottom <= BoxLT.y)
				{
					//if (ResultLeft <= BoxLT.x + BoxRB.x &&
					//	ResultTop <= BoxLT.y + BoxRB.y &&
					//	ResultRight >= BoxLT.x &&
					//	ResultBottom >= BoxLT.y)

						Check = true;
						m_FallTime = 0.f;

						// 현재Top을 이 오브젝트의 Bottom값으로 지정한다.
						m_Pos.y = BoxLT.y - (1.f - m_Pivot.y) * m_Size.y;
						m_Ground = true;
						m_Jump = false;


				}
				// 바닥이 없을 경우
				if (!Check)
				{
					// 땅을 밟고 있던 상태라면 이제 떨어지는 상태가 될것이다.
					if (m_Ground)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_Pos.y;
					}

					m_Ground = false;
				}
			}							
			return;
		}
		return;

	case ECollider_Type::Line:
		if (m_PhysicsSimulate)
		{
			++m_HitCount;


			Vector2 StrPoint = Dest->GetPoint();
			Vector2 EndPoint = Dest->GetSize();

			float LineAngle = StrPoint.Angle(EndPoint);

			if(LineAngle >= 0.f && LineAngle <= 360.f) 
			{
				m_IsAngle = true;
				m_Angle = LineAngle;
			}
			// 바닥에 착지시킨다.
			if (m_Move.y >= 0.f)
			{
				bool Check = false;

				if (!m_Ground)
				{
					m_FallTime = 0.f;
					m_Ground = true;
					m_Jump = false;
				}
				// 바닥이 없을 경우
				if (!Check)
				{
					// 땅을 밟고 있던 상태라면 이제 떨어지는 상태가 될것이다.
					if (m_Ground && m_HitCount)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_Pos.y;
					}

					m_Ground = false;
				}
			}
			return;
		}
		return;
	case ECollider_Type::Circle:
		return;
	}
}

void CSonic::CollisionEnd(CCollider* Src, CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Line:
		if (m_HitCount)
		{
			--m_HitCount;

			if (!m_HitCount)
			{
				m_IsAngle = false;
				m_Angle = 0.f;
			}
		}
	}

}

void CSonic::CollisionOn(CCollider* Src, CCollider* Dest)
{
	//FIX
	//반사벡터를 이용해서 대각선으로 장애물에 부딪혔을 경우의 정확한 위치를 구하기
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		if (Dest->GetProfile()->Channel == ECollision_Channel::MapObject)
		{
			std::string Name = Dest->GetName();

			if (Name == "Ring")
			{
				return;
			}
		}

		if (Dest->GetProfile()->Channel == ECollision_Channel::TileMap)
		{
			if (m_PhysicsSimulate && m_Move.y >= 0.f)
			{
				float	PrevBottom = m_PrevPos.y + (1.f - m_Pivot.y) * m_Size.y;
				float	CurBottom = m_Pos.y + (1.f - m_Pivot.y) * m_Size.y;

				float	PrevLeft = m_PrevPos.x - m_Pivot.x * m_Size.x;
				float	CurLeft = m_Pos.x - m_Pivot.x * m_Size.x;

				float	PrevRight = m_PrevPos.x + (1.f - m_Pivot.x) * m_Size.x;
				float	CurRight = m_Pos.x + (1.f - m_Pivot.x) * m_Size.x;

				float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
				float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
				float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
				float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;

				Vector2 BoxLT = Dest->GetPoint();
				Vector2 BoxRB = Dest->GetSize();
				if (BoxLT == -1.f || BoxRB == -1.f)
					break;

				bool Check = false;

				///충돌체 위치까지 빼주기
				if (PrevBottom <= BoxLT.y)
				{
					Check = true;
					m_FallTime = 0.f;

					// 현재Top을 이 오브젝트의 Bottom값으로 지정한다.
					m_Pos.y = BoxLT.y - (1.f - m_Pivot.y) * m_Size.y;
					m_Ground = true;
					m_Jump = false;


				}
				// 바닥이 없을 경우
				if (!Check)
				{
					// 땅을 밟고 있던 상태라면 이제 떨어지는 상태가 될것이다.
					if (m_Ground)
					{
						m_FallTime = 0.f;
						m_FallStartY = m_Pos.y;
					}

					m_Ground = false;
				}
				return;
			}
		}
		return;

	case ECollider_Type::Line:		
		if (m_PhysicsSimulate)
		{
			if (m_HitCount < 0)
				return;

			ECollision_Channel mmmm = Dest->GetProfile()->Channel;

			Vector2 StrPoint = Dest->GetPoint();
			Vector2 EndPoint = Dest->GetSize();

			float LineLen = StrPoint.Distance(EndPoint);

			float	PrevBottom = m_PrevPos.y + (1.f - m_Pivot.y) * m_Size.y;
			float	CurBottom = m_Pos.y + (1.f - m_Pivot.y) * m_Size.y;

			float	PrevTop = m_PrevPos.y - (1.f - m_Pivot.y) * m_Size.y;
			float	CurTop = m_Pos.y - (1.f - m_Pivot.y) * m_Size.y;

			float	PrevLeft = m_PrevPos.x - m_Pivot.x * m_Size.x;
			float	CurLeft = m_Pos.x - m_Pivot.x * m_Size.x;

			float	PrevRight = m_PrevPos.x + (1.f - m_Pivot.x) * m_Size.x;
			float	CurRight = m_Pos.x + (1.f - m_Pivot.x) * m_Size.x;

			float ResultLeft = PrevLeft < CurLeft ? PrevLeft : CurLeft;
			float ResultRight = PrevRight > CurRight ? PrevRight : CurRight;
			float ResultTop = PrevBottom < CurBottom ? PrevBottom : CurBottom;
			float ResultBottom = PrevBottom > CurBottom ? PrevBottom : CurBottom;


			float uA = ((CurRight - CurLeft) * (StrPoint.y - CurTop) - (CurTop - CurTop) * (StrPoint.x - CurLeft)) / ((CurTop - CurTop) * (EndPoint.x - StrPoint.x) - (CurRight - CurLeft) * (EndPoint.y - StrPoint.y));
			float uB = ((EndPoint.x - StrPoint.x) * (StrPoint.y - CurTop) - (EndPoint.y - StrPoint.y) * (StrPoint.x - CurLeft)) / ((CurTop - CurTop) * (EndPoint.x - StrPoint.x) - (CurRight - CurLeft) * (EndPoint.y - StrPoint.y));

			Vector2 TopHitPt;
			bool topHit = false;

			// if uA and uB are between 0-1, lines are colliding
			if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
			{
				float intersectionX = StrPoint.x + (uA * (EndPoint.x - StrPoint.x));
				float intersectionY = StrPoint.y + (uA * (EndPoint.y - StrPoint.y));

				TopHitPt = { intersectionX, intersectionY };
				topHit = true;
			} 

			Vector2 Bottom = { m_Pos.x, m_Pos.y + (1.f - m_Pivot.y) * m_Size.y };

			float DistA = m_Pos.Distance(StrPoint);
			float DistB = m_Pos.Distance(EndPoint);

/*			if (topHit)
			{
				Vector2 Top = { m_Pos.x, m_Pos.y - (1.f - m_Pivot.y) * m_Size.y };

				DistA = Top.Distance(StrPoint);
				DistB = Top.Distance(EndPoint);
			}	*/		

			if (DistA + DistB <= LineLen + 5.5f)
			{
				m_Pos.y -= 0.5f;

				int CHECKBUG = 0;
			}

			bool Check = false;


			if (!m_Ground)
			{
				m_FallTime = 0.f;
				m_Ground = true;
			}

			if (m_Ground && m_Jump)
			{
				m_Pos.y -= 5.f;
			}

			float f2 = m_Angle;
			bool f1 = m_IsAngle;
			float f3 = m_Pos.Angle(EndPoint);
			float f4 = StrPoint.Angle(EndPoint);
			bool CHECKBUG = true;
			return;
		}
		return;
	case ECollider_Type::Circle:
		return;
	}
}

void CSonic::AddForce(float Speed, Vector2 Dir)
{
	m_Force += Dir * Speed;
}

void CSonic::AddForce(Vector2 Speed)
{
	m_Force += Speed;
}

bool CSonic::MoveRound(Vector2 Pos, float Dir)
{
	if (m_SetMoveRound)
	{
		if (m_MoveRoundDir != Dir)
		{
			m_MoveRoundPos.Angle(m_Pos);
			return false;
		}

		m_CharDir.x = Dir;

		SetPhysicsSimulate(false);

		m_Pos.x = Pos.x + cosf(DegreeToRadian(m_MoveRoundAngle)) * 70.f;
		m_Pos.y = Pos.y + sinf(DegreeToRadian(m_MoveRoundAngle)) * 70.f;


		return true;
	}

	return false;
}