#pragma once

#include "Collider.h"

class CColliderBox :
    public CCollider
{
    friend class CGameObject;
    friend class CTileMap;

protected:
    CColliderBox();
    CColliderBox(const CColliderBox& collider);
    virtual ~CColliderBox();

protected:
    float   m_Width;
    float   m_Height;
    BoxInfo m_Info;
    Vector2 m_HitPointY;

public:
    BoxInfo GetInfo()   const
    {
        return m_Info;
    }

    void SetExtent(float Width, float Height)
    {
        m_Width = Width;
        m_Height = Height;
    }
    
    Vector2 GetHitPointY()  const
    {
        return m_HitPointY;
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
        return m_Info.LT;
    }

    virtual Vector2 GetSize() const
    {
        return m_Info.RB;
    }

    virtual void Save(FILE* File);
    virtual void Load(FILE* File);
};

