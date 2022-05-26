#include "main.h"
#include "peripherals.h"
#include "utilities.h"

#define RPiLAB

int main(int argc, char *argv[]) {
	SystemInit();
	DataPrepare();
	while (1) {
		UpdateIO();
		PrintDiagnosticInfo();
		ClearScreen();
		DrawObjects();
		usleep(1000);
	}
}


void* TimerThread(void* arguments)
{
    struct timespec destTime;
    clock_gettime(CLOCK_MONOTONIC,&destTime);
	while(1)
		{
		destTime.tv_nsec+=1000000;
		if(destTime.tv_nsec>=1E9)
		{
			destTime.tv_nsec-=1E9;
			destTime.tv_sec++;
		}
		globalTimer_ms++;
		if(!(globalTimer_ms%100)) flash_ligth=0xFF;
 	    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &destTime, NULL);
		}
return NULL;
}

void SystemInit() {
	FrameBufferFD = open("/dev/fb0", O_RDWR);
	ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info);
	framebuffer = mmap(NULL, fix_info.line_length * 480, PROT_READ | PROT_WRITE,MAP_SHARED, FrameBufferFD, 0);
	inputEventsFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
#ifdef RPiLAB
	inputJoyFD= open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
#else
	inputJoyFD=0;
#endif
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	startTime_ms=tTime.tv_sec*1000+tTime.tv_usec/1000;
}

void PrintDiagnosticInfo(){
	struct timeval tTime;
	gettimeofday(&tTime,NULL);
	long TimeDiff=(tTime.tv_sec*1000+tTime.tv_usec/1000)-startTime_ms;
	long actTime=globalTimer_ms;
	if((frame_count%20)==0) printf("%i:: %li:%li=>%li KEYS: %i, %i, %i, %i, %x\n",frame_count,actTime,TimeDiff,actTime-TimeDiff,getKey(), Jx, Jy,JRz,JoYAct.ButtonStates);
}

void UpdateIO() {

	struct input_event ev;
	while (read(inputEventsFD, &ev, sizeof ev) > 0) {
		if (ev.type == EV_KEY) {
			switch (ev.value) {
			case 1:
				gRawKeys[0] = ev.code;
				break;
			case 0:
				gRawKeys[0] = 0;
				break;
			default:
				break;
			}
#ifndef RPiLAB
				switch (ev.code) {
				case KEY_KP4: JoYAct.AxisX =-127*(ev.value&1); break;
				case KEY_KP6: JoYAct.AxisX =127*(ev.value&1); break;
				case KEY_KP8: JoYAct.AxisY =-127*(ev.value&1); break;
				case KEY_KP2: JoYAct.AxisY =127*(ev.value&1); break;
				case KEY_RIGHT:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_2;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_2;
					break;
				case KEY_LEFT:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_4;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_4;
					break;
				case KEY_UP:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_1;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_1;
					break;
				case KEY_DOWN:
					if(ev.value == 1) JoYAct.ButtonStates |=BUTTON_3;
					if(ev.value == 0) JoYAct.ButtonStates &=~BUTTON_3;
					break;
				default:
					break;
				}
#endif
		}

	}
#ifdef RPiLAB
	struct js_event ev2;
			while (read(inputJoyFD, &ev2, sizeof ev2) > 0) {
					if (ev2.type & JS_EVENT_AXIS) {
						switch (ev2.number) {

						case 1:
							JoYAct.AxisY = ev2.value >> 8;		break;
						case 2:
							JoYAct.AxisX = ev2.value >> 8;		break;
						case 3:
							JoYAct.AxisZ = ev2.value >> 8;		break;
						case 4:
							JoYAct.AxisR = ev2.value >> 8;		break;
						default:
							break;
						}

					}
					if (ev2.type & JS_EVENT_BUTTON) {
						if (ev2.value)
							JoYAct.ButtonStates |= (1 << ev2.number);
						else
							JoYAct.ButtonStates &= ~(1 << ev2.number);
					}

}
#endif

}

void ClearScreen() {

	unsigned int bckgmask =getKey()>>2;

	int stage_max= -JRz/20;
	if (stage_max < 1)		stage_max = 1;
	if (stage_max > 9)		stage_max = 9;

	if (JoYAct.ButtonStates & BUTTON_SELECT)
		stage_max = 24;

	stage++;
	for (int a = stage % stage_max; a < (640 * 480); a += stage_max) {
		((u_int32_t*) framebuffer)[fix_info.line_length / 4 * (a / 640)
				+ a % 640] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1) | bckgmask;
	}
}
void DrawObjects() {
		frame_count++;
		if (getKey() == 75) polozenie--;
		else if (getKey() == 77) polozenie++;

		if (polozenie < 0) polozenie = 0;
		else if(polozenie > 400) polozenie = 400;


			for (int i = 0; i < 50; i++){
						for (int j = 475; j < 480; j++){
							int p1 = polozenie + i;



							SetPixel(GRAPH, p1, j, 0xfffff);
						}
					}
		DrawBall(ballx,bally);
		MoveBall();



/*
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++){
			int p1 = i + xx;
			int p2 = j + yy;
			SetPixel(GRAPH, p1, p2, 0xfffff);
		}
	}
	xx+=dxx;
	yy+=dyy;
	if(xx==150 || xx==0)dxx=-dxx;
	if(yy==100 || yy==0)dyy=-dyy;
*/

}
void DataPrepare() {
	for (unsigned char a = 0; a < sizeof(struct JoY); a++)
		((char*) &JoYAct)[a] = 0;
	ActMaxObj = MaxObj;

	for (int a = 0; a < MaxObj; a++) {
		do {
			s[a] = randr(0x1f) + 1;
			xt[a] = x[a] = randr(619 * 16 - s[a]);
			yt[a] = y[a] = randr(479 * 16 - s[a]);
			int spd = randr(15) + 7;
			dx[a] = (x[a] - 320 * 16) * spd;
			dy[a] = (y[a] - 240 * 16) * spd;

			while (abs(dx[a]) > (9) || abs(dy[a]) > (9)) {
				dx[a] /= 3;
				dy[a] /= 3;
			}
		} while ((abs(dy[a]) + abs(dx[a])) <= 4);
	}
}


void DrawBall(int x, int y)
{
	for(int i = 0; i < 10; i++)
	{
		for(int j = 0; j < 10; j++)
		{
			int p1 = i + x;
			int p2 = j + y;

			SetPixel(GRAPH, p1, p2, 0xfffff);
		}
	}

}

void MoveBall()
{


	ballx += balldx;
	bally += balldy;

	if(ballx >= 630 || ballx <= 1) balldx = -balldx;
	if(bally >= 470 || bally <= 1) balldy = -balldy;

}


