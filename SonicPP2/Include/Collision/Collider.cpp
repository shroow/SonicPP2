
#include "Collider.h"
#include "CollisionManager.h"

CCollider::CCollider()	:
	m_Scene(nullptr),
	m_Owner(nullptr),
	m_Profile(nullptr),
	m_MouseCollision(false),
	m_Bottom(0.f)
{
}

CCollider::CCollider(const CCollider& collider)	:
	CRef(collider),
	m_ColliderType(collider.m_ColliderType),
	m_Offset(collider.m_Offset),
	m_Scene(nullptr),
	m_Owner(nullptr),
	m_Profile(collider.m_Profile),
	m_MouseCollision(false),
	m_Bottom(0.f)
{
}

CCollider::~CCollider()
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}
}

void CCollider::SetCollisionProfile(const std::string& Name)
{
	m_Profile = CCollisionManager::GetInst()->FindProfile(Name);
}

void CCollider::AddCollisionList(CCollider* Collider)
{
	m_CollisionList.push_back(Collider);
}

bool CCollider::CheckCollisionList(CCollider* Collider)
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Collider)
			return true;
	}

	return false;
}

void CCollider::DeleteCollisionList(CCollider* Collider)
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		if (*iter == Collider)
		{
			m_CollisionList.erase(iter);
			return;
		}
	}
}

void CCollider::ClearCollisionList()
{
	auto	iter = m_CollisionList.begin();
	auto	iterEnd = m_CollisionList.end();

	for (; iter != iterEnd; ++iter)
	{
		(*iter)->DeleteCollisionList(this);
	}

	m_CollisionList.clear();
}

void CCollider::CallCollisionBegin(CCollider* Dest)
{
	if (m_CollisionBegin)
		m_CollisionBegin(this, Dest);
}

void CCollider::CallCollisionOn(CCollider* Dest)
{
	if (m_CollisionOn)
		m_CollisionOn(this, Dest);
}

void CCollider::CallCollisionEnd(CCollider* Dest)
{
	if (m_CollisionEnd)
		m_CollisionEnd(this, Dest);
}

void CCollider::CallMouseCollisionBegin(const Vector2& MousePos)
{
	if (m_MouseCollisionBegin)
		m_MouseCollisionBegin(this, MousePos);
}

void CCollider::CallMouseCollisionEnd(const Vector2& MousePos)
{
	if (m_MouseCollisionEnd)
		m_MouseCollisionEnd(this, MousePos);
}

bool CCollider::Init()
{
	m_Profile = CCollisionManager::GetInst()->FindProfile("Default");

	return true;
}

void CCollider::Update(float DeltaTime)
{
}

void CCollider::PostUpdate(float DeltaTime)
{
}

void CCollider::Render(HDC hDC, float DeltaTime)
{
}

bool CCollider::Collision(CCollider* Dest)
{
	return false;
}

bool CCollider::CollisionMouse(const Vector2& Mouse)
{
	return false;
}

void CCollider::Save(FILE* File)
{
	CRef::Save(File);

	//fwrite(&m_Owner, sizeof(CGameObject*), 1, File);
	fwrite(&m_ColliderType, sizeof(ECollider_Type), 1, File);
	fwrite(&m_Offset, sizeof(Vector2), 1, File);
	fwrite(&m_Profile, sizeof(CollisionProfile*), 1, File);
	fwrite(&m_HitPoint, sizeof(Vector2), 1, File);
	fwrite(&m_Bottom, sizeof(float), 1, File);
}

void CCollider::Load(FILE* File)
{
	CRef::Load(File);

	fread(&m_ColliderType, sizeof(ECollider_Type), 1, File);
	fread(&m_Offset, sizeof(Vector2), 1, File);
	fread(&m_Profile, sizeof(CollisionProfile*), 1, File);
	fread(&m_HitPoint, sizeof(Vector2), 1, File);
	fread(&m_Bottom, sizeof(float), 1, File);
}
