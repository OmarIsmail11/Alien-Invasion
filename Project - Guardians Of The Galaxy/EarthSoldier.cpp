#include "EarthSoldier.h"
#include "Game.h"
#include <iostream>

using namespace std;

EarthSoldier::EarthSoldier(int id, int jointime, int health, int power, int attackcapacity,Game* &game)
{
	ID = id;
	type = ES;
	JoinTime = jointime;
	if (health > 0 && health <= 100) {
		Health = health ;
		InitialHealth = health;
	}
	else {
		Health = 100;
		InitialHealth = 100;
	}
	Power = power;
	GameManager = game;
	AttackCapacity = attackcapacity;
}

EarthSoldier::EarthSoldier(int id, int jointime, int health, int power, int attackcapacity, bool infstatus, bool Immunestatus, Game*& game)
{
	ID = id;
	type = ES;
	JoinTime = jointime;
	if (health > 0 && health <= 100) {
		Health = health;
		InitialHealth = health;
	}
	else {
		Health = 100;
		InitialHealth = 100;
	}
	Power = power;
	GameManager = game;
	AttackCapacity = attackcapacity;
	IsInfected = false;
	IsImmune = false;
}

EarthSoldier::EarthSoldier(int id, int jointime, int health, int power, int attackcapacity)
{
	ID = id;
	type = ES;
	JoinTime = jointime;
	if (health > 0 && health <= 100) {
		Health = health;
		InitialHealth = health;
	}
	else {
		Health = 100;
		InitialHealth = 100;
	}
	Power = power;
	AttackCapacity = attackcapacity;
}
EarthSoldier::EarthSoldier()
{
	ID = 0;
	JoinTime = 0;
	type = ES;
	Health = 100;
	Power = 0;
	AttackCapacity = 0;
	InitialHealth = 0;
}

int EarthSoldier::getInitialhealth()
{
	return InitialHealth;
}
int EarthSoldier::getJoinedUMLTime()
{
	return JoinedUMLTime;
}
void EarthSoldier::setJoinedUMLTime(int t)
{
	JoinedUMLTime = t;
}

void EarthSoldier::Attack()
{
	if (GameManager->getAA()->getAScount() <= 0 || AttackCapacity <= 0)
	{
		return;
	}
	Queue<AlienSoldier*>* TempList = new Queue<AlienSoldier*>();
	Queue<AlienSoldier*>* ShotList = new Queue<AlienSoldier*>();
	int killedunits = 0;
	int aliveunits = 0;
	int ShotCount = 0;
	int Damage = 0;
	AlienSoldier* AttackedAS = new AlienSoldier();
	AttackedAS = GameManager->getAA()->PickAS();
	if (IsInfected == false)
	{
		for (int i = 0; i < AttackCapacity; i++)
		{
			if (AttackedAS != NULL && GameManager->getAA()->getAScount() > 0)
			{
				GameManager->getAA()->RemoveAS(AttackedAS);
				Damage = (Power * Health / 100) / sqrt(AttackedAS->getHealth());
				AttackedAS->setHealth(AttackedAS->getHealth() - Damage);

				AttackedAS->GotShot();
				if (AttackedAS->GetNumGotShot() == 1) {
					AttackedAS->setFirstShotTime(GameManager->GetTimeStep());
				}

				if (AttackedAS->getHealth() == 0)
				{
					AttackedAS->setDistrucTime(GameManager->GetTimeStep());
					GameManager->addKilled(AttackedAS);
					ShotList->enqueue(AttackedAS);
					killedunits++;
					ShotCount++;
				}
				else if (AttackedAS->getHealth() > 0)
				{
					TempList->enqueue(AttackedAS);
					ShotList->enqueue(AttackedAS);
					aliveunits++;
					ShotCount++;
				}
			}
		}
		if (ShotCount != 0)
		{
			cout << u8"👮 " << "ES" << ID << " shots ";
			ShotList->Print2();
			cout << " IDs of all alien units shot by ES" << ID << endl;
		}
		AlienSoldier* AS = new AlienSoldier;
		for (int i = 0; i < aliveunits; i++)
		{
			TempList->dequeue(AS);
			GameManager->AddUnit(AS);
		}
		if (GameManager->getAA()->getASArmy()->isEmpty())
		{
			return;
		}
	}
	else
	{
		Queue<EarthSoldier*>* TempList = new Queue<EarthSoldier*>();
		Queue<EarthSoldier*>* ShotList = new Queue<EarthSoldier*>();
		EarthSoldier* AttackedES = new EarthSoldier();
		AttackedES = GameManager->getEA()->PickES();
		for (int i = 0; i < AttackCapacity; i++)
		{
			if (AttackedES != NULL && GameManager->getEA()->getEScount() > 0)
			{
				GameManager->getEA()->RemoveES(AttackedES);
				Damage = (Power * Health / 100) / sqrt(AttackedES->getHealth());
				AttackedES->setHealth(AttackedES->getHealth() - Damage);

				AttackedES->GotShot();
				if (AttackedES->GetNumGotShot() == 1) {
					AttackedES->setFirstShotTime(GameManager->GetTimeStep());
				}

				if (AttackedES->getHealth() == 0)
				{
					AttackedES->setDistrucTime(GameManager->GetTimeStep());
					GameManager->addKilled(AttackedES);
					ShotList->enqueue(AttackedES);
					killedunits++;
					ShotCount++;
				}
				else if (AttackedES->getHealth() > 0 && AttackedES->getHealth() < 0.2 * AttackedES->getInitialhealth())
				{
					AttackedES->setJoinedUMLTime(GameManager->GetTimeStep());
					GameManager->addUML_ES(AttackedES);
				}
				else
				{
					TempList->enqueue(AttackedES);
					ShotList->enqueue(AttackedES);
					aliveunits++;
					ShotCount++;
				}
			}
		}
		if (ShotCount != 0)
		{
			cout << u8"👮 " << "Inf_ES" << ID << " shots ";
			ShotList->Print2();
			cout << " IDs of all earth units shot by AS" << ID << endl;
		}
		EarthSoldier* ES = new EarthSoldier;
		for (int i = 0; i < aliveunits; i++)
		{
			TempList->dequeue(ES);
			GameManager->AddUnit(ES);
		}
		if (GameManager->getEA()->getESArmy()->isEmpty())
		{
			return;
		}
	}
}

void EarthSoldier::setIsInfected(bool status)
{
	IsInfected = status;
}

bool EarthSoldier::getIsInfected()
{
	return IsInfected;
}

void EarthSoldier::setIsImmune(bool status)
{
	IsImmune = status;
}

bool EarthSoldier::getIsImmune()
{
	return IsImmune;
}
