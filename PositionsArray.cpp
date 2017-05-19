#include"PositionsArray.h"
#include"Statics.h"
#include<iostream>
using namespace std;

PositionsArray::PositionsArray() {
	clearArray();
}

int PositionsArray::getPosition(int player, int inning) {
	return positions[player][inning];
}

void PositionsArray::findPositionsCombination() {
	clearArray();
	assignOuts();
	assignInfield();
	fillRestOfPositions();	
}

void PositionsArray::assignOuts() {
	int outsInGame = NUMOFOUTSPERINNING * NUMOFINNINGS;
	int outPosition = NUMOFPOSITIONS - 1;
	int outCounter;
	int randomPlayer;

	for (int i = 0; i < NUMOFINNINGS; i += 1) {
		outCounter = 0;
		while (outCounter < NUMOFOUTSPERINNING) {
			randomPlayer = rand() % NUMOFPLAYERS;
			if (!hasPlayerPlayedPosition(outPosition, randomPlayer)) {
				positions[randomPlayer][i] = outPosition;
				outCounter += 1;
			}
		}
	}
}

void PositionsArray::assignInfield() {
	int maxInfieldPositions = NUMOFINFIELDPOSITIONS;
	int randomPosition;
	int attemptCounter;
	int maxAttempts;

	// Loop through players
	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		// Loop through innings until infield position found
		for (int i = 0; i < 2; i += 1) {
			if (positions[p][i] != -1) continue; // If there was a position already assigned here, skip

			randomPosition = rand() % maxInfieldPositions;
			attemptCounter = 0;
			maxAttempts = maxInfieldPositions * 100;
			while (!isPositionAvailable(randomPosition, p, i) && attemptCounter < maxAttempts) {
				randomPosition = rand() % maxInfieldPositions;
				attemptCounter += 1;
			}

			if (attemptCounter >= maxAttempts) continue; // If no available infield position in inning, try next inning

			positions[p][i] = randomPosition; // Assign position
			break; // Next player
		}
	}
}

void PositionsArray::fillRestOfPositions() {
	int numOfPlayingPositions = NUMOFPOSITIONS - 1; // -1 to not include 'out' position
	int randomPosition;
	int attemptCounter;
	int maxAttempts;

	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		for (int i = 0; i < NUMOFINNINGS; i += 1) {
			if (positions[p][i] != -1) continue; // If there was a position already assigned here, skip

			randomPosition = rand() % numOfPlayingPositions;
			attemptCounter = 0;
			maxAttempts = numOfPlayingPositions * 100;
			while (!isPositionAvailable(randomPosition, p, i) && attemptCounter < maxAttempts) {
				randomPosition = rand() % numOfPlayingPositions;
				attemptCounter += 1;
			}

			positions[p][i] = randomPosition;
		}
	}
}

bool PositionsArray::isPositionAvailable(int position, int player, int inning) {
	return !hasPlayerPlayedPosition(position, player) && !hasPositionBeenPlayedInInning(position, inning);
}

bool PositionsArray::hasPlayerPlayedPosition(int position, int player) {
	for (int i = 0; i < NUMOFINNINGS; i += 1) {
		if (positions[player][i] == position) {
			return true;
		}
	}

	return false;
}

bool PositionsArray::hasPositionBeenPlayedInInning(int position, int inning) {
	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		if (positions[p][inning] == position) {
			return true;
		}
	}

	return false;
}

void PositionsArray::clearArray() {
	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		for (int i = 0; i < NUMOFINNINGS; i += 1) {
			positions[p][i] = -1;
		}
	}
}

bool PositionsArray::arePositionsUnique() {
	int outPosition = NUMOFPOSITIONS - 1;
	int playerPosition;
	bool unique = true;

	for (int p = 0; p < NUMOFPLAYERS; p += 1) {
		for (int i = 0; i < NUMOFINNINGS; i += 1) {
			playerPosition = positions[p][i];
			if (playerPosition == outPosition) continue; // skip if 'out' position
			positions[p][i] = -1; // Temporarily change position so test functions don't match it

			if (hasPlayerPlayedPosition(playerPosition, p)) {
				unique = unique && false;
			}

			if (hasPositionBeenPlayedInInning(playerPosition, i)) { 
				unique = unique && false;
			}

			positions[p][i] = playerPosition;
			if (!unique) return false;
		}
	}

	return true;
}
