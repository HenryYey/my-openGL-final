#pragma once
#include "Angel.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")
const int MENU_BALL = 0;
const int MENU_BEAR = 1;
const int MENU_NIGHT = 2;
const int MENU_MORNING = 3;


void cons(double x, double y, double z, double x1, double y1, double z1); // ���ζ�������
void box(double x, double y, double z, double x1, double y1, double z1); // �����嶥������
void build(); // ���Ƴ�����
void createPolygon(); // ��������

void draw();

void timerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
// �˵��ص�����
void mainWindowMenuEvents(int menuChoice);
// ���������������ڲ˵�
void mainWindowSetupMenu();