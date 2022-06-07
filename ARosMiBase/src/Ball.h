/*
 * Ball.h
 *
 *  Created on: Jun 5, 2022
 *      Author: zbign
 */

#ifndef BALL_H_
#define BALL_H_

#include "main.h"

namespace std {

//class with ball
class Ball {
private:
	short int dx = 2;
	short int dy = 2;
	short int x = 50;
	short int y = 50;
	short int width = 10;
	short int height = 10;
	short int Bottom;
	short int Right;
	bool is_fireball = false;
	short int collision_counter = 0;

public:

	void Add_collision_counter()
	{
		this->collision_counter++;
	}
	void Reset_collision_counter()
	{
		this->collision_counter = 0;
	}

	void MoveBall() {
		x += dx;
		y += dy;

		if (x >= 400 - (12 + width) || x <= 1 + 12)
		{
			dx = -dx;
			//this->collision_counter++;
		}


		if (y <= 1 + 13)
		{
			dy = -dy;
			//this->collision_counter++;
		}


		Bottom = y + height;
		Right = x + width;
	}

	//Ball is 10x10 square (temporary)
	void DrawBall() {
		int temp = 0;
		if(is_fireball == true)
		{
			this->width = 15;
			this->height = 15;
		}
		else
		{
			this->width = 10;
			this->height = 10;
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				int p1 = i + x;
				int p2 = j + y;

				if(is_fireball == true)
				{
					if(tab_fireball[temp] != 0xffffff)
					{
						SetPixel(GRAPH, p1, p2, tab_fireball[temp]);
					}
				}
				else
				{
					if(tab_ball1[temp] != 0xffffff)
					{
						SetPixel(GRAPH, p1, p2, tab_ball1[temp]);
					}


				}
				temp++;
		}
	}
	}

	short int getX() const {
		return x;
	}

	void setX(short int x = 100) {
		this->x = x;
	}

	short int getY() const {
		return y;
	}

	void setY(short int y = 50) {
		this->y = y;
	}

	short int getDx() const {
		return dx;
	}

	void setDx(short int dx = 1) {
		this->dx = dx;
	}

	short int getDy() const {
		return dy;
	}

	void setDy(short int dy = 1) {
		this->dy = dy;
	}

	short int getHeight() const {
		return height;
	}

	void setHeight(short int height = 10) {
		this->height = height;
	}

	short int getWidth() const {
		return width;
	}

	void setWidth(short int width = 10) {
		this->width = width;
	}

	short int getBottom() const {
		return Bottom;
	}

	void setBottom(short int bottom) {
		Bottom = bottom;
	}

	short int getRight() const {
		return Right;
	}

	void setRight(short int right) {
		Right = right;
	}

bool isIsFireball() const {
	return is_fireball;
}

void setIsFireball(bool isFireball = false) {
	is_fireball = isFireball;
}

	short int getCollisionCounter() const {
		return collision_counter;
	}

	void setCollisionCounter(short int collisionCounter = 0) {
		collision_counter = collisionCounter;
	}
}
;

} /* namespace std */

#endif /* BALL_H_ */
