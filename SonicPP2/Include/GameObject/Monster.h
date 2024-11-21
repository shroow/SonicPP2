#pragma once
#include "GameObject.h"
class CMonster :
    public CGameObject
{
	friend class CScene;

protected:
	CMonster();
	CMonster(const CMonster& Obj);
	virtual ~CMonster();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);
	virtual void InflictSpeed(float Speed, Vector2 Dir);
};

