/*
 * Paddle.h
 *
 *  Created on: Jun 5, 2022
 *      Author: zbign
 */

#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"


namespace std {
//class with moving platform
class Paddle {

	short int position = 0;
	bool right = false;
	bool left = false;
	short int speed = 5;
	short int height = 7;
	short int width = 48;

public:
	void MovePaddle() {
		if (getKey() == 75) {
			position = position - speed;
			left = true;
			right = false;
		} else if (getKey() == 77) {
			position = position + speed;
			left = false;
			right = true;
		}

		else {
			left = false;
			right = false;
		}

		if (position < 0)
			position = 0;
		else if (position > 350)
			position = 350;
	}

	void DrawPaddle()
	{
		int temp = 0;
		for (int i = 0; i < width; i++) {
			for (int j = 468 ; j < 468 + height; j++) {
				int p1 = position + i;

				SetPixel(GRAPH, p1, j, tab_paddle1[temp]);
				temp++;
			}
		}
	}

	short int getPosition() const {
		return position;
	}

	void setPosition(short int position = 0) {
		this->position = position;
	}

	short int getHeight() const {
		return height;
	}

	void setHeight(short int height = 5) {
		this->height = height;
	}

	short int getSpeed() const {
		return speed;
	}

	void setSpeed(short int speed = 5) {
		this->speed = speed;
	}

	short int getWidth() const {
		return width;
	}

	void setWidth(short int width = 50) {
		this->width = width;
	}
};
}



#endif /* PADDLE_H_ */
