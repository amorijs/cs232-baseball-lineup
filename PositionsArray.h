#ifndef _POSITIONSARRAY
#define _POSITIONSARRAY

#include <stdlib.h> 
#include<math.h>
#include <time.h>
#include"Statics.h"
using namespace std;

class PositionsArray {
private:
	int positions[NUMOFPLAYERS][NUMOFINNINGS];

public:
	PositionsArray();
	int getPosition(int player, int inning);
	void clearArray();
	void findPositionsCombination();
	void assignOuts();
	void assignInfield();
	void fillRestOfPositions();
	bool isPositionAvailable(int position, int player, int inning);
	bool hasPlayerPlayedPosition(int position, int row);
	bool hasPositionBeenPlayedInInning(int position, int inning);
	bool arePositionsUnique();
};

#endif