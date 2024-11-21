
#include "CharacterHUD.h"
#include "Button.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../Input.h"
#include "ImageWidget.h"
#include "Text.h"
#include "Number.h"

int	g_Minute = 0;
int g_Second = 0;

CCharacterHUD::CCharacterHUD()
{
}

CCharacterHUD::~CCharacterHUD()
{
}

bool CCharacterHUD::Init()
{
	if (!CWidgetWindow::Init())
		return false;

	SetSize(200.f, 100.f);
	SetPos(0.f, 0.f);

	m_Score = CreateWidget<CImageWidget>("Score");
	m_Score->SetTexture("ScoreHUD", TEXT("HUD/Score.bmp"));
	m_Score->SetSize(49.f, 16.f);
	m_Score->SetPos(45.f, 32.f);
	m_Score->SetColorKey(255, 0, 255);

	m_Time = CreateWidget<CImageWidget>("Time");
	m_Time->SetTexture("TimeHUD", TEXT("HUD/Time.bmp"));
	m_Time->SetSize(40.f, 16.f);
	m_Time->SetPos(45.f, 55.f);
	m_Time->SetColorKey(255, 0, 255);

	m_Rings = CreateWidget<CImageWidget>("Rings");
	m_Rings->SetTexture("RingsHUD", TEXT("HUD/Rings.bmp"));
	m_Rings->SetSize(49.f, 16.f);
	m_Rings->SetPos(45.f, 75.f);
	m_Rings->SetColorKey(255, 0, 255);
	
	CImageWidget* Colon = CreateWidget<CImageWidget>("Colon");
	m_MinuteCount = CreateWidget<CNumber>("Minute");
	m_SecondCount = CreateWidget<CNumber>("Second");
	m_RingCount = CreateWidget<CNumber>("RingCount");

	Colon->SetTexture("Colon", TEXT("HUD/Number/Colon.bmp"));
	Colon->SetSize(8.f, 16.f);
	Colon->SetPos(110.f, 55.f);
	Colon->SetColorKey(255, 0, 255);

	std::vector<std::wstring>	vecFileName;

	for (int i = 0; i <= 9; ++i)
	{
		TCHAR	FileName[MAX_PATH] = {};
		// %d에 i의 값이 대입되어 문자열이 만들어지게 된다.
		wsprintf(FileName, TEXT("HUD/Number/%d.bmp"), i);
		vecFileName.push_back(FileName);
	}


	m_MinuteCount->SetTexture("Number", vecFileName);
	m_SecondCount->SetTexture("Number", vecFileName);
	m_RingCount->SetTexture("Number", vecFileName);

	m_MinuteCount->SetColorKey(255, 0, 255);
	m_SecondCount->SetColorKey(255, 0, 255);
	m_RingCount->SetColorKey(255, 0, 255);


	m_MinuteCount->SetSize(8.f, 16.f);
	m_MinuteCount->SetPos(100.f, 55.f);

	m_SecondCount->SetSize(8.f, 16.f);
	m_SecondCount->SetPos(120.f, 55.f);

	m_RingCount->SetSize(8.f, 16.f);
	m_RingCount->SetPos(120.f, 75.f);

	m_FPSText = CreateWidget<CText>("Text");

	m_FPSText->SetText(TEXT("FPS"));
	m_FPSText->SetPos(640, 35.f);
	m_FPSText->SetTextColor(255, 255, 255);

	m_FPSText->EnableShadow(true);
	m_FPSText->SetShadowOffset(2.f, 2.f);

	return true;
}

void CCharacterHUD::Update(float DeltaTime)
{
	CWidgetWindow::Update(DeltaTime);

	m_TimeCount += DELTA_TIME;

	if (m_TimeCount >= 1.f)
	{
		m_TimeCount = 0.f;
		
		if (++g_Second > 59)
		{
			++g_Minute;
			g_Second = 0;
		}

		m_MinuteCount->SetNumber(g_Minute);
		m_SecondCount->SetNumber(g_Second);
	}

	m_RingCount->SetNumber(m_Ring);

	float FPS = CGameManager::GetInst()->GetFPS();

	char	Text[256] = {};
	sprintf_s(Text, "FPS : %.5f", FPS);

	TCHAR	Unicode[256] = {};
	int Length = MultiByteToWideChar(CP_ACP, 0, Text, -1, 0, 0);
	MultiByteToWideChar(CP_ACP, 0, Text, -1, Unicode, Length);

	m_FPSText->SetText(Unicode);
}
