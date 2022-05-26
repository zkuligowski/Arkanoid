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
volatile int flash_ligth=0;
volatile long globalTimer_ms=0;
long startTime_ms;
int frame_count = 0;
int xx=0;
int yy=0;
int dxx=1;
int dyy=1;

int p1 = 0;
int polozenie = 0;

short int balldx = 1;
short int balldy = 1;
short int ballx = 100;
short int bally = 50;

pthread_t tID;

int Jxt = 0, Jyt = 0, Jx = 0, Jy = 0, Jz = 0, JRz = 0;


char *fbname;
int FrameBufferFD, inputEventsFD, inputJoyFD;
struct fb_fix_screeninfo fix_info;
struct fb_var_screeninfo var_info;
void *framebuffer;

#endif /* SRC_MAIN_H_ */
