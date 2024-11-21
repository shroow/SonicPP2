#pragma once
#include "Monster.h"
class CEggBossFire :
    public CMonster
{
	friend class CScene;

protected:
	CEggBossFire();
	CEggBossFire(const CEggBossFire& Obj);
	virtual ~CEggBossFire();

private:
	Vector2		m_CharDir;
	int			m_HP;

	CSharedPtr<class CEggHead>		m_BossHead;
	
	std::vector<std::string>	m_vecSequenceKey[2];

	float			m_ImCount;
	EBoss_State		m_State;
	EBoss_State		m_PrevState;
	float			m_StateCount;

	float	m_TimeCount;
	int		m_EffectCount;

public:
	void SetCharDir(float Dir)
	{
		m_CharDir.x = Dir;
	}
	
public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);
	virtual void InflictSpeed(float Speed, Vector2 Dir);

public:
	void StartMove();
	void StopMove();
	void StopTurn();
	void FireBasic();
	void FireBasic2();
	void FireDown();
	void Die();

private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

