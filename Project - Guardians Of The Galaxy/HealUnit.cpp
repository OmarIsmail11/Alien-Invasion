#include "HealUnit.h"
#include "Game.h"
#include <iostream>

using namespace std;

HealUnit::HealUnit()
{
	ID = 0;
	type = HU;
	JoinTime = 0;
	Health = 100;
	Power = 0;
	AttackCapacity = 0;
}

HealUnit::HealUnit(int id, int jointime, int health, int power, int attackcapacity, Game*& game)
{
	ID = id;
	type = HU;
	JoinTime = jointime;
	Health = (health > 0 && health <= 100 ? health : 100);
	Power = power;
	GameManager = game;
	AttackCapacity = attackcapacity;
}

void HealUnit::setdie(bool why)
{
	die = why;
}

bool HealUnit::getdie()
{
	return die;
}

void HealUnit::Attack()
{
	if (GameManager->getEA()->getESArmy()->isEmpty() && GameManager->getEA()->getETArmy()->IsEmpty())
	{
		return;
	}
	int HealCapacity = AttackCapacity;
	if (HealCapacity == 0)
	{
		return;
	}
	int HealthImprovS = 0;
	int HealthImprovT = 0;
	int HealCount = 0;
	Queue<EarthTank*>* TempListT = new Queue<EarthTank*>();
	Queue<EarthSoldier*>* TempListS = new Queue<EarthSoldier*>();
	Queue<EarthSoldier*>* TempS = new Queue<EarthSoldier*>();
	Queue<EarthTank*>* TempT = new Queue<EarthTank*>();
	EarthSoldier* ES = new EarthSoldier();
	EarthTank* ET = new EarthTank();
	//int EScount = GameManager->getEA()->getEScount();
	/*for (int i = 0; i < EScount; i++)
	{
		if (ES != nullptr)
		{
			if (ES->getHealth() > 0 && ES->getHealth() < ES->getInitialhealth() * (0.2))
			{
				GameManager->getEA()->RemoveES(ES);
				GameManager->addUML_ES(ES);
				ES->setJoinedUMLTime(GameManager->GetTimeStep());
				ES = GameManager->getEA()->PickES();
			}
			else
			{
				GameManager->getEA()->RemoveES(ES);
				TempS->enqueue(ES);
				ES = GameManager->getEA()->PickES();
			}
		}
	}*/
	/*while (!TempS->isEmpty())
	{
		TempS->dequeue(ES);
		GameManager->getEA()->AddES(ES);
	}*/
	while (HealCapacity != 0&&ES!=nullptr)
	{
		if (GameManager->getUML_ES_Count() > 0)
		{
			int pri;
			GameManager->RemoveES_UML(ES, pri);
			if (GameManager->GetTimeStep() - ES->getJoinedUMLTime() > 10)
			{
				GameManager->addKilled(ES);
				//GameManager->RemoveES_UML(ES, pri);
			}
			else
			{
				if (ES->getIsInfected() == false)
				{
					HealthImprovS = (Power * Health / 100) / sqrt(ES->getHealth());
				}
				else 
				{
					HealthImprovS = 0.5 * ((Power * Health / 100) / sqrt(ES->getHealth()));
					ES->setIsImmune(true);
					ES->setIsInfected(false);
				}
				ES->setHealth(ES->getHealth() + HealthImprovS);
				HealCount++;
				HealCapacity--;
				if (ES->getHealth() > ES->getInitialhealth() * (0.2))
				{
					GameManager->AddUnit(ES);
				}
				else
				{
					TempListS->enqueue(ES);
				}
				if (HealCapacity == 0)
				{
					/*GameManager->getEA()->RemoveHU(HU);
					delete HU;
					HU = nullptr;
					return;*/
					die=true;
					return;
				}
			}
		}
		else
		{
			break;
		}
	}
	while (!TempListS->isEmpty())
	{
		TempListS->dequeue(ES);
		GameManager->addUML_ES(ES);
	}

	//ET = GameManager->getEA()->PickET();
	//int ETcount = GameManager->getEA()->getETcount();
	/*for (int i = 0; i < ETcount; i++)
	{
		if (ET != nullptr)
		{
			if (ET->getHealth() > 0 && ET->getHealth() < ET->getInitialhealth() * (0.2))
			{
				GameManager->getEA()->RemoveET(ET);
				GameManager->addUML_ET(ET);
				ET->setJoinedUMLTime(GameManager->GetTimeStep());
				ET = GameManager->getEA()->PickET();
			}
			else
			{
				GameManager->getEA()->RemoveET(ET);
				TempT->enqueue(ET);
				ET = GameManager->getEA()->PickET();
			}
		}
	}*/
	/*while (!TempT->isEmpty())
	{
		TempT->dequeue(ET);
		GameManager->getEA()->AddET(ET);
	}*/
	while (HealCapacity != 0&&ET!=nullptr)
	{
		if (GameManager->getUML_ET_Count() > 0)
		{
			GameManager->RemoveET_UML(ET);
			if (GameManager->GetTimeStep() - ET->getJoinedUMLTime() > 10)
			{
				GameManager->addKilled(ET);
				//GameManager->RemoveET_UML(ET);
			}
			else
			{
				HealthImprovT = (Power * Health / 100) / sqrt(ET->getHealth());
				ET->setHealth(ET->getHealth() + HealthImprovT);
				HealCount++;
				HealCapacity--;
				if (ET->getHealth() > ET->getInitialhealth() * (0.2))
				{
					//GameManager->getEA()->AddET(ET);
					GameManager->AddUnit(ET);
				}
				else
				{
					TempListT->enqueue(ET);
				}
				if (HealCapacity == 0)
				{
					/*GameManager->getEA()->RemoveHU(HU);
					delete HU;
					HU = nullptr;
					return;*/
					die = true;
					return;
				}
			}
		}
		else
		{
			break;
		}
	}
	while (!TempListT->isEmpty())
	{
		TempListT->dequeue(ET);
		GameManager->addUML_ET(ET);
	}
	if (HealCount!=0)
	{
		die = true;
	}
}
