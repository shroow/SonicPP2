#include "Monster.h"

CMonster::CMonster()
{
	SetTypeID<CMonster>();
}

CMonster::CMonster(const CMonster& Obj) :
	CGameObject(Obj)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	return true;
}

void CMonster::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CMonster::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CMonster::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

bool CMonster::InflictDamage(bool Damage)
{
	return CGameObject::InflictDamage(Damage);
}

void CMonster::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);
}
