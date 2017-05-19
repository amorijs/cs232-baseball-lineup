#include<iostream>
#include<string>
#include"Statics.h"
#include"Player.h"
#include"PositionsArray.h"
using namespace std;

void getPlayerNames(Player players[NUMOFPLAYERS]);
void getBattingAverages(Player players[NUMOFPLAYERS]);
void sortByBattingAverage(Player players[NUMOFPLAYERS]);
void swap(int indexA, int indexB, Player players[NUMOFPLAYERS]);
void assignFoundPositions(Player players[NUMOFPLAYERS], PositionsArray positions);
void printPositions(Player players[NUMOFPLAYERS]);
void printColumnLabels();
void printSpaces(int numOfSpaces);
void printRow(int column, Player players[NUMOFPLAYERS]);

int main() {
	Player players[NUMOFPLAYERS];
	PositionsArray positions = *new PositionsArray();

	// Get and sort players
	getPlayerNames(players);
	getBattingAverages(players);
	sortByBattingAverage(players);
	
	// Find positions combination
	srand(time(NULL));
	while (!positions.arePositionsUnique()) {
		positions.findPositionsCombination();
	}

	// Assign positions
	assignFoundPositions(players, positions);
	printPositions(players);

	system("pause");
	return 0;
}

void getPlayerNames(Player players[NUMOFPLAYERS]) {
	string name;

	for (int i = 0; i < NUMOFPLAYERS; i += 1) {
		cout << "Enter player " << i + 1 << "'s name: ";
		cin >> name;
		players[i] = *new Player(name);
	}
}

void getBattingAverages(Player players[NUMOFPLAYERS]) {
	int battingAverage;

	for (int i = 0; i < NUMOFPLAYERS; i += 1) {
		cout << "Enter " << players[i].getName() << "'s batting average: ";
		cin >> battingAverage;
		players[i].setBattingAverage(battingAverage);
	}
}

void sortByBattingAverage(Player players[NUMOFPLAYERS]) {
	for (int i = 0; i < NUMOFPLAYERS; i += 1) {
		for (int j = i + 1; j < NUMOFPLAYERS; j += 1) {
			if (players[i].getBattingAverage() < players[j].getBattingAverage()) {
				swap(i, j, players);
			}
		}
	}
}

// Swaps two players in list (Only swaps name and average, cannot be used after positions assigned)
void swap(int indexA, int indexB, Player players[NUMOFPLAYERS]) {
	string tempName = players[indexA].getName();
	int tempBattingAverage = players[indexA].getBattingAverage();

	players[indexA].setName(players[indexB].getName());
	players[indexA].setBattingAverage(players[indexB].getBattingAverage());
	players[indexB].setName(tempName);
	players[indexB].setBattingAverage(tempBattingAverage);
}

void assignFoundPositions(Player players[NUMOFPLAYERS], PositionsArray positions) {
	int playerPosition;

	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		for (int i = 0; i < NUMOFINNINGS; i += 1) {
			playerPosition = positions.getPosition(p, i);
			players[p].setPositionOnInning(playerPosition, i);
		}
	}
}

void printPositions(Player players[NUMOFPLAYERS]) {
	cout << "Game lineup and field positions:" << endl;
	cout << "--------------------------------" << endl;
	printColumnLabels();

	for (int i = 0; i < NUMOFPLAYERS; i += 1) {
		printRow(i, players);
	}
}

void printColumnLabels() {
	const int NUMOFCOLUMNS = 6;
	const string columnLabels[6] = { "Name", "Inning 1", "Inning 2", "Inning 3", "Inning 4", "Inning 5" };
	string thisColumn;

	for (int i = 0; i < NUMOFCOLUMNS; i += 1) {
		thisColumn = columnLabels[i];
		cout << columnLabels[i];
		printSpaces(NUMOFSPACESBETWEENCOLUMNS - thisColumn.length());
	}

	cout << endl;
}

void printSpaces(int numOfSpaces) {
	for (int i = 0; i < numOfSpaces; i += 1) {
		cout << " ";
	}
}

void printRow(int row, Player players[NUMOFPLAYERS]) {
	string positionsArray[] = { "C","P","1B","2B","3B","SS","RF","RCF","LCF","LF","Out","Out" };
	string name = players[row].getName();
	int position;
	string positionString;

	cout << name;
	printSpaces(NUMOFSPACESBETWEENCOLUMNS - name.length());

	// Loop through all positions
	for (int i = 0; i < NUMOFINNINGS; i += 1) {
		position = players[row].getPositionOnInning(i);
		positionString = positionsArray[position];
		cout << positionString;
		printSpaces(NUMOFSPACESBETWEENCOLUMNS - positionString.length());
	}

	cout << endl;
}