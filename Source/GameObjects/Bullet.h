#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"

class SpriteEntity;
class Tank;

class Bullet : public RenderBase, public TickInterface
{
public:

	Bullet(SpriteEntity* SpriteObj, VecInt2D Position, Direction Dir, int Speed, int Damage, Tank* Owner);
	~Bullet();

	int Speed;
	int Damage;

protected:

	SpriteEntity* SpriteObj;
	VecInt2D DirectionVec;
	Direction Dir;

	Tank* Owner;

public:

	Tank* GetOwner() const { return Owner; }

	virtual void onTick(unsigned int DeltaTime) override;

	virtual void onRender() override;
	virtual void onCollide(RenderBase* Other, CollisionFilter Filter) override;
	virtual void onDestroy() override;

public:

	static int BulletIndex;
	static Bullet* SpawnBulletSlow(Tank* Owner, VecInt2D Position, Direction Direction, bool bSetRenderEnable = true);
};