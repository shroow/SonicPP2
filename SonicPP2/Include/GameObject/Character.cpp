
#include "Character.h"

CCharacter::CCharacter()
{
	SetTypeID<CCharacter>();
}

CCharacter::CCharacter(const CCharacter& Obj) :
	CGameObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Update(float DeltaTime)
{
	CGameObject::Update(DeltaTime);
}

void CCharacter::PostUpdate(float DeltaTime)
{
	CGameObject::PostUpdate(DeltaTime);
}

void CCharacter::Render(HDC hDC, float DeltaTime)
{
	CGameObject::Render(hDC, DeltaTime);
}

bool CCharacter::InflictDamage(bool Damage)
{
	return CGameObject::InflictDamage(Damage);
}

void CCharacter::InflictSpeed(float Speed, Vector2 Dir)
{
	CGameObject::InflictSpeed(Speed, Dir);

}