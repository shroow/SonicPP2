
#include "ColliderBox.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"
#include "../GameObject/GameObject.h"

CColliderBox::CColliderBox()	:
	m_Width(100.f),
	m_Height(100.f)
{
	SetTypeID<CColliderBox>();

	m_ColliderType = ECollider_Type::Box;
}

CColliderBox::CColliderBox(const CColliderBox& collider) :
	CCollider(collider),
	m_Width(collider.m_Width),
	m_Height(collider.m_Height),
	m_Info(collider.m_Info)
{
}

CColliderBox::~CColliderBox()
{
}

bool CColliderBox::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderBox::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderBox::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

	Vector2	Pos = m_Owner->GetPos();
	Vector2	Size(m_Width, m_Height);

	m_Info.LT = Pos + m_Offset - Size / 2.f;
	m_Info.RB = Pos + m_Offset + Size / 2.f;

	m_Bottom = m_Info.RB.y;
}

void CColliderBox::Render(HDC hDC, float DeltaTime)
{
#ifdef _DEBUG

	EBrush_Type Green = EBrush_Type::Green;
	EBrush_Type Red = EBrush_Type::Red;

	if (CGameManager::GetInst()->GetEditMode())
	{
		Green = EBrush_Type::Red;
		Red = EBrush_Type::Green;
	}

	HBRUSH	Brush = CGameManager::GetInst()->GetBrush(Green);

	if (!m_CollisionList.empty() || m_MouseCollision)
		Brush = CGameManager::GetInst()->GetBrush(Red);

	CCamera* Camera = m_Scene->GetCamera();

	RECT	RenderRC;

	RenderRC.left = (long)(m_Info.LT.x - Camera->GetPos().x);
	RenderRC.top = (long)(m_Info.LT.y - Camera->GetPos().y);
	RenderRC.right = (long)(m_Info.RB.x - Camera->GetPos().x);
	RenderRC.bottom = (long)(m_Info.RB.y - Camera->GetPos().y);

	FrameRect(hDC, &RenderRC, Brush);

	if (CGameManager::GetInst()->GetEditMode())
		FillRect(hDC, &RenderRC, Brush);

#endif // _DEBUG

	bool DEBUG = m_Scene->GetDEBUG();
#ifdef DEBUG

	EBrush_Type Green = EBrush_Type::Green;
	EBrush_Type Red = EBrush_Type::Red;

	if (CGameManager::GetInst()->GetEditMode())
	{
		Green = EBrush_Type::Red;
		Red = EBrush_Type::Green;
	}

	HBRUSH	Brush = CGameManager::GetInst()->GetBrush(Green);

	if (!m_CollisionList.empty() || m_MouseCollision)
		Brush = CGameManager::GetInst()->GetBrush(Red);

	CCamera* Camera = m_Scene->GetCamera();

	RECT	RenderRC;

	RenderRC.left = (long)(m_Info.LT.x - Camera->GetPos().x);
	RenderRC.top = (long)(m_Info.LT.y - Camera->GetPos().y);
	RenderRC.right = (long)(m_Info.RB.x - Camera->GetPos().x);
	RenderRC.bottom = (long)(m_Info.RB.y - Camera->GetPos().y);

	FrameRect(hDC, &RenderRC, Brush);

	if (CGameManager::GetInst()->GetEditMode())
		FillRect(hDC, &RenderRC, Brush);

#endif // _DEBUG
}

bool CColliderBox::Collision(CCollider* Dest)
{
	// 씬메니저에서 씬콜리전 콜을 하고 
	// 씬콜리전의 콜리전벡터안의 있는 모든 콜라이더간의 충돌타입만 체크하고
	// 각 콜라이더가 다른 콜라이더 모두와 Collision(CCollider* Dest)을 진행한다
	// 그리고 Collision(CCollider* Dest)에서는 타입만 판단하여 씬콜리전을 콜한다
	// 충돌 했는지 안했는지는 콜리젼매니저에서 bool 반환값을 준다
	// 충돌지점은 각 콜라이더의 히트포인트로 저장된다

	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollisionManager::GetInst()->CollisionBoxToBox(m_HitPoint, this, (CColliderBox*)Dest);
	case ECollider_Type::Line:
		return CCollisionManager::GetInst()->CollisionBoxToLine(m_HitPoint, this, (CColliderLine*)Dest);
	case ECollider_Type::Circle:
		return CCollisionManager::GetInst()->CollisionBoxToCircle(m_HitPoint, this, (CColliderCircle*)Dest);
	}

	return false;
}

bool CColliderBox::CollisionMouse(const Vector2& Mouse)
{
	return CCollisionManager::GetInst()->CollisionPointToBox(m_HitPoint, Mouse, m_Info);
}

void CColliderBox::Save(FILE* File)
{
	CCollider::Save(File);

	fwrite(&m_Width, sizeof(float), 1, File);
	fwrite(&m_Height, sizeof(float), 1, File);
	fwrite(&m_Info.LT, sizeof(Vector2), 1, File);
	fwrite(&m_Info.RB, sizeof(Vector2), 1, File);
}

void CColliderBox::Load(FILE* File)
{
	CCollider::Load(File);

	fread(&m_Width, sizeof(float), 1, File);
	fread(&m_Height, sizeof(float), 1, File);
	fread(&m_Info.LT, sizeof(Vector2), 1, File);
	fread(&m_Info.RB, sizeof(Vector2), 1, File);
}
