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

void DrawBall(int x, int y);
void MoveBall();

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
int xx = 0;
int yy = 0;
int dxx = 1;
int dyy = 1;

int p1 = 0;
int polozenie = 0;

//short int balldx = 1;
//short int balldy = 1;
//short int ballx = 100;
//short int bally = 50;

//class with ball
class Ball {
	short int dx = 1;
	short int dy = 1;
	short int x = 100;
	short int y = 50;

public:
	void MoveBall() {
		x += dx;
		y += dy;
		//printf("%d\n", x);

		if (x >= 630 || x <= 1)
			dx = -dx;


		if (y >= 470 || y <= 1)
			dy = -dy;



	}

public:
	//Ball is 10x10 square (temporary)
	void DrawBall() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
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
};

//class with moving platform
class Platform {

	short int p1 = 0;
	short int position = 0;
	short int right = 0;
	short int left = 0;
	short int speed = 5;

public:
	void DrawPlatform() {
		if (getKey() == 75) {
			position = position - speed;
			left = 1;
			right = 0;
		} else if (getKey() == 77) {
			position = position + speed;
			left = 0;
			right = 1;
		}

		else {
			left = 0;
			right = 0;
		}

		if (position < 0)
			position = 0;
		else if (position > 400)
			position = 400;

		for (int i = 0; i < 50; i++) {
			for (int j = 475; j < 480; j++) {
				int p1 = position + i;

				SetPixel(GRAPH, p1, j, 0xfffff);
			}
		}
	}
};

class Block {
	short int x;
	short int y;

public:
	void DrawBlock(int block_x, int block_y, int length, int width) {
		int p1 = block_x + length;
		int p2 = block_y + width;

		for (int x = block_x; x < p1; x++) {
			for (int y = block_y; y < p2; y++) {
				SetPixel(GRAPH, x, y, 0xfffff);
			}
		}
	}
};

pthread_t tID;

int Jxt = 0, Jyt = 0, Jx = 0, Jy = 0, Jz = 0, JRz = 0;

char *fbname;
int FrameBufferFD, inputEventsFD, inputJoyFD;
struct fb_fix_screeninfo fix_info;
struct fb_var_screeninfo var_info;
void *framebuffer;

#endif /* SRC_MAIN_H_ */
