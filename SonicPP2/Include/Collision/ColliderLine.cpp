#include "ColliderLine.h"
#include "../GameObject/GameObject.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"

CColliderLine::CColliderLine()
{
	SetTypeID<CColliderLine>();

	m_ColliderType = ECollider_Type::Line;
	m_Info.Buffer = 1.f;
}

CColliderLine::CColliderLine(const CColliderLine& collider) :
	CCollider(collider),
	m_Info(collider.m_Info)
{
}

CColliderLine::~CColliderLine()
{
}

bool CColliderLine::Init()
{
	if (!CCollider::Init())
		return false;

	return true;
}

void CColliderLine::Update(float DeltaTime)
{
	CCollider::Update(DeltaTime);
}

void CColliderLine::PostUpdate(float DeltaTime)
{
	CCollider::PostUpdate(DeltaTime);

	Vector2	Pos = m_Owner->GetPos();
}

void CColliderLine::Render(HDC hDC, float DeltaTime)
{
#ifdef _DEBUG

	EBrush_Type Green = EBrush_Type::Green;
	EBrush_Type Red = EBrush_Type::Red;

	if (CGameManager::GetInst()->GetEditMode())
	{
		Green = EBrush_Type::Red;
		Red = EBrush_Type::Green;
	}

	HPEN	Pen = CGameManager::GetInst()->GetPen(Green);

	if (!m_CollisionList.empty() || m_MouseCollision)
		Pen = CGameManager::GetInst()->GetPen(Red);

	HPEN	PrevPen = (HPEN)SelectObject(hDC, Pen);

	CCamera* Camera = m_Scene->GetCamera();

	Vector2	PosA = m_Info.PtA - Camera->GetPos();
	Vector2	PosB = m_Info.PtB - Camera->GetPos();

	//MoveToEx(hDC, (long)m_Info.PtA.x, (long)m_Info.PtA.y, nullptr);
	MoveToEx(hDC, (long)PosA.x, (long)PosA.y, nullptr);

	//LineTo(hDC, (long)m_Info.PtB.x, (long)m_Info.PtB.y);
	LineTo(hDC, (long)PosB.x, (long)PosB.y);

	SelectObject(hDC, PrevPen);

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

	HPEN	Pen = CGameManager::GetInst()->GetPen(Green);

	if (!m_CollisionList.empty() || m_MouseCollision)
		Pen = CGameManager::GetInst()->GetPen(Red);

	HPEN	PrevPen = (HPEN)SelectObject(hDC, Pen);

	CCamera* Camera = m_Scene->GetCamera();

	Vector2	PosA = m_Info.PtA - Camera->GetPos();
	Vector2	PosB = m_Info.PtB - Camera->GetPos();

	//MoveToEx(hDC, (long)m_Info.PtA.x, (long)m_Info.PtA.y, nullptr);
	MoveToEx(hDC, (long)PosA.x, (long)PosA.y, nullptr);

	//LineTo(hDC, (long)m_Info.PtB.x, (long)m_Info.PtB.y);
	LineTo(hDC, (long)PosB.x, (long)PosB.y);

	SelectObject(hDC, PrevPen);

#endif // _DEBUG
}

bool CColliderLine::Collision(CCollider* Dest)
{
	switch (Dest->GetColliderType())
	{
	case ECollider_Type::Box:
		return CCollisionManager::GetInst()->CollisionBoxToLine(m_HitPoint, (CColliderBox*)Dest, this);
	case ECollider_Type::Circle:
		return CCollisionManager::GetInst()->CollisionLineToCircle(m_HitPoint, this, (CColliderCircle*)Dest);
	case ECollider_Type::Line:
		return CCollisionManager::GetInst()->CollisionLineToLine(m_HitPoint, this, (CColliderLine*)Dest);
	}

	return false;
}

bool CColliderLine::CollisionMouse(const Vector2& Mouse)
{
	return CCollisionManager::GetInst()->CollisionPointToLine(m_HitPoint, Mouse, m_Info);
}

void CColliderLine::Save(FILE* File)
{
	CCollider::Save(File);

	fwrite(&m_Info.PtA, sizeof(Vector2), 1, File);
	fwrite(&m_Info.PtB, sizeof(Vector2), 1, File);
	fwrite(&m_Info.Buffer, sizeof(float), 1, File);
}

void CColliderLine::Load(FILE* File)
{
	CCollider::Load(File);

	fread(&m_Info.PtA, sizeof(Vector2), 1, File);
	fread(&m_Info.PtB, sizeof(Vector2), 1, File);
	fread(&m_Info.Buffer, sizeof(float), 1, File);
}

