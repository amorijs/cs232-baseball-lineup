#ifndef _PLAYER
#define _PLAYER

#include<string>
#include"Statics.h"
using namespace std;

class Player {
private:
	string name;
	int battingAverage;
	int positionOnInning[NUMOFINNINGS];

public:
	Player();
	Player(string name);
	void setName(string name);
	void setBattingAverage(int battingAverage);
	int getPositionOnInning(int inning);
	void setPositionOnInning(int position, int inning);
	string getName();
	int getBattingAverage();
};

#endif