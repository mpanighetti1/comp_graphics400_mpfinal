
#ifndef DRAGONFLY_HW3_H
#define DRAGONFLY_HW3_H

#include "helper_HW3.h"
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

class DRAGONFLY_HW3 {

public:
	static void draw_dragonfly(int shadow);
	static void draw_dragonfly_fire();
	static void draw_dragonfly_right_wings(int shadow);
	static void draw_dragonfly_left_wings(int shadow);

private:

};

#endif
