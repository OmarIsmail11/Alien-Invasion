#pragma once
#include "ArmyUnit.h"
class SaverUnit : public ArmyUnit
{
public:
	SaverUnit(int id, int jointime, int health, int power, int attackcapacity, Game*& game);
	SaverUnit(int id, int jointime, int health, int power, int attackcapacity);
	SaverUnit();
	void Attack();
};

