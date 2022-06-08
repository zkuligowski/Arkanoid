/*
 * Game.h
 *
 *  Created on: Jun 5, 2022
 *      Author: zbign
 */

#ifndef GAME_H_
#define GAME_H_

#include "main.h"

class Game
{
	short int lives;
	bool gameover = false;
	int points;
	bool game_won = false;

public:
	void StartGame()
	{
		this->lives = 3;
		this->gameover = false;
		this->points = 0;

	}

	void AddPoint(int point){
		this->points = this->points + point;
	}

	void AddLive()
	{
		this->lives++;
	}

	void SubstractLive()
	{
		this->lives--;
	}

	void GameOver()
	{
		printf("xD");

		this->gameover = true;
	}

	short int getLives() const {
		return lives;
	}

	void setLives(short int lives) {
		this->lives = lives;
	}

	bool isGameover() const {
		return gameover;
	}

	void setGameover(bool gameover) {
		this->gameover = gameover;
	}

	int getPoints() const {
		return points;
	}

	void setPoints(int points) {
		this->points = points;
	}

	bool isGameWon() const {
		return game_won;
	}

	void setGameWon(bool gameWon = false) {
		game_won = gameWon;
	}
};


#endif /* GAME_H_ */
