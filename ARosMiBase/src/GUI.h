/*
 * GUI.h
 *
 *  Created on: Jun 5, 2022
 *      Author: zbign
 */

#ifndef GUI_H_
#define GUI_H_

#include "main.h"


class GUI {
	short int screen = 1;


public:
	void SetBackground(unsigned int width, unsigned int height, unsigned int background[])
	{
		//background
		int temp = 0;
		for (unsigned int y = 0; y < height; y++) {

			for (unsigned int x = 0; x < width; x++) {

				SetPixel(GRAPH, x, y, background[temp]);
				temp++;
			}
		}
	}

	void DrawLives(unsigned int lives, unsigned int picture[])
	{
		int temp = 0;
		if(lives >= 1)
		{
			for (unsigned int y = 70; y < 70 + 32; y++) {
				for (unsigned int x = 430; x < 430 + 36; x++) {

					SetPixel(GRAPH, x, y, picture[temp]);
					temp++;
				}
			}
		}
		if(lives >= 2)
		{
			int temp = 0;
			for (unsigned int y = 70; y < 70 + 32; y++) {
				for (unsigned int x = 500; x < 500 + 36; x++) {

					SetPixel(GRAPH, x, y, picture[temp]);
					temp++;
				}
			}
		}
		if(lives >= 3)
		{
			int temp = 0;
			for (unsigned int y = 70; y < 70 + 32; y++) {
				for (unsigned int x = 570; x < 570 + 36; x++) {

					SetPixel(GRAPH, x, y, picture[temp]);
					temp++;
				}
			}
		}
	}

	void SetLogo(unsigned int logo[])
	{
		int temp = 0;
				for (unsigned int y = 10; y < 50; y++) {

					for (unsigned int x = 420; x < 620; x++) {

						SetPixel(GRAPH, x, y, logo[temp]);
						temp++;
					}
				}
	}




	short int getScreen() const {
		return screen;
	}

	void setScreen(short int screen = 1) {
		this->screen = screen;
	}
};

#endif /* GUI_H_ */
