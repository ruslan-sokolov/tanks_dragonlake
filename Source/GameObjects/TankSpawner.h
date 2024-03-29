#pragma once

#include "../Entities/TickInterface.h"
#include "../Entities/RenderBase.h"

#include <vector>

struct LevelStruct;

struct TankSpawnPoint;

/**
 * Tank spawner, can have multiple spawn points, and handle them all
 */
class TankSpawner : public RenderBase, public TickInterface
{
public:

	TankSpawner(std::vector<TankSpawnPoint> SpawnPoints, int TankSpawnNumMax, unsigned int SpawnRate, std::vector<int>FlashyTankNums);
	~TankSpawner();

protected:

	std::vector<TankSpawnPoint> SpawnPoints;
	std::vector<int> FlashyTankNums;

	unsigned int SpawnRate;
	unsigned int SpawnRateAccomulated;

	int TankSpawnNumMax;
	int TankSpawnNum;

	bool TankSpawnerExhausted() { return TankSpawnNum >= TankSpawnNumMax; }

	TankSpawnPoint& ChooseSpawnPoint();
	void SpawnTank(TankSpawnPoint& SpawnPoint);

public:

	int GetSpawnTankNum() const { return TankSpawnNum; }

	virtual void onTick(unsigned int DeltaTime) override final;
	virtual void onRender() override final;
	virtual void Destroy() override final;
	virtual void Initialize() override final;

	static int SpawnerCount;
	static TankSpawner* SpawnBasicTankSpawnerCorners(int SpawnTankNum, int SpawnRate, const int* FlashyIndexesArr, int FlashyIndexesArrSize, bool bInitialize = false);
	static TankSpawner* SpawnBasicTankSpawnerTop(int SpawnTankNum, int SpawnRate, const int* FlashyIndexesArr, int FlashyIndexesArrSize, bool bInitialize = false);
};