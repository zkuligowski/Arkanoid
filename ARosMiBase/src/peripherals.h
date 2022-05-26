#ifndef peri_CL
#define peri_CL


//buttons
#define BUTTON_START 0x20
#define BUTTON_SELECT 0x10

#define BUTTON_L1 0x1
#define BUTTON_R1 0x2
#define BUTTON_L2 0x4
#define BUTTON_R2 0x8

#define BUTTON_1 0x100
#define BUTTON_2 0x200
#define BUTTON_3 0x400
#define BUTTON_4 0x800

#define SetPixel(Pointer,x,y,z) Pointer[x+y*640]=z;

struct JoY {
	int ButtonStates;
	long AxisX;
	long AxisY;
	long AxisZ;
	long AxisR;
	long Hat;
};

int checkKey(int code);
int getKey();
#endif
