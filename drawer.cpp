// 绘制相关
#include "Angel.h"
#include "drawer.h"
#include "utils.h"
#include "texture.h"
#include "Camera.h"

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")
# define  pi  3.14159265
# define  black  0 ,  0 ,  0
# define  white  1.0 ,  1.0 ,  1.0
# define  green  0.0 ,  0.5 ,  0.0
# define  red    0.8 ,  0.0 ,  0.0
# define  gray   0.5 ,  0.5, 0.5
# define  wall   190 / 255.0  , 190 / 255.0  , 190 / 255.0
# define pink    228 / 255.0, 147/255.0, 212.0 /255.0
# define  gold   10.0,215.0/255.0,0.0
# define  brown  210.0/255.0, 105.0/255.0,  30.0/255.0
# define  nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define  men   244.0/255.0 ,164.0/255.0 , 96.0/255.0
# define  menba   139.0/255.0 ,69.0/255.0,19.0/255.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0
# define morning 214 / 255.0 , 240 / 255.0 , 255/255.0, 0.8
# define night 40 / 255.0, 40 / 255.0 , 79 / 255.0, 0.15

using namespace std;

int temp = 0;

double coor[8][3];             // 长方体
double san[8][3];              // 梯形

GLuint texture;
bool ballFlag;
bool isNight = false; // 夜晚标志

int mainWindowMenu;
int mainWindowSubmenu;

int jump = 0; // 跳跃标志
bool bearDead = false; // 熊的坠崖标志
bool ballDead = false; // 球的坠崖标志
//设置材质
GLfloat sca[3] = { 1.5, 1.5, 1.5 };
GLfloat tra[3] = { -300, 0, -470 };

Camera camera;

//梯形顶点坐标
void cons(double x, double y, double z, double x1, double y1, double z1) {
	san[0][0] = x;
	san[0][1] = y;
	san[0][2] = z;     //  第0个点

	san[1][0] = x;
	san[1][1] = y;
	san[1][2] = z + z1;   //  第1个点

	san[4][0] = x;
	san[4][1] = y + y1;
	san[4][2] = z;     //  第4个点

	san[5][0] = x;
	san[5][1] = y + y1;
	san[5][2] = z + z1 / 2;      //  第5个点
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			san[3][i] = san[0][i] + x1;
			san[2][i] = san[1][i] + x1;
			san[6][i] = san[4][i] + x1;
			san[7][i] = san[5][i] + x1;
		}
		else {
			san[3][i] = san[0][i];
			san[2][i] = san[1][i];
			san[6][i] = san[4][i];
			san[7][i] = san[5][i];
		}
	}
}

