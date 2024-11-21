#include "SpinBoard.h"
#include "../GameManager.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Widget/WidgetComponent.h"
#include "../Widget/ImageWidget.h"
#include "../Widget/WidgetWindow.h"
#include "../Widget/ClearBoard.h"
#include "../Scene/SceneResource.h"
#include "Sonic.h"

CSpinBoard::CSpinBoard()	:
	m_CheckCreate(false)
{
	SetTypeID<CSpinBoard>();
}

CSpinBoard::CSpinBoard(const CSpinBoard& Obj) :
	CGameObject(Obj)
{
}

CSpinBoard::~CSpinBoard()
{
}


bool CSpinBoard::Init()
{
	m_TimeCount = 3.f;
	SetPivot(0.5f, 0.5f);

	CreateAnimation();

	AddAnimation("SpinBoard");
	AddAnimation("BoardSpin", true, 0.5f);

	//SetEndFunction<CSpinBoard>("SpringYellowBounce", this, &CSpinBoard::SetIdle);

	SetSize(32.f, 16.f);

	CColliderBox* Box = AddCollider<CColliderBox>("MapObject");

	Box->SetExtent(32.f, 16.f);
	Box->SetOffset(0.f, -8.f);
	Box->SetCollisionProfile("MapObject");

	Box->SetCollisionBeginFunction<CSpinBoard>(this, &CSpinBoard::CollisionBegin);
	Box->SetCollisionEndFunction<CSpinBoard>(this, &CSpinBoard::CollisionEnd);

	ChangeAnimation("BoardSpin");

	SetPhysicsSimulate(true);

	return true;
}

void CSpinBoard::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);

	if (m_Fall == false && m_Ground == true && m_CheckCreate == false)
	{
		ChangeAnimation("SpinBoard");
		m_CheckCreate = true;
		m_Scene->CreateWidgetWindow<CClearBoard>("ClearBoard");
		m_Scene->GetSceneResource()->SoundStop("STAGE1ACT1BGM");
		m_Scene->GetSceneResource()->SoundStop("Boss");
		m_Scene->GetSceneResource()->SoundPlay("Clear");
	}

	if (m_CheckCreate && m_TimeCount)
	{
		m_TimeCount -= DELTA_TIME;
		if (m_TimeCount < 0.f)
			m_TimeCount = 0.f;
		CGameObject* Obj = m_Scene->GetPlayer();
		CSonic* Sonic = (CSonic*)Obj;

		Sonic->SetClear();
	}
}

void CSpinBoard::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CSpinBoard::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

void CSpinBoard::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
}

void CSpinBoard::CollisionBegin(CCollider* Src, CCollider* Dest)
{
	if (Dest->GetProfile()->Channel == ECollision_Channel::Player)
	{

	}

}

void CSpinBoard::CollisionEnd(CCollider* Src, CCollider* Dest)
{

}