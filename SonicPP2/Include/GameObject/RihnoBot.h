#pragma once
#include "Monster.h"

class CRihnoBot :
    public CMonster
{
	friend class CScene;

protected:
	CRihnoBot();
	CRihnoBot(const CRihnoBot& Obj);
	virtual ~CRihnoBot();

private:
	Vector2 m_CharDir;
	bool	m_TurnCheck;
	bool	m_MoveCheck;
	bool	m_IdleCheck;
	float	m_TurnCount;
	int		m_HP;

	std::vector<std::string>	m_vecSequenceKey[2];

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);
	virtual void InflictSpeed(float Speed, Vector2 Dir);

public:
	void StopMove();
	void StopTurn();
	void SetCharDir(float Dir)
	{
		m_CharDir.x = Dir;
	}

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void CollisionOn(CCollider* Src, CCollider* Dest);
};

