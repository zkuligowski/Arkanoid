#include "main.h"
#include "peripherals.h"
#include "utilities.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Game.h"
#include "GUI.h"
#include "Font.h"


#include <list>


#define RPiLAB
using namespace std;

int main(int argc, char *argv[]) {
	SystemInit();
	DataPrepare();

	Game game;
	game.StartGame();
	GUI gui1;


	Ball ball;


	Paddle paddle;

	int number_of_blocks = 36;
	Block *blocks = new Block[number_of_blocks];
	list<Block> block_list;

	unsigned int tabX[number_of_blocks] = {
			40,100,160,210,270,330,
			40,100,160,210,270,330,
			40,100,160,210,270,330,
			40,100,160,210,270,330,
			40,100,160,210,270,330,
			40,100,160,210,270,330,

	};
	unsigned int tabY[number_of_blocks] = {
			50,50,50,50,50,50,
			100,100,100,100,100,100,
			150,150,150,150,150,150,
			200,200,200,200,200,200,
			250,250,250,250,250,250,
			300,300,300,300,300,300

	};

	unsigned int tabColour[number_of_blocks] = {
			3,3,3,3,3,3,
			3,2,2,2,2,3,
			3,2,1,1,2,3,
			3,2,1,1,2,3,
			3,2,2,2,2,3,
			3,3,3,3,3,3
	};


	while (1) {
		UpdateIO();
		PrintDiagnosticInfo();
		ClearScreen();
		DrawTxt(440, 200, "POINTS:", 7);
		//DrawChar(560, 300, &Font24_Table[1872]);
		PrintInt(560, 200, game.getPoints());
		DrawTxt(420, 340, "NUM4 - LEFT", 11);
		DrawTxt(420, 380, "NUM6 - RIGHT", 12);
		DrawTxt(420, 420, "NUM0 - MENU", 11);


		if(gui1.getScreen() == 1)
		{
			gui1.SetBackground(640, 480, tab_start_screen);
		}
		else if(gui1.getScreen() == 2)
		{
			gui1.DrawLives(game.getLives(), tab_heart);
			gui1.SetLogo(tab_logo);

			if (game.isGameover() == false)
			{
				gui1.SetBackground(400, 480, tab_background1);
				paddle.MovePaddle();
				paddle.DrawPaddle();
				ball.DrawBall();
				ball.MoveBall();

				if (((ball.getY() + ball.getHeight()) >= 469) && ((ball.getY() + ball.getHeight()) <= 471))
				{
					if (ball.getX() >= paddle.getPosition() - ball.getWidth()
							&& ball.getX()
							<= paddle.getPosition() + paddle.getWidth()) {
						ball.setDy(-(ball.getDy()));

						if (getKey() == 75) {
							ball.setDx(ball.getDx() - 2);

						}
						else if (getKey() == 77)
						{
							ball.setDx(ball.getDx() + 2);
						}
					}
				}

				//THIS IS TEMPORARY
				//ONLY TO PREVENT FROM CRASH PROGRAM
				else if ((ball.getY() + ball.getHeight()) > 480) {
					ball.SpawnBall();
					game.SubstractLive();
					if (game.getLives() == 0)
						game.GameOver();
				}

				//Draw the blocks
				//and bouncing off the blocks
				int blocks_to_win = 0;
				for (auto &block_index : block_list) {

					if (block_index.getLive() >= 1) {
						block_index.DrawBlock();

						if (ball.getBottom() >= block_index.getY()
								&& ball.getY() <= block_index.getBottom()) {
							if ((ball.getX() >= block_index.getRight() - 2 && ball.getX() <= block_index.getRight() + 2)
									|| (ball.getRight() >= block_index.getX() - 2 && ball.getRight() <= block_index.getX() + 2))
							{
								if(ball.isIsFireball() == false)
								{
									ball.setDx(-(ball.getDx()));
									block_index.SubstractLive();
									game.AddPoint(1);
								}
								else
								{
									block_index.DestroyBlock();
									ball.Add_collision_counter();
									game.AddPoint(2);
									//printf("kol =  %d\n", ball.getCollisionCounter());
									if(ball.getCollisionCounter() >= 4)
									{
										ball.Reset_collision_counter();
										ball.setIsFireball(false);
									}

								}


								if(block_index.getLive() == 0)
								{
									block_index.CheckDrop();
									if(block_index.getDropNumber() == 1)
									{
										ball.setIsFireball(true);
									}
								}
							}
						}

						if (ball.getRight() > block_index.getX()
								&& ball.getX() < block_index.getRight()) {
							if ((ball.getY() >= block_index.getBottom() - 2 && ball.getY() <= block_index.getBottom() + 2)
									|| (ball.getBottom() >= block_index.getY() - 2 && ball.getBottom() <= block_index.getY() + 2)) {
								if(ball.isIsFireball() == false)
								{
									ball.setDy(-(ball.getDy()));
									block_index.SubstractLive();
									game.AddPoint(1);
								}
								else
								{
									block_index.DestroyBlock();
									ball.Add_collision_counter();
									game.AddPoint(2);
									if(ball.getCollisionCounter() >= 4)
									{
										ball.Reset_collision_counter();
										ball.setIsFireball(false);
									}
								}


								if(block_index.getLive() == 0)
								{
									block_index.CheckDrop();
									if(block_index.getDropNumber() == 1)
									{
										ball.setIsFireball(true);
									}
								}

							}
						}
					}
					blocks_to_win +=  block_index.getLive();
				}
				if(blocks_to_win == 0)
					{
						game.GameOver();
						game.setGameWon(true);
					}
			}
			else
			{
				if(game.isGameWon() == true)
				{
					gui1.SetBackground(400, 480, tab_you_win);
				}
				else if(game.getLives() == 0)
				{
					gui1.SetBackground(400, 480, tab_lostgameimage);
				}

			}
			int temp = 0;
			int temp2 = 0;
			int move_x = 0;
			if(ball.isIsFireball()== true)
			{
				for(int t = 1; t <= (4 - ball.getCollisionCounter());  t++)
				{
					temp2 = 420 + move_x;
					for (int i = temp2; i < (temp2 + ball.getHeight()); i++) {
						for (int j = 120; j < 120 + ball.getWidth(); j++) {
							if(tab_fireball[temp] != 0xffffff)
							{
								SetPixel(GRAPH, i, j, tab_fireball[temp]);
							}
							temp++;
						}
					}
					move_x = move_x + 20;
					temp = 0;
				}


			}




		}
		//printf("%d\n", game1.getLives());

		if(getKey() == 79 && gui1.getScreen() == 1) //Start new Game
		{
			gui1.setScreen(2);
			game.StartGame();
			ball.SpawnBall();
			ball.setIsFireball(false);

			for(int i = 0; i < number_of_blocks; i++)
			{
				blocks[i].setX(tabX[i]);
				blocks[i].setY(tabY[i]);;
				blocks[i].setColour(tabColour[i]);

				block_list.push_back(blocks[i]);
			}


		}
		else if(getKey() == 80 && gui1.getScreen() == 1) //Continue Game
		{
			gui1.setScreen(2);
		}
		else if(getKey() == 82 && gui1.getScreen() == 2) //Back to MENU
		{
			gui1.setScreen(1);
		}
		else if(getKey() == 55)
		{
			for (auto &block_index : block_list) {
				block_index.setLive(0);
			}
		}




		usleep(10000);
	}
}



