// 工具集合
#include <math.h>
#include "utils.h"
#include<gl/glut.h>
# define  pi  3.14159265
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };  //材质参数：镜面反射，所得到的光的强度（颜色）
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };  //材质本身就微微的向外发射光线
void setMetiral(GLfloat matiral_diffuse_ambient[4]) // 设置材质以及镜面反射
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient); //表面更逼真
	//设置参数
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);  //镜面反射，所得到的光的强度（颜色）
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);  //材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色 
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 64);   //“镜面指数”（0~128） 该值越小，材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
}

void drawSphere(double r, int lats, int longs, double x, double y, double z) {  //圆
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
