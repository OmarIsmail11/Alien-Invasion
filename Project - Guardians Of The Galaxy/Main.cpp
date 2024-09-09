#include <fstream>
#include <iostream>
/*#include "Queue.h"
#include "PriorityQueue.h"
#include "Node.h"
#include "Stack.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "EarthArmy.h"
#include "ArmyUnit.h"
#include "EarthGunnery.h"
#include "AlienArmy.h"
#include "AlienSoldier.h"
#include "RandGen.h"*/
#include "Windows.h"
#include "Game.h"


using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	// Test code 
	srand(time(NULL));
	Game* Control = new Game();
	Control->Simulate();
	return 0;
}