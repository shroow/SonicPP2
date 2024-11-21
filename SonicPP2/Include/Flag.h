#pragma once

enum class ETexture_Type
{
	Sprite,
	Frame
};

enum class ERender_Layer
{
	Back,
	Tile,
	Default,
	Effect,
	Max
};

enum class ECollision_Channel
{
	Default,
	Player,
	Monster,
	PlayerAttack,
	MonsterAttack,
	Mouse,
	MapObject,
	TileMap,
	Max
};

enum class ECollision_Interaction
{
	Ignore,
	Collision
};

enum class ECollider_Type
{
	None,
	Box,
	Line,
	Circle
};

enum class EBrush_Type
{
	Red,
	Green,
	Black,
	Blue,
	Yellow,
	Max
};

enum class EEffect_Type
{
	Once,
	Duration,
	Loop
};

enum class EButton_State
{
	Normal,
	MouseHovered,
	Click,
	Disable,
	Max
};

enum class EButton_Sound_State
{
	MouseHovered,
	Click,
	Max
};

enum class ETile_Option : unsigned char
{
	Normal,
	ImpossibleToMove
};

enum class EPlayer_Input
{
	Right,
	Left,
	Up,
	Down,
	Jump,
	MAX
};

enum class EObject_Type
{
	Small,
	Medium,
	Big
};

enum class EObject_Dir
{
	Left,
	Right,
	Up,
	Down
};

enum class EBoss_State
{
	None,
	Idle,
	Move1,
	Move2,
	Attack1,
	Attack2,
	Hurt,
	Die,
	Max
};