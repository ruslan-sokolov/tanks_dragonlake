#include "Tank.h"

#include "../Entities/SpriteFlipFlop.h"

#include "../Helpers/DebugPrint.h"

#include "Bullet.h"


int Tank::TankIndex = 0;

Tank::Tank(SpriteFlipFlop* Left, SpriteFlipFlop* Right, SpriteFlipFlop* Up, SpriteFlipFlop* Down,
	VecInt2D Position, Direction Direction, int Health, int Speed, int MoveAnimSpeed)
	: Left(Left), Right(Right), Up(Up), Down(Down), Speed(Speed), MoveAnimSpeed(MoveAnimSpeed)
{
	SetHealth(Health);

	SetSize(Left->GetSize());
	SetPosition(Position);

	ChangeCurrentDirectionSprite(Direction);

	Left->SetFlipFlopTime(MoveAnimSpeed);
	Left->SetAutoFlipFlopEnable(false);
	
	Right->SetFlipFlopTime(MoveAnimSpeed);
	Right->SetAutoFlipFlopEnable(false);
	
	Up->SetFlipFlopTime(MoveAnimSpeed);
	Up->SetAutoFlipFlopEnable(false);
	
	Down->SetFlipFlopTime(MoveAnimSpeed);
	Down->SetAutoFlipFlopEnable(false);

	EnableCollsion();
}

Tank::~Tank()
{
	delete Left;
	delete Right;
	delete Up;
	delete Down;
}

void Tank::ChangeCurrentDirectionSprite(Direction DirectionTo)
{
	if (DirectionTo == CurrentDirection) return;

	CurrentDirection = DirectionTo;

	switch (CurrentDirection)
	{
	case Direction::RIGHT:
		CurrentActiveSprite = Right;
		break;
	case Direction::DOWN:
		CurrentActiveSprite = Down;
		break;
	case Direction::LEFT:
		CurrentActiveSprite = Left;
		break;
	default:
		CurrentActiveSprite = Up;
		break;
	}

	CurrentActiveSprite->SetPosition(Position);
}

void Tank::PlayMoveAnim()
{
	CurrentActiveSprite->SetAutoFlipFlopEnable(true);
}

void Tank::StopMoveAnim()
{
	CurrentActiveSprite->SetAutoFlipFlopEnable(false);
}

void Tank::MoveBegin(Direction DirectionTo)
{
	bCanMove = true;

	ChangeCurrentDirectionSprite(DirectionTo);

	PlayMoveAnim();
}

void Tank::MoveEnd(Direction DirectionTo)
{
	if (DirectionTo != CurrentDirection)  // do not execute when two key are pressed then one of them is released
		return;

	bCanMove = false;

	StopMoveAnim();
}

void Tank::Move(unsigned int DeltaTime)
{
	if (!bCanMove)
		return;

	VecInt2D PositionDelta = DirectionToVec(CurrentDirection) * (((Speed * DeltaTime) >> 10) + 1);
	
	SetPosition(Position + PositionDelta, CollisionFilter::CF_BLOCK);
	CurrentActiveSprite->SetPosition(Position);
}

void Tank::Fire()
{
	// ToDo: Fix bug
	//if (ActiveBullet != nullptr) // only one active bullet allowed for player
	//{
	//	delete ActiveBullet;
	//	ActiveBullet = nullptr;
	//	// return;
	//}

	PRINTF(PrintColor::Green, "%s shooted", GetName());

	ActiveBullet = Bullet::SpawnBulletSlow(this, GetSidePosition(CurrentDirection), CurrentDirection);
}

void Tank::onDamage(int Damage)
{
	HealthInterface::onDamage(Damage);

	PRINTF(PrintColor::Green, "Tank %d damage recieved", Damage);
}

void Tank::onDead()
{
	HealthInterface::onDead();

	PRINT(PrintColor::Green, "Tank died");
}

void Tank::onTick(unsigned int DeltaTime)
{
	TickInterface::onTick(DeltaTime);

	if (!IsDead())
	{
		Move(DeltaTime);
	}
}

void Tank::onRender()
{
	CurrentActiveSprite->onRender();
}

void Tank::onCollide(RenderBase* Other, CollisionFilter Filter)
{
	// PRINTF(PrintColor::Green, "TANK %s Collided With: %s", GetName(), Other->GetName());
}

Tank* Tank::SpawnTankBasic(VecInt2D Position, Direction Direction, Anchor Anchor, bool bSetRenderEnable)
{
	SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_LEFT_0, TANK_LEFT_1);
	SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_RIGHT_0, TANK_RIGHT_1);
	SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_UP_0, TANK_UP_1);
	SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_DOWN_0, TANK_DOWN_1);

	Position -= GetAnchorOffset(Left->GetSize(), Anchor);

	Tank* SpawnedTank = new Tank(Left, Right, Up, Down, Position, Direction, 
		TANK_HEALTH_BASIC, TANK_SPEED_SLOW, TANK_SPEED_SLOW_ANIM_TIME);

	std::string Name = "tank_basic_" + std::to_string(TankIndex);
	SpawnedTank->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedTank->EnableRender();
	}

	TankIndex++;

	return SpawnedTank;
}

Tank* Tank::SpawnEnemyTankBasic(VecInt2D Position, Direction Direction, Anchor Anchor, bool bSetRenderEnable)
{
	SpriteFlipFlop* Left = new SpriteFlipFlop(TANK_EB_LEFT_0, TANK_EB_LEFT_1);
	SpriteFlipFlop* Right = new SpriteFlipFlop(TANK_EB_RIGHT_0, TANK_EB_RIGHT_1);
	SpriteFlipFlop* Up = new SpriteFlipFlop(TANK_EB_UP_0, TANK_EB_UP_1);
	SpriteFlipFlop* Down = new SpriteFlipFlop(TANK_EB_DOWN_0, TANK_EB_DOWN_1);

	Position -= GetAnchorOffset(Left->GetSize(), Anchor);

	Tank* SpawnedTank = new Tank(Left, Right, Up, Down, Position, Direction,
		TANK_HEALTH_BASIC, TANK_SPEED_SLOW, TANK_SPEED_SLOW_ANIM_TIME);
	
	std::string Name = "tank_enemy_basic_" + std::to_string(TankIndex);
	SpawnedTank->SetName(Name);

	if (bSetRenderEnable)
	{
		SpawnedTank->EnableRender();
	}

	TankIndex++;

	return SpawnedTank;
}