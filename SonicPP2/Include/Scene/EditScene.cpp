
#include "EditScene.h"
#include "../GameObject/TileMap.h"
#include "SceneResource.h"
#include "Camera.h"
#include "../Input.h"
#include "Camera.h"
#include "../GameManager.h"
#include "EditDlg.h"
#include "../Resource/Texture/Texture.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderLine.h"
#include "../Collision/ColliderCircle.h"

CEditScene::CEditScene() :
	m_TileMapDlg(nullptr)
{
}

CEditScene::~CEditScene()
{
	CGameManager::GetInst()->SetEditMode(false);
	SAFE_DELETE(m_TileMapDlg);
}

bool CEditScene::Init()
{
	CInput::GetInst()->SetMouseOn(true);

	GetCamera()->SetResolution(800.f, 480.f);
	GetCamera()->SetWorldResolution(7488.f, 1536.f);
	GetCamera()->SetTargetPivot(0.5f, 0.5f);

	CInput::GetInst()->AddBindFunction<CEditScene>("MoveUp",
		Input_Type::Push, this, &CEditScene::MoveUp, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("MoveDown",
		Input_Type::Push, this, &CEditScene::MoveDown, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("MoveRight",
		Input_Type::Push, this, &CEditScene::MoveRight, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("MoveLeft",
		Input_Type::Push, this, &CEditScene::MoveLeft, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("OpenTileMapEditor",
		Input_Type::Down, this, &CEditScene::OpenTileMapEditor, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("Fire",
		Input_Type::Push, this, &CEditScene::MouseLButtonDrag, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("Fire",
		Input_Type::Down, this, &CEditScene::MouseLButtonDown, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("Fire",
		Input_Type::Up, this, &CEditScene::MouseLButtonUp, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("Delete",
		Input_Type::Down, this, &CEditScene::MouseRButtonDown, this);
	CInput::GetInst()->AddBindFunction<CEditScene>("Delete",
		Input_Type::Push, this, &CEditScene::MouseRButtonPush, this);

	CGameManager::GetInst()->SetEditMode(true);

	return true;
}



void CEditScene::CreateTileMap(int CountX, int CountY, int SizeX, int SizeY)
{
	if (!m_TileMap)
		m_TileMap = CreateObject<CTileMap>("TileMap");

	m_TileMap->CreateTile(CountX, CountY, Vector2((float)SizeX, (float)SizeY));
}

void CEditScene::SetTileTexture(CTexture* Texture)
{
	if (m_TileMap)
		m_TileMap->SetTileTexture(Texture);
}

void CEditScene::LoadTileMap(const char* FullPath)
{
	if (!m_TileMap)
		m_TileMap = CreateObject<CTileMap>("TileMap");

	m_TileMap->LoadFullPath(FullPath);
}

void CEditScene::MoveLeft()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(-1000.f * DELTA_TIME, 0.f));
}

void CEditScene::MoveRight()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(1000.f * DELTA_TIME, 0.f));
}

void CEditScene::MoveUp()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(0.f, -1000.f * DELTA_TIME));
}

void CEditScene::MoveDown()
{
	Vector2 CameraPos = GetCamera()->GetPos();

	GetCamera()->SetPos(CameraPos + Vector2(0.f, 1000.f * DELTA_TIME));
}

void CEditScene::OpenTileMapEditor()
{
	if (!m_TileMapDlg)
	{
		m_TileMapDlg = new CEditDlg;

		m_TileMapDlg->m_Scene = this;
		m_TileMapDlg->Init();
	}
}

void CEditScene::MouseLButtonDrag()
{
	if (!m_TileMap)
		return;
	
	if (m_TileMapDlg->GetDeleteCheck())
	{
		m_TileMap->DeleteCollider();
	}
	
	if (m_TileMapDlg->GetColliderCheck())
		return;

	Vector2	MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x ||
		MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
		return;

	switch (m_TileMapDlg->GetBrushType())
	{
	case ETile_Brush::Frame:
		ChangeFrame();
		break;
	case ETile_Brush::Option:
		ChangeOption();
		break;
	}

}

void CEditScene::MouseLButtonDown()
{
	if (!m_TileMap)
		return;

	if (m_TileMapDlg->GetDeleteCheck())
	{
		m_TileMap->DeleteCollider();
	}

	if (!m_TileMapDlg->GetColliderCheck())
		return;

	Vector2	MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x ||
		MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
		return;

	m_StartPos = CInput::GetInst()->GetMouseWorldPos();
}

void CEditScene::MouseLButtonUp()
{
	if (!m_TileMap)
		return;

	if (!m_TileMapDlg->GetColliderCheck())
		return;
	
	if (m_TileMapDlg->GetDeleteCheck())
		return;

	Vector2	MousePos = CInput::GetInst()->GetMousePos();

	CCamera* Camera = GetCamera();

	if (MousePos.x < 0.f || MousePos.x > Camera->GetResolution().x ||
		MousePos.y < 0.f || MousePos.y > Camera->GetResolution().y)
		return;

	ECollider_Type ColliderTypeInfo = ECollider_Type::None;

	ColliderTypeInfo = m_TileMapDlg->GetSelectCollider();
	
	if (ColliderTypeInfo == ECollider_Type::None)
		return;

	m_EndPos = CInput::GetInst()->GetMouseWorldPos();

	if (m_StartPos.x > m_EndPos.x)
	{
		m_StartPos = { 0.f, 0.f };
		m_EndPos = { 0.f, 0.f };
		return;
	}


	CColliderBox* Box = nullptr;
	CColliderLine* Line = nullptr;
	CColliderCircle* Circle = nullptr;
	float Buffer = -1.f;
	float Width = 0.f;
	float Height = 0.f;

	switch (ColliderTypeInfo)
	{
	case ECollider_Type::Box:
		if (m_StartPos.y > m_EndPos.y)
			return;
		Box = m_TileMap->AddCollider<CColliderBox>("TileMap");

		Width = m_EndPos.x - m_StartPos.x;
		Height = m_EndPos.y - m_StartPos.y;

		Box->SetOffset(m_StartPos.x + Width / 2.f, m_StartPos.y + Height / 2);
		Box->SetExtent(Width, Height);
		
		Box->SetCollisionProfile("TileMap");

		Box->SetCollisionBeginFunction<CTileMap>(m_TileMap, &CTileMap::CollisionBegin);
		Box->SetCollisionEndFunction<CTileMap>(m_TileMap, &CTileMap::CollisionEnd);
		break;
	case ECollider_Type::Line:
		Line = m_TileMap->AddCollider<CColliderLine>("TileMap");
		
		Buffer = m_TileMapDlg->GetLineBuffer();
		if (Buffer == -1)
			Buffer = 1.f;
				
		//Line->SetOffset(m_StartPos.x, m_StartPos.y);
		Line->SetLineInfo(m_StartPos.x, m_StartPos.y, 
			m_EndPos.x, m_EndPos.y, Buffer);
		Line->SetCollisionProfile("TileMap");

		Line->SetCollisionBeginFunction<CTileMap>(m_TileMap, &CTileMap::CollisionBegin);
		Line->SetCollisionEndFunction<CTileMap>(m_TileMap, &CTileMap::CollisionEnd);
		break;
	case ECollider_Type::Circle:
		Circle = m_TileMap->AddCollider<CColliderCircle>("TileMap");
		Circle->SetOffset(0.f, 0.f);
		Circle->SetCollisionProfile("TileMap");

		Circle->SetCollisionBeginFunction<CTileMap>(m_TileMap, &CTileMap::CollisionBegin);
		Circle->SetCollisionEndFunction<CTileMap>(m_TileMap, &CTileMap::CollisionEnd);
		break;
	}

	m_StartPos = { 0.f, 0.f };
	m_EndPos = { 0.f, 0.f };
	return;
}

void CEditScene::MouseRButtonDown()
{
	m_TileMap->DeleteCollider();
}

void CEditScene::MouseRButtonPush()
{
	m_TileMap->DeleteCollider();
}

void CEditScene::ChangeFrame()
{
	Vector2	MousePos = CInput::GetInst()->GetMouseWorldPos();

	const AnimationFrameData* Frame = m_TileMapDlg->GetTileFrameData();

	if (!Frame)
		return;

	m_TileMap->SetTileFrame(MousePos, Frame->Start, Frame->End);
	m_TileMap->SetTileRender(MousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(MousePos, m_TileMapDlg->GetCheckSideCollision());
}

void CEditScene::ChangeOption()
{
	Vector2	MousePos = CInput::GetInst()->GetMouseWorldPos();

	ETile_Option SelectOption = m_TileMapDlg->GetSelectOption();


	m_TileMap->ChangeTileOption(MousePos, SelectOption);
	m_TileMap->SetTileRender(MousePos, m_TileMapDlg->GetCheckRender());
	m_TileMap->SetTileSideCollision(MousePos, m_TileMapDlg->GetCheckSideCollision());
}

