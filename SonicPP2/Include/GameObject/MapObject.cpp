#include "MapObject.h"

CMapObject::CMapObject() :
	m_Breakable(false)
{
}

CMapObject::CMapObject(const CMapObject& Obj)	:
	CGameObject(Obj),
	m_Breakable(Obj.m_Breakable)
{
}

CMapObject::~CMapObject()
{
}

bool CMapObject::Init()
{
	return true;
}

void CMapObject::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMapObject::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMapObject::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}
