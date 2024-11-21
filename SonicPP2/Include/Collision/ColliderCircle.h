#pragma once

#include "Collider.h"

class CColliderCircle :
    public CCollider
{
    friend class CGameObject;
    friend class CTileMap;

protected:
    CColliderCircle();
    CColliderCircle(const CColliderCircle& collider);
    virtual ~CColliderCircle();

protected:
    CircleInfo m_Info;

public:
    CircleInfo GetInfo()   const
    {
        return m_Info;
    }

    void SetRadius(float Radius)
    {
        m_Info.Radius = Radius;
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
        return m_Info.Center;
    }

    virtual Vector2 GetSize() const
    {
        return m_Info.Center;
    }

    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

