#include <stdio.h>
#include <graphics.h>
#include <Windows.h>

int getDelay() {
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();
	if (lastTime == 0) {
		lastTime = currentTime;
		return 0;
	}
	else {
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;
	}
}

void  preLoadSound(const char* name) {
	char cmd[512];
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
	mciSendString(cmd, 0, 0, 0);
	sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
	mciSendString(cmd, 0, 0, 0);
}

void  playSound(const char* name) {
	static int index = 1;
	char cmd[512];

	if (index == 1) {
		sprintf_s(cmd, sizeof(cmd), "play %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-2", name, name);
		mciSendString(cmd, 0, 0, 0);
		index++;
	}
	else if (index == 2) {
		sprintf_s(cmd, sizeof(cmd), "play %s-2", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "close %s-1", name);
		mciSendString(cmd, 0, 0, 0);
		sprintf_s(cmd, sizeof(cmd), "open %s alias %s-1", name, name);
		mciSendString(cmd, 0, 0, 0);
		index = 1;
	}
}

void setFont(const char* fontName, int fontWidth, int fontHeight) {
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = fontHeight;                      // ��������߶�Ϊ 48
	f.lfWidth = fontWidth;
	strcpy(f.lfFaceName, fontName);    // ��������Ϊ�����塱(�߰汾 VC �Ƽ�ʹ�� _tcscpy_s ����)
	f.lfQuality = ANTIALIASED_QUALITY;    // �������Ч��Ϊ�����  
	settextstyle(&f);
}