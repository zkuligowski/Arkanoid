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
	short int points;

public:
	void StartGame()
	{
		this->lives = 3;
		this->gameover = false;
		this->points = 0;

	}

	void AddPoint(){
		this->points++;
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
		printf("\nno i chuj przegrales!");
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

	short int getPoints() const {
		return points;
	}

	void setPoints(short int points) {
		this->points = points;
	}
};


#endif /* GAME_H_ */
