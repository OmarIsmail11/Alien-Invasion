#include "SaverUnit.h"
#include <iostream>

using namespace std;

SaverUnit::SaverUnit(int id, int jointime, int health, int power, int attackcapacity, Game*& game)
{
	ID = id;
	type = SU;
	JoinTime = jointime;
	Health = (health > 0 && health <= 100 ? health : 100);
	Power = power;
	GameManager = game;
	AttackCapacity = attackcapacity;
}

SaverUnit::SaverUnit(int id, int jointime, int health, int power, int attackcapacity)
{
	ID = id;
	type = SU;
	JoinTime = jointime;
	Health = (health > 0 && health <= 100 ? health : 100);
	Power = power;
	AttackCapacity = attackcapacity;
}

SaverUnit::SaverUnit()
{
	ID = 0;
	type = SU;
	JoinTime = 0;
	Health = 100;
	Power = 0;
	AttackCapacity = 0;
}

void SaverUnit::Attack()
{

}