void* TimerThread(void *arguments) {
	struct timespec destTime;
	clock_gettime(CLOCK_MONOTONIC, &destTime);
	while (1) {
		destTime.tv_nsec += 1000000;
		if (destTime.tv_nsec >= 1E9) {
			destTime.tv_nsec -= 1E9;
			destTime.tv_sec++;
		}
		globalTimer_ms++;
		if (!(globalTimer_ms % 100))
			flash_ligth = 0xFF;
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &destTime, NULL);
	}
	return NULL;
}

void SystemInit() {
	FrameBufferFD = open("/dev/fb0", O_RDWR);
	ioctl(FrameBufferFD, FBIOGET_FSCREENINFO, &fix_info);
	framebuffer = mmap(NULL, fix_info.line_length * 480, PROT_READ | PROT_WRITE,
			MAP_SHARED, FrameBufferFD, 0);
	inputEventsFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
#ifdef RPiLAB
	inputJoyFD = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);
#else
	inputJoyFD=0;
#endif
	pthread_create(&tID, NULL, TimerThread, NULL);
	struct timeval tTime;
	gettimeofday(&tTime, NULL);
	startTime_ms = tTime.tv_sec * 1000 + tTime.tv_usec / 1000;
}

void PrintDiagnosticInfo() {
	struct timeval tTime;
	gettimeofday(&tTime, NULL);
	long TimeDiff = (tTime.tv_sec * 1000 + tTime.tv_usec / 1000) - startTime_ms;
	long actTime = globalTimer_ms;
	//if((frame_count%20)==0) printf("%i:: %li:%li=>%li KEYS: %i, %i, %i, %i, %x\n",frame_count,actTime,TimeDiff,actTime-TimeDiff,getKey(), Jx, Jy,JRz,JoYAct.ButtonStates);
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
				JoYAct.AxisY = ev2.value >> 8;
				break;
			case 2:
				JoYAct.AxisX = ev2.value >> 8;
				break;
			case 3:
				JoYAct.AxisZ = ev2.value >> 8;
				break;
			case 4:
				JoYAct.AxisR = ev2.value >> 8;
				break;
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

	unsigned int bckgmask = getKey() >> 2;

	int stage_max = -JRz / 20;
	if (stage_max < 1)
		stage_max = 1;
	if (stage_max > 9)
		stage_max = 9;

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

void DrawChar(int x, int y, unsigned char *picture) {
	for (int yy = y; yy < 24 + y; yy++) {
		for (int xx = x; xx < 24 + x; xx += 8) {
			for (int i = 0; i < 8; i++) {
				if (((*picture >> i) & 0x01) == 1) {
					SetPixel(GRAPH, xx - i + 7, yy, 0xffffff);
				} else
					SetPixel(GRAPH, xx - i + 7, yy, 0);
			}
			picture++;
		}
	}
}

void DrawNum(int x, int y, char val) {
	DrawChar(x, y, &Font24_Table[1152 + val * 72]);
}

void DrawLetter(int x, int y, char val) {
	DrawChar(x, y, &Font24_Table[2376 + (val - 'A') * 72]);
}

void DrawTxt(int x, int y, char *a, unsigned char lenght) {
	for (int i = 0; i < lenght; i++) {
		if (a[i] == ' ')
			continue;
		else
			DrawLetter(x + 17 * i, y, a[i]);
	}
}

void PrintInt(int x, int y, int val) {
	int str;
	str = (int) val / 100;
	DrawNum(x, y, str);
	val = val - str * 100;
	str = (int) val / 10;
	DrawNum(x + 17, y, str);
	val = val - str * 10;
	DrawNum(x + 34, y, val);
}

