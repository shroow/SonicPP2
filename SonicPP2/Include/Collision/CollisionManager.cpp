
#include "CollisionManager.h"
#include "ColliderBox.h"
#include "ColliderCircle.h"
#include "ColliderLine.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto	iter = m_mapProfile.begin();
	auto	iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("Default", ECollision_Channel::Default, true);
	CreateProfile("Player", ECollision_Channel::Player, true, ECollision_Interaction::Ignore);
	CreateProfile("Monster", ECollision_Channel::Monster, true, ECollision_Interaction::Ignore);
	CreateProfile("PlayerAttack", ECollision_Channel::PlayerAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("MonsterAttack", ECollision_Channel::MonsterAttack, true, ECollision_Interaction::Ignore);
	CreateProfile("Mouse", ECollision_Channel::Mouse, true, ECollision_Interaction::Collision);
	CreateProfile("MapObject", ECollision_Channel::MapObject, true, ECollision_Interaction::Ignore);
	CreateProfile("TileMap", ECollision_Channel::TileMap, true, ECollision_Interaction::Ignore);

	SetCollisionInteraction("Player", ECollision_Channel::MonsterAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::MapObject, ECollision_Interaction::Collision);
	SetCollisionInteraction("Player", ECollision_Channel::TileMap, ECollision_Interaction::Collision);

	SetCollisionInteraction("Monster", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::MapObject, ECollision_Interaction::Collision);
	SetCollisionInteraction("Monster", ECollision_Channel::TileMap, ECollision_Interaction::Collision);
	
	SetCollisionInteraction("TileMap", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("TileMap", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("TileMap", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("TileMap", ECollision_Channel::Mouse, ECollision_Interaction::Collision);

	SetCollisionInteraction("MapObject", ECollision_Channel::Player, ECollision_Interaction::Collision);
	SetCollisionInteraction("MapObject", ECollision_Channel::PlayerAttack, ECollision_Interaction::Collision);
	SetCollisionInteraction("MapObject", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("MapObject", ECollision_Channel::TileMap, ECollision_Interaction::Collision);

	SetCollisionInteraction("PlayerAttack", ECollision_Channel::Monster, ECollision_Interaction::Collision);
	SetCollisionInteraction("PlayerAttack", ECollision_Channel::MapObject, ECollision_Interaction::Collision);

	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Default, ECollision_Interaction::Collision);
	SetCollisionInteraction("MonsterAttack", ECollision_Channel::Player, ECollision_Interaction::Collision);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, ECollision_Channel Channel, 
	bool Enable, ECollision_Interaction BaseIteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
		return false;

	Profile = new CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->Enable = Enable;
	Profile->vecCollisionInteraction.resize((size_t)ECollision_Channel::Max);

	for (int i = 0; i < (int)ECollision_Channel::Max; ++i)
	{
		Profile->vecCollisionInteraction[i] = BaseIteraction;
	}

	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionInteraction(const std::string& Name, ECollision_Channel Channel,
	ECollision_Interaction Iteraction)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
		return false;

	Profile->vecCollisionInteraction[(int)Channel] = Iteraction;

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto	iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
		return nullptr;

	return iter->second;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& HitPoint, CColliderBox* Src,
	CColliderBox* Dest)
{
	if (CollisionBoxToBox(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& HitPoint, CColliderCircle* Src, 
	CColliderCircle* Dest)
{
	if (CollisionCircleToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, CColliderBox* Src, CColliderCircle* Dest)
{
	if (CollisionBoxToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& HitPoint, const Vector2& Src,
	CColliderBox* Dest)
{
	if (CollisionPointToBox(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& HitPoint, 
	const Vector2& Src, CColliderCircle* Dest)
{
	if (CollisionPointToCircle(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToBox(Vector2& HitPoint, const BoxInfo& Src, 
	const BoxInfo& Dest)
{
	if (Src.LT.x > Dest.RB.x)
		return false;

	else if (Src.LT.y > Dest.RB.y)
		return false;

	else if (Src.RB.x < Dest.LT.x)
		return false;

	else if (Src.RB.y < Dest.LT.y)
		return false;

	float Left = Src.LT.x > Dest.LT.x ? Src.LT.x : Dest.LT.x;
	float Top = Src.LT.y > Dest.LT.y ? Src.LT.y : Dest.LT.y;
	float Right = Src.RB.x < Dest.RB.x ? Src.RB.x : Dest.RB.x;
	float Bottom = Src.RB.y < Dest.RB.y ? Src.RB.y : Dest.RB.y;

	HitPoint.x = (Left + Right) / 2.f;
	HitPoint.y = (Top + Bottom) / 2.f;

	return true;
}

bool CCollisionManager::CollisionCircleToCircle(Vector2& HitPoint, const CircleInfo& Src, 
	const CircleInfo& Dest)
{
	// 센터 사이의 거리를 구한다.
	float Dist = Src.Center.Distance(Dest.Center);

	bool result = Dist <= Src.Radius + Dest.Radius;

	HitPoint = (Src.Center + Dest.Center) / 2.f;

	return result;
}

bool CCollisionManager::CollisionBoxToCircle(Vector2& HitPoint, const BoxInfo& Src, 
	const CircleInfo& Dest)
{
	// 원의 중점이 사각형의 좌, 우 영역 혹은 위, 아래 영역에 존재하는지 판단한다.
	if ((Src.LT.x <= Dest.Center.x && Dest.Center.x <= Src.RB.x) ||
		(Src.LT.y <= Dest.Center.y && Dest.Center.y <= Src.RB.y))
	{
		// 사각형을 원의 반지름만큼 확장한다.
		BoxInfo	RC = Src;
		RC.LT.x -= Dest.Radius;
		RC.LT.y -= Dest.Radius;
		RC.RB.x += Dest.Radius;
		RC.RB.y += Dest.Radius;

		// 확장된 사각형 안에 원의 중점이 들어온다면 충돌된 것이다.
		if (RC.LT.x > Dest.Center.x)
			return false;

		else if (RC.LT.y > Dest.Center.y)
			return false;

		else if (RC.RB.x < Dest.Center.x)
			return false;

		else if (RC.RB.y < Dest.Center.y)
			return false;

		// 히트포인트.
		BoxInfo	CircleBox;
		CircleBox.LT = Dest.Center - Dest.Radius;
		CircleBox.RB = Dest.Center + Dest.Radius;

		float Left = Src.LT.x > CircleBox.LT.x ? Src.LT.x : CircleBox.LT.x;
		float Top = Src.LT.y > CircleBox.LT.y ? Src.LT.y : CircleBox.LT.y;
		float Right = Src.RB.x < CircleBox.RB.x ? Src.RB.x : CircleBox.RB.x;
		float Bottom = Src.RB.y < CircleBox.RB.y ? Src.RB.y : CircleBox.RB.y;

		HitPoint.x = (Left + Right) / 2.f;
		HitPoint.y = (Top + Bottom) / 2.f;

		return true;
	}

	Vector2	Pos[4] =
	{
		Src.LT,
		Vector2(Src.RB.x, Src.LT.y),
		Vector2(Src.LT.x, Src.RB.y),
		Src.RB
	};

	// 4개의 점중 하나라도 원 안에 들어온다면 충돌한 것이다.
	for (int i = 0; i < 4; ++i)
	{
		float Dist = Dest.Center.Distance(Pos[i]);

		if (Dist <= Dest.Radius)
		{
			BoxInfo	CircleBox;
			CircleBox.LT = Dest.Center - Dest.Radius;
			CircleBox.RB = Dest.Center + Dest.Radius;

			float Left = Src.LT.x > CircleBox.LT.x ? Src.LT.x : CircleBox.LT.x;
			float Top = Src.LT.y > CircleBox.LT.y ? Src.LT.y : CircleBox.LT.y;
			float Right = Src.RB.x < CircleBox.RB.x ? Src.RB.x : CircleBox.RB.x;
			float Bottom = Src.RB.y < CircleBox.RB.y ? Src.RB.y : CircleBox.RB.y;

			HitPoint.x = (Left + Right) / 2.f;
			HitPoint.y = (Top + Bottom) / 2.f;

			return true;
		}
	}

	return false;
}

bool CCollisionManager::CollisionPointToBox(Vector2& HitPoint, const Vector2& Src,
	const BoxInfo& Dest)
{
	if (Dest.LT.x > Src.x)
		return false;

	else if (Dest.LT.y > Src.y)
		return false;

	else if (Dest.RB.x < Src.x)
		return false;

	else if (Dest.RB.y < Src.y)
		return false;

	HitPoint = Src;

	return true;
}

bool CCollisionManager::CollisionPointToCircle(Vector2& HitPoint,
	const Vector2& Src, const CircleInfo& Dest)
{
	float Dist = Dest.Center.Distance(Src);

	if (Dist <= Dest.Radius)
	{
		HitPoint = Src;

		return true;
	} 

	return false;
}

bool CCollisionManager::CollisionPointToLine(Vector2& HitPoint, 
	const Vector2& Src, CColliderLine* Dest)
{
	if (CollisionPointToLine(HitPoint, Src, Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToLine(Vector2& HitPoint, CColliderBox* Src, CColliderLine* Dest)
{

	if (CollisionBoxToLine(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionLineToCircle(Vector2& HitPoint, CColliderLine* Src, CColliderCircle* Dest)
{
	if (CollisionLineToCircle(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionLineToLine(Vector2& HitPoint, CColliderLine* Src, CColliderLine* Dest)
{
	if (CollisionLineToLine(HitPoint, Src->GetInfo(), Dest->GetInfo()))
	{
		Dest->m_HitPoint = HitPoint;
		return true;
	}

	return false;
}

bool CCollisionManager::CollisionPointToLine(Vector2& HitPoint, const Vector2& Src, const LineInfo& Dest)
{
	float DistA = Src.Distance(Dest.PtA);
	float DistB = Src.Distance(Dest.PtB);

	float LineLen = Dest.PtA.Distance(Dest.PtB);


	if (DistA + DistB >= LineLen - Dest.Buffer &&
		DistA + DistB <= LineLen + Dest.Buffer)
	{
		HitPoint = Src;

		return true;
	}

	return false;
}

bool CCollisionManager::CollisionBoxToLine( Vector2& HitPoint, const BoxInfo& Src, const LineInfo& Dest)
{
	float x1 = Dest.PtA.x;
	float y1 = Dest.PtA.y;
	float x2 = Dest.PtB.x;
	float y2 = Dest.PtB.y;

	float x3 = Src.LT.x;
	float y3 = Src.LT.y;
	float x4 = Src.LT.x;
	float y4 = Src.RB.y;

	Vector2 LeftHitPt;
	Vector2 RightHitPt;
	Vector2 TopHitPt;
	Vector2 BotHitPt;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	
	bool left = false;
	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		LeftHitPt = { intersectionX, intersectionY };
		//HitPoint = { intersectionX, intersectionY };
		left = true;
	}
	
	x1 = Dest.PtA.x;
	y1 = Dest.PtA.y;
	x2 = Dest.PtB.x;
	y2 = Dest.PtB.y;
	
	x3 = Src.RB.x;
	y3 = Src.LT.y;
	x4 = Src.RB.x;
	y4 = Src.RB.y;


	uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	bool right = false;
	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		RightHitPt = { intersectionX, intersectionY };
		//HitPoint = { intersectionX, intersectionY };
		right = true;
	}
	
	x1 = Dest.PtA.x;
	y1 = Dest.PtA.y;
	x2 = Dest.PtB.x;
	y2 = Dest.PtB.y;

	x3 = Src.LT.x;
	y3 = Src.LT.y;
	x4 = Src.RB.x;
	y4 = Src.LT.y;


	uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	bool top = false;
	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		TopHitPt = { intersectionX, intersectionY };
		//HitPoint = { intersectionX, intersectionY };
		top = true;
	}

	x1 = Dest.PtA.x;
	y1 = Dest.PtA.y;
	x2 = Dest.PtB.x;
	y2 = Dest.PtB.y;

	x3 = Src.LT.x;
	y3 = Src.RB.y;
	x4 = Src.RB.x;
	y4 = Src.RB.y;


	uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	bool bottom = false;
	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		BotHitPt = { intersectionX, intersectionY };
		//HitPoint = { intersectionX, intersectionY };
		bottom = true;
	}

	if (left || right || top || bottom) {
		if (bottom)
		{
			HitPoint = BotHitPt;
			return true;
		}
		else if (top)
		{
			HitPoint = TopHitPt;
			return true;
		}
		else if (left)
		{
			HitPoint = RightHitPt;
			return true;
		}
		else if (right)
		{
			HitPoint = LeftHitPt;
			return true;
		}

		//if (left && !(right || top || bottom))
		//	HitPoint = LeftHitPt;
		//else if (right && !(left || top || bottom))
		//	HitPoint = RightHitPt;
		//else if (top && !(left || right || bottom))
		//	HitPoint = TopHitPt;
		//else if (bottom && !(left || right || top))
		//	HitPoint = BotHitPt;

		//else if ((left && top) && !(right || bottom))
		//	HitPoint = (LeftHitPt + TopHitPt) / 2.f;		
		//else if ((left && bottom) && !(right || top))
		//	HitPoint = (LeftHitPt + BotHitPt) / 2.f;	

		//else if ((right && top) && !(left || bottom))
		//	HitPoint = (RightHitPt + TopHitPt) / 2.f;
		//else if ((right && bottom) && !(left || top))
		//	HitPoint = (RightHitPt + BotHitPt) / 2.f;

		//else if ((left && right) && !(top || bottom))
		//	HitPoint = (LeftHitPt + RightHitPt) / 2.f;
		//else if ((top && bottom) && !(left || right))
		//	HitPoint = (TopHitPt + BotHitPt) / 2.f;

		return true;
	}
	return false;
}

bool CCollisionManager::CollisionLineToCircle(Vector2& HitPoint, const LineInfo& Src, const CircleInfo& Dest)
{
	float DistX = Src.PtA.x - Dest.Center.x;
	float DistY = Src.PtA.y - Dest.Center.y;
	float DistanceA = sqrt((DistX * DistX) + (DistY * DistY));
	
	DistX = Src.PtB.x - Dest.Center.x;
	DistY = Src.PtB.y - Dest.Center.y;
	float DistanceB = sqrt((DistX * DistX) + (DistY * DistY));

	if (DistanceA <= Dest.Radius)
	{
		HitPoint = Src.PtA;
		return true;
	}
	else if (DistanceB <= Dest.Radius)
	{
		HitPoint = Src.PtB;
		return true;
	}
	else if (DistanceA <= Dest.Radius && DistanceB <= Dest.Radius)
	{
		HitPoint = Dest.Center;
		return true;
	}

	float LineLen = Src.PtA.Distance(Src.PtB);

	float Dot = (((Dest.Center.x - Src.PtA.x) * (Src.PtB.x - Src.PtA.x)) + 
		((Dest.Center.y - Src.PtA.y) * (Src.PtB.y - Src.PtA.y))) / (LineLen * LineLen);

	Vector2 Closest;
	Closest.x = Src.PtA.x + (Dot * (Src.PtB.x - Src.PtA.x));
	Closest.y = Src.PtA.y + (Dot * (Src.PtB.y - Src.PtA.y));


	float DistA = Closest.Distance(Src.PtA);
	float DistB = Closest.Distance(Src.PtB);

	LineLen = Src.PtA.Distance(Src.PtB);

	if (DistA + DistB >= LineLen - Src.Buffer && DistA + DistB <= LineLen + Src.Buffer)
	{
	}
	else
		return false;
	
	DistX = Closest.x - Dest.Center.x;
	DistY = Closest.y - Dest.Center.y;
	float Distance = sqrt((DistX * DistX) + (DistY * DistY));

	if (Distance <= Dest.Radius)
		return true;

	return false;
}

bool CCollisionManager::CollisionLineToLine(Vector2& HitPoint, const LineInfo& Src, const LineInfo& Dest)
{
	float x1 = Src.PtA.x;
	float y1 = Src.PtA.y;
	float x2 = Src.PtB.x;
	float y2 = Src.PtB.y;

	float x3 = Dest.PtA.x;
	float y3 = Dest.PtA.y;
	float x4 = Dest.PtB.x;
	float y4 = Dest.PtB.y;

	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

		// optionally, draw a circle where the lines meet
		float intersectionX = x1 + (uA * (x2 - x1));
		float intersectionY = y1 + (uA * (y2 - y1));

		HitPoint = { intersectionX, intersectionY };
		return true;
	}
	return false;
}