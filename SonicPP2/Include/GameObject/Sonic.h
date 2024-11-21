#pragma once
#include "Character.h"

class CSonic :
    public CCharacter
{
	friend class CScene;

protected:
	CSonic();
	CSonic(const CSonic& Obj);
	virtual ~CSonic();

private:
	bool	m_CheckInput[(int)EPlayer_Input::MAX];
	bool	m_Crouching;
	bool	m_Rolling;
	bool	m_JumpRolling;
	bool	m_Stopping;
	bool	m_LookingUp;
	bool	m_Bounce;
	bool	m_Board;
	bool	m_Bottom;
	int		m_SpinDash;
	int		m_RingCount;
	float	m_MaxSpeed;
	Vector2	m_HitSpeed;
	Vector2	m_CharDir;
	bool	m_Hit;
	std::vector<std::string>	m_vecSequenceKey[2];

	CSharedPtr<class CSpinDash>   m_SpinEffect;

	bool m_Boss;

public:
	int GetRingCount()	const
	{
		return m_RingCount;
	}

	void SetRingCount(int Num)
	{
		m_RingCount += Num;
	}

	void SetClear();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Render(HDC hDC, float DeltaTime);
	virtual bool InflictDamage(bool Damage);
	virtual void InflictSpeed(float Speed, Vector2 Dir);

public:
	void StartMoveRight();
	void MoveRight();
	void EndMoveRight();
	void StartMoveLeft();
	void MoveLeft();
	void EndMoveLeft();
	void StartMoveUp();
	void MoveUp();
	void EndMoveUp();
	void StartMoveDown();
	void MoveDown();
	void EndMoveDown();
	void StartJump();
	void EndJump();
	void Jumpkey();
	void Jumpkey1();
	void Jumpkey2();
	void Jumpkey3();
	void EnterKey();
	void SetBottom(Vector2 Pos);

public:
	void Crouching();
	void Spinning();
	void StartMove();
	void StartStop();
	void StopMove();
	void SonicJump();
	void Board();


private:
	void CollisionBegin(CCollider* Src, CCollider* Dest);
	void CollisionEnd(CCollider* Src, CCollider* Dest);
	void CollisionOn(CCollider* Src, CCollider* Dest);

private:
	void AddForce(float Speed, Vector2 Dir);
	void AddForce(Vector2 Speed);
	bool MoveRound(Vector2 Pos, float Dir);

};

