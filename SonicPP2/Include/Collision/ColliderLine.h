#pragma once
#include "Collider.h"

class CColliderLine :
    public CCollider
{
    friend class CGameObject;
    friend class CTileMap;

protected:
    CColliderLine();
    CColliderLine(const CColliderLine& collider);
    virtual ~CColliderLine();

protected:
    LineInfo    m_Info;

public:
    LineInfo GetInfo()   const
    {
        return m_Info;
    }

    float GetBuffer()   const
    {
        return m_Info.Buffer;
    }

    void SetLineInfo(Vector2 Start, Vector2 End, float Buffer = 1.f)
    {
        m_Info.PtA = Start;
        m_Info.PtB = End;
        m_Info.Buffer = Buffer;
    }

    void SetLineInfo(float StartX, float StartY, 
        float EndX, float EndY, float Buffer = 1.f)
    {
        m_Info.PtA.x = StartX;
        m_Info.PtA.y = StartY;
        m_Info.PtB.x = EndX;
        m_Info.PtB.y = EndY;
        m_Info.Buffer = Buffer;
    }

    void SetBuffer(float Buffer)
    {
        m_Info.Buffer = Buffer;
    }


public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
    virtual void PostUpdate(float DeltaTime);
    virtual void Render(HDC hDC, float DeltaTime);
    virtual bool Collision(CCollider* Dest);
    virtual bool CollisionMouse(const Vector2& Mouse);

    virtual Vector2 GetPoint() const
    {
        return m_Info.PtA;
    }
    virtual Vector2 GetSize() const
    {
        return m_Info.PtB;
    }

    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

