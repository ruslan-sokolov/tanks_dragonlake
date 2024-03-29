#pragma once

#include "SpriteEntity.h"
#include "TickInterface.h"

/* SpriteFlipFlop
 */
class SpriteFlipFlop : public SpriteEntity, public TickInterface
{
public:

	SpriteFlipFlop(const char* ResourceImageRelPathFlip, const char* ResourceImageRelPathFlop, unsigned int FlipFlopTimeMs = 0)
		: SpriteEntity(ResourceImageRelPathFlip),
		ResourceImagePathSibling(ResourceImageRelPathFlop), FlipFlopTime(FlipFlopTimeMs)
	{
	}

	~SpriteFlipFlop() {}

	virtual void onRender() override final;
	virtual void Initialize() override final;
	virtual void Destroy() override final;

	virtual void CreateSprite() override final
	{
		SpriteEntity::CreateSprite();

		SpriteObjSibling = SpritePrototypeManager::GetSpritePrototype(ResourceImagePathSibling);
	}

protected:

	const char* ResourceImagePathSibling = (char*)0;
	Sprite* SpriteObjSibling = nullptr;

	/** if True DrawSprite will draw Inherited SpriteObj else SpriteObjSibling */
	bool bFlipFlop = true;

	/** Control auto flipFlop on tick */
	bool bAutoFlipFlopEnabled = true;

	/** on tick sprite change, in ms, if 0 - disable */
	unsigned int FlipFlopTime = 0;
	unsigned int FlipFlopTimeAccomulated = 0;

public:
	
	void SetFlipFlopTime(unsigned int TimeInMs)	{ FlipFlopTime = TimeInMs; }

	unsigned int GetFlipFlopTime() const { return FlipFlopTime; }

	/** manual controlled flip flop */
	void SetFlipFlop(bool bFlipFlop) { this->bFlipFlop = bFlipFlop; }

	bool GetFlipFlop() const { return bFlipFlop; }

	void SetAutoFlipFlopEnable(bool bEnable) { bAutoFlipFlopEnabled = bEnable; }

	bool IsAutoFlipFlopEnabled() const { return bAutoFlipFlopEnabled; }

	virtual void onTick(unsigned int DeltaTime) override;
};