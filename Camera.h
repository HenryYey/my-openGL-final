#pragma once
#include "Angel.h"
class Camera {
public:
	// 相机视角
	double rotate_x = 25.0;
	double rotate_y = -5.0;
	double rotate_z = 0.0;
	// 熊
	GLfloat ax = 0;
	GLfloat ay = 0;
	GLfloat az = 0;
	// 球
	GLfloat bx = 0;
	GLfloat by = 0;
	GLfloat bz = 0;
	//雪人	
	GLfloat cx = 0;
};
