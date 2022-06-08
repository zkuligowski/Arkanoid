/*
 * Block.h
 *
 *  Created on: Jun 5, 2022
 *      Author: zbign
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "main.h"
#include <random>


class Block {
	short int x; // x is left
	short int y; // y is top
	short int length = 15;
	short int width = 50;
	short int right;// = x + width;
	short int bottom;// = y + length;
	short int live;
	short int colour;
	bool can_drop = true;
	short int drop_number;

public:

	//Block();

/*
	Block(int block_x, int block_y, int block_length, int block_width, short int live, unsigned char colour, bool can_drop)
	{
		this->x = block_x;
		this->y = block_y;
		this->length = block_length;
		this->width = block_width;
		this->right = block_x + block_width;
		this->bottom = block_y + block_length;
		this->live = live;
		this->colour = colour;
		this->can_drop = can_drop;
	}
*/
	void CheckDrop()
	{
		if(can_drop == true)
		{
			std::random_device rd; // obtain a random number from hardware
			std::mt19937 gen(rd()); // seed the generator
			std::uniform_int_distribution<> distr(1, 5); // define the range
			this->drop_number = distr(gen);
			printf("%d\n",drop_number);
		}
	}

	void DestroyBlock()
	{
		this->live = 0;
	}

	void DrawBlock() {
		int p1 = x + width;
		int p2 = y + length;
		int temp = 0;

		for (int y = this->y; y < p2; y++) {
			for (int x = this->x; x < p1; x++) {
				if(colour == 1) // GOLD
				{
					if(live == 3)
					{
						SetPixel(GRAPH, x, y, tab_golden_block[temp]);
					}
					else if(live == 2)
					{
						SetPixel(GRAPH, x, y, tab_gold_block_crack1[temp]);
					}
					else if(live == 1)
					{
						SetPixel(GRAPH, x, y, tab_gold_block_crack2[temp]);
					}

				}
				else if(colour == 2) // SIVER
				{
					if(live == 2)
					{
						SetPixel(GRAPH, x, y, tab_silver_block[temp]);
					}
					else if(live == 1)
					{
						SetPixel(GRAPH, x, y, tab_silver_block_crack[temp]);
					}
				}
				else if(colour == 3) // WHITE
				{
					SetPixel(GRAPH, x, y, tab_white_block[temp]);
				}

				temp++;
			}
		}
	}

	void SubstractLive()
	{
		this->live--;
	}

	void AddLive()
	{
		this->live++;
	}

	short int getBottom() const {
		return bottom;
	}

	void setBottom(short int bottom) {
		this->bottom = bottom;
	}

	int getLength() const {
		return length;
	}

	void setLength(int length) {
		this->length = length;
	}

	short int getRight() const {
		return right;
	}

	void setRight(short int right) {
		this->right = right;
	}

	int getWidth() const {
		return width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	short int getX() const {
		return x;
	}

	void setX(short int x) {
		this->x = x;
		right = x + width;
	}

	short int getY() const {
		return y;
	}

	void setY(short int y) {
		this->y = y;
		bottom = y + length;
	}

	short int getLive() const {
		return live;
	}

	void setLive(short int live) {
		this->live = live;
	}

	short int getDropNumber() const {
		return drop_number;
	}

	void setDropNumber(short int dropNumber) {
		drop_number = dropNumber;
	}

	short int getColour() const {
		return colour;
	}

	void setColour(short int colour) {
		this->colour = colour;
		if(colour == 1)
		{
			live = 3;
		}
		else if(colour == 2)
		{
			live = 2;
		}
		else if(colour == 3)
		{
			live = 1;
		}
	}

	bool isCanDrop() const {
		return can_drop;
	}

	void setCanDrop(bool canDrop) {
		can_drop = canDrop;
	}
};

#endif /* BLOCK_H_ */
