#include "stdlib.h"
#include<iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "utils.h"
#include "texture.h"
#include "drawer.h"
#include "Angel.h"
#include "mesh.h"
#include "FreeImage.h"
#include "Mesh_Painter.h"
// 窗口宽高
GLfloat w = 1000;
GLfloat h = 1000;

using namespace std;
# define  black  0 ,  0 ,  0
# define  white  1.0 ,  1.0 ,  1.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0
# define sky 40 / 255.0, 40 / 255.0 , 79 / 255.0, 0.15

static GLfloat angle = 0.0f;   //旋转角度
std::vector<My_Mesh*> my_meshs;
Mesh_Painter*			mp_;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mp_->draw_meshes();
	draw(); // 绘制模型
	glFlush(); 
	glutSwapBuffers();
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.5 };;//光源位置
GLfloat light_position[] = { 1.0, 1.0, 0, 1.0 };;//光源位置
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void)
{
	GLfloat sun_direction[] = { 600.0, 400.0, 100.0, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };

	glEnable(GL_LIGHTING);              // 环境光
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	//glLightModelfv(GL_AMBIENT, ambient_intensity);
	glEnable(GL_LIGHT0);                // 漫反射
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); // 使光照在纹理上更逼真
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);// 光源位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity); // 光照强度

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	cout << "The OpenGL version is: " << glGetString(GL_VERSION) << "\n";
	cout << glGetString(GL_VENDOR) << "\n";
	glLineWidth(5);

	glEnable(GL_BLEND); // 打开混合
	glDisable(GL_DEPTH_TEST); // 关闭深度测试
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // 基于源象素alpha通道值的半透明混合函数
	glEnable(GL_DEPTH_TEST); //打开深度测试

	glMatrixMode(GL_PROJECTION);     // 接下来视角有关的定义
	glOrtho(-w, w, -h, h, -w , w); // 正交投影orthographic projection 
}

int main(int argc, char** argv)    //  main函数
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("2017132090");
	// glewExperimental = GL_TRUE;
	glewInit();
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);    // 启用纹理
	// glewExperimental = GL_TRUE;
	glewInit();
	mp_ = new Mesh_Painter;

	My_Mesh* my_mesh2 = new My_Mesh;
	my_mesh2->load_obj("model/yellowpeople.obj");
	my_mesh2->set_texture_file("model/yellowpeople.jpg");
	my_mesh2->set_translate(-0.8, 0.8, 0.2);//平移
	my_mesh2->set_theta(0., 180., 0.);//旋转轴
	my_mesh2->set_theta_step(0, 30, 0);//旋转速度
	my_meshs.push_back(my_mesh2);
	mp_->add_mesh(my_mesh2);

	mp_->init_shaders("./shader/v_texture.glsl", "./shader/f_texture.glsl");
	mp_->update_vertex_buffer();
	mp_->update_texture();

	glutDisplayFunc(display);
	mainWindowSetupMenu();
	//glutMotionFunc(myMouseMotion); //调用鼠标移动函数
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(500, timerFunction, 1);    //注册定时器
	glutMainLoop();
	system("pause");
	return 0;
}