void box(double x, double y, double z, double x1, double y1, double z1) { //长方体
	coor[0][0] = x;
	coor[0][1] = y;
	coor[0][2] = z;        //  第0个点

	coor[1][0] = x;
	coor[1][1] = y;
	coor[1][2] = z + z1;     //  第一个点

	coor[2][0] = x + x1;
	coor[2][1] = y;
	coor[2][2] = z + z1;     //  第二个点

	coor[3][0] = x + x1;
	coor[3][1] = y;
	coor[3][2] = z;        //  第三个点
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (j == 1)
				coor[i + 4][j] = coor[i][j] + y1;
			else
				coor[i + 4][j] = coor[i][j];
		}
	}
}
// 绘制梯形
void createPolygon() { 
	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glEnd();   //     下底

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     左面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glEnd();   //     右面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[2][0], san[2][1], san[2][2]);
	glVertex3f(san[1][0], san[1][1], san[1][2]);
	glEnd();   //     前面

	glBegin(GL_POLYGON);
	//glColor3f(green);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(san[0][0], san[0][1], san[0][2]);
	glVertex3f(san[3][0], san[3][1], san[3][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glEnd();   //     后面

	glBegin(GL_POLYGON);
	//glColor3f(red);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(san[4][0], san[4][1], san[4][2]);
	glVertex3f(san[7][0], san[7][1], san[7][2]);
	glVertex3f(san[6][0], san[6][1], san[6][2]);
	glVertex3f(san[5][0], san[5][1], san[5][2]);
	glEnd();   //     上面
}
// 绘制正方体
void build() { 
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(coor[0][0], coor[0][1], coor[0][2]);
	glVertex3f(coor[1][0], coor[1][1], coor[1][2]);
	glVertex3f(coor[2][0], coor[2][1], coor[2][2]);
	glVertex3f(coor[3][0], coor[3][1], coor[3][2]);
	glEnd();   //     下底

	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(coor[1][0], coor[1][1], coor[1][2]);
	glVertex3f(coor[0][0], coor[0][1], coor[0][2]);
	glVertex3f(coor[4][0], coor[4][1], coor[4][2]);
	glVertex3f(coor[5][0], coor[5][1], coor[5][2]);
	glEnd();   //     左面

	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(coor[7][0], coor[7][1], coor[7][2]);
	glVertex3f(coor[6][0], coor[6][1], coor[6][2]);
	glVertex3f(coor[2][0], coor[2][1], coor[2][2]);
	glVertex3f(coor[3][0], coor[3][1], coor[3][2]);
	glEnd();   //     右面

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(coor[5][0], coor[5][1], coor[5][2]);
	glVertex3f(coor[6][0], coor[6][1], coor[6][2]);
	glVertex3f(coor[2][0], coor[2][1], coor[2][2]);
	glVertex3f(coor[1][0], coor[1][1], coor[1][2]);
	glEnd();   //     前面

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(coor[0][0], coor[0][1], coor[0][2]);
	glVertex3f(coor[3][0], coor[3][1], coor[3][2]);
	glVertex3f(coor[7][0], coor[7][1], coor[7][2]);
	glVertex3f(coor[4][0], coor[4][1], coor[4][2]);
	glEnd();   //     后面

	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(coor[4][0], coor[4][1], coor[4][2]);
	glVertex3f(coor[7][0], coor[7][1], coor[7][2]);
	glVertex3f(coor[6][0], coor[6][1], coor[6][2]);
	glVertex3f(coor[5][0], coor[5][1], coor[5][2]);
	glEnd();   //     上面
}

/*
碰撞检测 规则：
1. 北极熊会把雪人踩扁
2. 球或北极熊走出边界会坠崖
*/
void veritfy() {
	// 熊与雪人碰撞
	if (
		(camera.ax > 215 && camera.ax < 330) &&
		(camera.az > 435 && camera.az < 510)
		) {
		camera.cx += 9999;
		cout << "Oops! 雪人被熊踩扁了！" << endl;
	}

	if (camera.ax >= 600 || camera.ax <= -400 || camera.az <= -300 || camera.az >= 660) {
		cout << "Wow! 熊坠崖了！" << endl;
		bearDead = true;
	}

	if (camera.bx >= 400 || camera.bx <= -600 || camera.bz <= -300 || camera.bz >= 660) {
		cout << "Wow! 球坠崖了！" << endl;
		ballDead = true;
	}

}

void draw() {
	if (isNight) glClearColor(night);      // 定义背景颜色
	else glClearColor(morning);      // 定义背景颜色

	glMatrixMode(GL_MODELVIEW);

	texture = load_texture("./model/snow.bmp");  //加载雪地纹理
	// 场景相关
	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);
	// 底板
	glBegin(GL_POLYGON);
	box(-200, 0, -200, 1000, 30, 1000);
	glColor3f(white);
	build();

	//纹理设置地面
	//设置材质
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);

	glEnable(GL_TEXTURE_2D);    
	glBindTexture(GL_TEXTURE_2D, texture);//雪地纹理
	glBegin(GL_QUADS);
	// 地面高30，所以这里设置31
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 31, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-200, 31, 800);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(800, 31, 800);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(800, 31, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// 擎天柱
	glColor3f(gray);
	box(250, 0, 0, 50, -1500, 50);
	build();
	// 墙
	glColor3f(wall);
	box(320, 30, -50, 10, 100, 220);
	build();
	box(460, 30, -50, 10, 100, 220);
	build();
	box(320, 30, -50, 150, 100, 220);
	build();
	box(320, 30, -50, 150, 100, 220);
	build();
	// 门
	glColor3f(men);
	box(360, 10, 170, 40, 90, 5);
	build();              //门面
	glColor3f(menba);
	box(360, 60, 171, 5, 5, 5);
	build();              //门把手
	// 顶棚
	glColor3f(gray);
	box(320, 130, -50, 150, 10, 220);
	build();
	// 房顶
	glColor3f(white);
	cons(310, 133, 60, 170, 40, 130);
	createPolygon();
	cons(310, 133, 60, 170, 40, -130);
	createPolygon();

	// 太阳/月亮
	if (isNight) glColor4f(1.0, 248 /255.0, 248/255.0, 0.9);
	else glColor4f(gold, 0.9); // 第二个参数为透明度
	glTranslatef(600, 400, 100);
	glutSolidSphere(50, 30, 30);
	glTranslatef(-600, -400, -100);
	// 雪人躯干
	glColor3f(white);
	glTranslatef(100 - camera.cx, 30, 0);
	glutSolidSphere(30, 20, 30);
	glTranslatef(-100 + camera.cx, -30, 0);

	glTranslatef(100 - camera.cx, 70, 0);
	glutSolidSphere(20, 20, 30);
	glTranslatef(-100 + camera.cx, -70, 0);

	glColor3f(red);
	glTranslatef(100 - camera.cx, 55, 28);
	glutSolidSphere(3, 20, 30);
	glTranslatef(-100 + camera.cx, -55, -28);
	glTranslatef(100 - camera.cx, 45, 33);
	glutSolidSphere(3, 20, 30);
	glTranslatef(-100 + camera.cx, -45, -33);
	// 雪人眼睛
	glColor3f(black);
	glTranslatef(95 - camera.cx, 75, 18);
	glutSolidSphere(5, 20, 30);
	glTranslatef(-95 + camera.cx , -75, -18);

	glTranslatef(110 -camera.cx , 75, 18);
	glutSolidSphere(5, 20, 30);
	glTranslatef(-110 + camera.cx, -75, -18);
	// 雪人双手
	glColor3f(nbrown);
	cons(100, 50, 0, 50, 5, 10);
	createPolygon();
	cons(100, 50, 0, -50, 5, 10);
	createPolygon();

	// 北极熊躯干
	glColor3f(white);
	glTranslatef(200 - camera.ax, 55 - camera.ay, 450 - camera.az);
	box(150, 30, 0, 50, 90, 50);
	build();
	glTranslatef(-200 + camera.ax, -55 + camera.ay, -450 + camera.az); // 身体

	glTranslatef(375 - camera.ax, 98 - camera.ay, 476 - camera.az);
	glutSolidSphere(41, 30, 30);
	glTranslatef(-375 + camera.ax, -98 + camera.ay, -476 + camera.az); // 肚子

	glTranslatef(375 - camera.ax, 200 - camera.ay, 475 - camera.az);
	glutSolidSphere(35, 30, 30);
	glTranslatef(-375 + camera.ax, -200 + camera.ay, -475 + camera.az); // 头
	// 北极熊眼睛
	glColor3f(black);
	glTranslatef(365 - camera.ax, 205 - camera.ay, 505 - camera.az);
	glutSolidSphere(5, 20, 30);
	glTranslatef(-365 + camera.ax, -205 + camera.ay, -505 + camera.az);

	glTranslatef(382 - camera.ax, 205 - camera.ay, 506 - camera.az);
	glutSolidSphere(5, 20, 30);
	glTranslatef(-382 + camera.ax, -205 + camera.ay, -506 + camera.az);
	// 北极熊嘴巴
	glColor3f(black);
	glTranslatef(375 - camera.ax, 192 - camera.ay, 500 - camera.az);
	glutSolidSphere(13, 20, 30);
	glTranslatef(-375 + camera.ax, -192 + camera.ay, -500 + camera.az);
	// 北极熊耳朵 
	glColor3f(white);
	glTranslatef(391 - camera.ax, 230 - camera.ay, 490 - camera.az);
	glutSolidSphere(13, 20, 30);
	glTranslatef(-391 + camera.ax, -230 + camera.ay, -490 + camera.az);
	glTranslatef(355 - camera.ax, 230 - camera.ay, 490 - camera.az);
	glutSolidSphere(13, 20, 30);
	glTranslatef(-355 + camera.ax, -230 + camera.ay, -490 + camera.az);
	// 北极熊双手 
	glColor3f(white);
	glTranslatef(0 - camera.ax, 0 - camera.ay, 0 - camera.az);
	cons(375, 140, 480, 60, 10, 10);
	createPolygon();
	cons(385, 140, 480, -60, 10, 10);
	createPolygon();
	glTranslatef(0 + camera.ax, 0 + camera.ay, 0 + camera.az);

	glTranslatef(435 - camera.ax, 140 - camera.ay, 488 - camera.az);
	glutSolidSphere(16, 20, 30);
	glTranslatef(-435 + camera.ax, -140 + camera.ay, -488 + camera.az);
	glTranslatef(310 - camera.ax, 140 - camera.ay, 488 - camera.az);
	glutSolidSphere(16, 20, 30);
	glTranslatef(-310 + camera.ax, -140 + camera.ay, -488 + camera.az);
	// 北极熊双腿
	glColor3f(white);
	glTranslatef(0 - camera.ax, 0 - camera.ay, 0 - camera.az);
	cons(350, 100, 470, 20, -90, 30);
	createPolygon();
	cons(383, 100, 470, 20, -90, 30);
	createPolygon();
	glTranslatef(0 + camera.ax, 0 + camera.ay, 0 + camera.az);
	glTranslatef(392 - camera.ax, 30 - camera.ay, 486 - camera.az);
	glutSolidSphere(16, 20, 30);
	glTranslatef(-392 + camera.ax, -30 + camera.ay, -486 + camera.az);
	glTranslatef(361 - camera.ax, 30 - camera.ay, 486 - camera.az);
	glutSolidSphere(16, 20, 30);
	glTranslatef(-361 + camera.ax, -30 + camera.ay, -486 + camera.az);

	// 树干
	glColor3f(brown);
	box(60, 10, 390, 30, 120, 20);
	build();
	// 树叶
	glColor3f(white);
	glTranslatef(60, 130, 400);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(30, 0, 0);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(-15, 0, -10);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(0, 0, 20);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(0, 10, -10);
	glutSolidSphere(35.0, 60, 20);
	glTranslatef(-75, -150, -400);

	// 树干
	glColor3f(brown);
	box(560, 10, -100, 30, 120, 20);
	build();

	// 树叶
	glColor3f(white);
	glTranslatef(560, 130, -100);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(30, 0, 0);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(-15, 0, -10);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(0, 0, 20);
	glutSolidSphere(35.0, 60, 20);

	glTranslatef(0, 10, -10);
	glutSolidSphere(35.0, 60, 20);
	glTranslatef(-575, -150,  100 );

	// 球
	glColor3f(pink);
	glTranslatef(200 - camera.bx, 70 - camera.by, 450 - camera.bz);
	glutSolidSphere(30, 40, 40);
	glTranslatef(-200, -70, -450);

	glLoadIdentity();          //增加Model view矩阵
	glRotatef(camera.rotate_x, 1.0, 0.0, 0.0);
	glRotatef(camera.rotate_y, 0.0, 1.0, 0.0);
	glRotatef(camera.rotate_z, 0.0, 0.0, 1.0);


}

