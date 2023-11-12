
#ifndef SCENE_HW3_H
#define SCENE_HW3_H

#include "helper_HW3.h"
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

class SCENE_HW3 {

public:
	static void draw_background();
	static void draw_objects(float Obj1_X, float Obj1_Y, float Obj1_Z,
						   float Obj2_X, float Obj2_Y, float Obj2_Z,
						   float Obj3_X, float Obj3_Y, float Obj3_Z, int shadow);
	static void draw_cloud(int shadow);
	static void draw_lily_pad(float Lily_pad_X, float Lily_pad_Y, float Lily_pad_Z);

private:

};

#endif
