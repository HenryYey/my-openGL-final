// ���߼���
#include <math.h>
#include "utils.h"
#include<gl/glut.h>
# define  pi  3.14159265
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  //���ʲ��������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };  //���ʱ����΢΢�����ⷢ�����
void setMetiral(GLfloat matiral_diffuse_ambient[4]) // ���ò����Լ����淴��
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient); //���������
	//���ò���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);  //���淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);  //���ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ 
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 64);   //������ָ������0~128�� ��ֵԽС������Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
}

void drawSphere(double r, int lats, int longs, double x, double y, double z) {  //Բ
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = pi * (-0.5 + (double)(i - 1) / lats);   // M_PI
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = pi * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		glScaled(100, 100, 100);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * pi * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(zr0, zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(zr1, zr1, z1);
		}
		glEnd();
	}
}
