#pragma once
#include "Angel.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")
const int MENU_BALL = 0;
const int MENU_BEAR = 1;
const int MENU_NIGHT = 2;
const int MENU_MORNING = 3;


void cons(double x, double y, double z, double x1, double y1, double z1); // 梯形顶点坐标
void box(double x, double y, double z, double x1, double y1, double z1); // 长方体顶点坐标
void build(); // 绘制长方体
void createPolygon(); // 绘制梯形

void draw();

void timerFunction(int value);
void Keyboard(unsigned char key, int x, int y);
// 菜单回调函数
void mainWindowMenuEvents(int menuChoice);
// 创建和设置主窗口菜单
void mainWindowSetupMenu();