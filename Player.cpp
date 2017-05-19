#include"Player.h"
using namespace std;

Player::Player() {
}

Player::Player(string name) {
	setName(name);
}

void Player::setName(string name) {
	this->name = name;
}

void Player::setBattingAverage(int battingAverage) {
	this->battingAverage = battingAverage;
}

void Player::setPositionOnInning(int position, int inning) {
	positionOnInning[inning] = position;
}

string Player::getName() {
	return name;
}

int Player::getBattingAverage() {
	return battingAverage;
}

int Player::getPositionOnInning(int inning) {
	return positionOnInning[inning];
}
