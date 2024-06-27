#include<stdio.h>
#include<graphics.h>
#include"tools.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 800

struct jinWenStr {
	int x, y;
	int color;
	bool show;
	char msg[64];
};

struct jinWenStr strs[100];//经文
int curIndex = -1;


int gongDeCount = 0;
int color;
IMAGE imgMuyu[9];
//100 98 96 94 92 94 96 98 100

bool pressDown=false;

bool update = true;

void keyEvent() {
	ExMessage msg;
	if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN) {
		playSound("res/muyu.mp3");
		pressDown = true;
		update = true;

		curIndex = (curIndex + 1) % 20;
		strs[curIndex].show = true;
		strs[curIndex].x = msg.x;
		strs[curIndex].y = msg.y;


		gongDeCount += 1;
	}
}



void loadJinWen() {
	for (int i = 0; i < 100; i++) {
		strcpy(strs[i].msg, "功德+1");
		strs[i].color = WHITE; // OxFFFFFF
		strs[i].show = false;
	}
}

void init() {
	//加载木鱼图片
	loadimage(&imgMuyu[0], "res/muyu.jpg");
	int width = imgMuyu[0].getwidth();
	int height = imgMuyu[0].getheight();
	float k = 1;
	for (int i = 0; i <4; i++) {
		k -= 0.02;
		loadimage(&imgMuyu[i], "res/muyu.jpg", width * k, height * k, true);
	}
	for (int i = 4; i < 9; i++) {
		k += 0.02;
		loadimage(&imgMuyu[i], "res/muyu.jpg", width * k, height * k, true);
	}

	loadJinWen();
	
	//创建窗口界面
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	

}

void initStr(struct jinWenStr* str) {
	str->show = false;
	str->color = WHITE; // 使用定义的WHITE
	str->x = 0; 
	str->y = 0; 
	strcpy(str->msg, "功德+1"); // 确保消息初始化
}

void updateWindow() {
	BeginBatchDraw();//开始双缓冲，解决闪现问题

	setbkcolor(BLACK);//设置背景颜色
	cleardevice();//使用背景颜色来清除窗口

	if (pressDown) {
		static int index = 0;
		int x = (WIN_WIDTH - imgMuyu[index].getwidth()) / 2;
		int y = (WIN_HEIGHT - imgMuyu[index].getheight()) / 2;
		putimage(x, y, &imgMuyu[index]);
		index++;

		if (index == 9) {
			pressDown = false;
			index = 0;
		}
	}
	else {
		int x = (WIN_WIDTH - imgMuyu[0].getwidth()) / 2;
		int y = (WIN_HEIGHT - imgMuyu[0].getheight()) / 2;

		putimage(x, y, &imgMuyu[0]);
	}

	//功德字体
	setFont("微软雅黑", 0, 40);
	setbkmode(TRANSPARENT);//字体背景透明
	//设置字体
	setcolor(WHITE);
	setFont("Segoe UI Black",0,60 );
	char str[16];
	sprintf_s(str, sizeof(str), "%d", gongDeCount);
	int x = (WIN_WIDTH - strlen(str) * 30) / 2;
	outtextxy(x, 100, str);

	//经文
	for (int i = 0; i < 100; i++) {
		if (strs[i].show) {
			settextcolor(strs[i].color);
			settextcolor(strs[i].color);
			outtextxy(strs[i].x, strs[i].y, strs[i].msg);
			strs[i].color -= 0x010101;
			strs[i].y -= 2;

			
			 if (strs[i].color == 0) {
				initStr(&strs[i]);
			}
			
		}
	}

	//结束双缓冲
	EndBatchDraw();

}


int main(void) {
	//项目初始化
	init();

	int timer = 0;
	while (1) {
		keyEvent();
		timer += getDelay();

		if (timer > 10) {
			update = true;
			timer = 0;
		}

		if (update) {
			updateWindow();
			update = false;
		}

	//updateWindow();//渲染窗口（窗口显示）

	//Sleep(10);

	}
	
	
	return 0;
}