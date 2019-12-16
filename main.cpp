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
// ���ڿ��
GLfloat w = 1000;
GLfloat h = 1000;

using namespace std;
# define  black  0 ,  0 ,  0
# define  white  1.0 ,  1.0 ,  1.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0
# define sky 40 / 255.0, 40 / 255.0 , 79 / 255.0, 0.15

static GLfloat angle = 0.0f;   //��ת�Ƕ�
std::vector<My_Mesh*> my_meshs;
Mesh_Painter*			mp_;


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mp_->draw_meshes();
	draw(); // ����ģ��
	glFlush(); 
	glutSwapBuffers();
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
//GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.5 };;//��Դλ��
GLfloat light_position[] = { 1.0, 1.0, 0, 1.0 };;//��Դλ��
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void)
{
	GLfloat sun_direction[] = { 600.0, 400.0, 100.0, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };

	glEnable(GL_LIGHTING);              // ������
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	//glLightModelfv(GL_AMBIENT, ambient_intensity);
	glEnable(GL_LIGHT0);                // ������
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); // ʹ�����������ϸ�����
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);// ��Դλ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity); // ����ǿ��

	glEnable(GL_COLOR_MATERIAL);        // Configure glColor().
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	cout << "The OpenGL version is: " << glGetString(GL_VERSION) << "\n";
	cout << glGetString(GL_VENDOR) << "\n";
	glLineWidth(5);

	glEnable(GL_BLEND); // �򿪻��
	glDisable(GL_DEPTH_TEST); // �ر���Ȳ���
	glBlendFunc(GL_SRC_ALPHA, GL_ONE); // ����Դ����alphaͨ��ֵ�İ�͸����Ϻ���
	glEnable(GL_DEPTH_TEST); //����Ȳ���

	glMatrixMode(GL_PROJECTION);     // �������ӽ��йصĶ���
	glOrtho(-w, w, -h, h, -w , w); // ����ͶӰorthographic projection 
}

int main(int argc, char** argv)    //  main����
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
	glEnable(GL_TEXTURE_2D);    // ��������
	// glewExperimental = GL_TRUE;
	glewInit();
	mp_ = new Mesh_Painter;

	My_Mesh* my_mesh2 = new My_Mesh;
	my_mesh2->load_obj("model/yellowpeople.obj");
	my_mesh2->set_texture_file("model/yellowpeople.jpg");
	my_mesh2->set_translate(-0.8, 0.8, 0.2);//ƽ��
	my_mesh2->set_theta(0., 180., 0.);//��ת��
	my_mesh2->set_theta_step(0, 30, 0);//��ת�ٶ�
	my_meshs.push_back(my_mesh2);
	mp_->add_mesh(my_mesh2);

	mp_->init_shaders("./shader/v_texture.glsl", "./shader/f_texture.glsl");
	mp_->update_vertex_buffer();
	mp_->update_texture();

	glutDisplayFunc(display);
	mainWindowSetupMenu();
	//glutMotionFunc(myMouseMotion); //��������ƶ�����
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(500, timerFunction, 1);    //ע�ᶨʱ��
	glutMainLoop();
	system("pause");
	return 0;
}

