#pragma once
#include "Effect.h"
class CFire :
	public CEffect
{
	friend class CScene;

protected:
	CFire();
	CFire(const CFire& Obj);
	virtual ~CFire();

private:
	float	m_Dir;
	int		m_State;
	float	m_TimeCount;
	std::vector<std::string>	m_vecSequenceKey[2];
	CSharedPtr<class CColliderBox>	m_Box;

public:
	void SetDir(float Dir)
	{
		m_Dir = Dir;
	}

	void SetState(int State, float Dir, Vector2 Pos);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);

private:
	void AnimationEnd();
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
};