void timerFunction(int value)
{
	if (jump == 1) {
		ballFlag == true ? camera.by = camera.by - 30 : camera.ay -= 30;
		jump = 2;
	}
	else if (jump == 2) {
		ballFlag == true ? camera.by = camera.by + 30 : camera.ay += 30;
		jump = 0;
	}
	// 坠崖过程
	if (bearDead) {
		camera.ay += 100;
	}
	if (ballDead) {
		camera.by += 100;
	}
	
	glutPostRedisplay();
	glutTimerFunc(500, timerFunction, 1);
}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		// 小球移动
	case 'd':
		ballFlag == true ? camera.bx -= 10 : camera.ax -= 15;
		break;

	case 'a':
		ballFlag == true ? camera.bx += 10 : camera.ax += 15;
		break;
	case 's':
		ballFlag == true ? camera.bz -= 10 : camera.az -= 15;
		break;
	case 'w':
		ballFlag == true ? camera.bz += 10 : camera.az += 15;
		break;
	case ' ':
		jump = 1;
		break;
		// 绕轴旋转
	case 'q':
		camera.rotate_y += 1;
		break;
	case 'e':
		camera.rotate_y -= 1;
		break;
	case 'z':
		camera.rotate_x += 1;
		break;
	case 'c':
		camera.rotate_x -= 1;
		break;
	}
	veritfy(); // 碰撞检测
	// 重绘
	glutPostRedisplay();
}
// 菜单回调函数
void mainWindowMenuEvents(int menuChoice)
{
	switch (menuChoice) {
	case MENU_BALL:
		ballFlag = true;
		break;
	case  MENU_BEAR:
		ballFlag = false;

		break;
	case  MENU_NIGHT:
		isNight = true;
		break;
	case MENU_MORNING:
		isNight = false;

		break;

	}
	// 标记mainWindow主窗口进行重绘
	glutPostRedisplay();
}


// 创建和设置主窗口菜单
void mainWindowSetupMenu()
{
	// 创建主菜单
	mainWindowMenu = glutCreateMenu(mainWindowMenuEvents);
	glutAddMenuEntry("Choose bear", MENU_BEAR);
	glutAddMenuEntry("Choose ball", MENU_BALL);
	glutAddMenuEntry("Night", MENU_NIGHT);
	glutAddMenuEntry("Morning", MENU_MORNING);
	// 关联鼠标右键激活菜单
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}