#pragma once
#include "WidgetWindow.h"
class CCharacterHUD :
    public CWidgetWindow
{
    friend class CScene;

protected:
    CCharacterHUD();
    virtual ~CCharacterHUD();

protected:
    CSharedPtr<class CImageWidget>  m_Score;
    CSharedPtr<class CImageWidget>  m_Time;
    CSharedPtr<class CImageWidget>  m_Rings;
    CSharedPtr<class CText>     m_FPSText;
    CSharedPtr<class CNumber>   m_MinuteCount;
    CSharedPtr<class CNumber>   m_SecondCount;
    CSharedPtr<class CNumber>   m_RingCount;
    float       m_TimeCount;
    int         m_AddCount;

    int         m_Ring;

public:
    void SetRing(int Ring)
    {
        m_Ring = Ring;
    }

public:
    virtual bool Init();
    virtual void Update(float DeltaTime);
};

