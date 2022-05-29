#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <linux/input.h>
#include <linux/joystick.h>
#include <time.h>
#include <pthread.h>




#include "utilities.h"
#include "peripherals.h"



extern struct JoY JoYAct;
extern int gRawKeys[6];

void UpdateIO();
void SystemInit();
void SystemExit();
void DataPrepare();
void ClearScreen();
void DrawObjects();
void PrintDiagnosticInfo();


#define MaxObj 9000
int ActMaxObj;
int dx[MaxObj];
int dy[MaxObj];
int s[MaxObj];
int x[MaxObj];
int y[MaxObj];
int xt[MaxObj];
int yt[MaxObj];

unsigned int GRAPH[640 * 480];

int mode = 0;
int stage = 0;
volatile int flash_ligth = 0;
volatile long globalTimer_ms = 0;
long startTime_ms;
int frame_count = 0;



//class with ball
class Ball {
	short int dx = 1;
	short int dy = 1;
	short int x = 50;
	short int y = 50;
	short int width = 10;
	short int height = 10;

public:
	void MoveBall() {
		x += dx;
		y += dy;

		if (x >= 400 || x <= 1)
			dx = -dx;

		if (y <= 1)
			dy = -dy;
	}

public:
	//Ball is 10x10 square (temporary)
	void DrawBall() {
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < width; j++) {
				int p1 = i + x;
				int p2 = j + y;

				SetPixel(GRAPH, p1, p2, 0xfffff);
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
};

//class with moving platform
class Paddle {

	short int p1 = 0;
	short int position = 0;
	bool right = false;
	bool left = false;
	short int speed = 5;
	short int height = 5;
	short int width = 50;

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
		else if (position > 400)
			position = 400;
	}

	void DrawPaddle()
	{
		for (int i = 0; i < width; i++) {
			for (int j = 470 ; j < 470 + height; j++) {
				int p1 = position + i;

				SetPixel(GRAPH, p1, j, 0xfffff);
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

class Block {
	short int x; // x is left
	short int y; // y is top
	int length;
	int width;
	short int right;
	short int bottom;

public:

	Block();

	Block(int block_x, int block_y, int block_length, int block_width)
	{
		this->x = block_x;
		this->y = block_y;
		this->length = block_length;
		this->width = block_width;
		this->right = block_x + block_width;
		this->bottom = block_y + block_length;
	}

	void DrawBlock() {
		int p1 = x + width;
		int p2 = y + length;

		for (int x = this->x; x < p1; x++) {
			for (int y = this->y; y < p2; y++) {
				SetPixel(GRAPH, x, y, 0xfffff);
			}
		}
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
	}

	short int getY() const {
		return y;
	}

	void setY(short int y) {
		this->y = y;
	}
};

class GUI {

};

pthread_t tID;

int Jxt = 0, Jyt = 0, Jx = 0, Jy = 0, Jz = 0, JRz = 0;

char *fbname;
int FrameBufferFD, inputEventsFD, inputJoyFD;
struct fb_fix_screeninfo fix_info;
struct fb_var_screeninfo var_info;
void *framebuffer;

#endif /* SRC_MAIN_H_ */
