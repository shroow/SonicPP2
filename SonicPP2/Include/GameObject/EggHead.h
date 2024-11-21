#pragma once
#include "GameObject.h"
class CEggHead :
    public CGameObject
{
	friend class CScene;

protected:
	CEggHead();
	CEggHead(const CEggHead& Obj);
	virtual ~CEggHead();

private:
	Vector2		m_CharDir;

	CSharedPtr<CGameObject>		m_BossHead;

	std::vector<std::string>	m_vecSequenceKey[2];

	EBoss_State		m_State;

	float			m_TimeCount;

public:
	void SetCharDir(float Dir)
	{
		m_CharDir.x = Dir;
	}

	void SetState(EBoss_State State)
	{
		m_State = State;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
};

