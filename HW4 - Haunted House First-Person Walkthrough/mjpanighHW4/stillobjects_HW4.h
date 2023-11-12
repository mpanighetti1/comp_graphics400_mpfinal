
#ifndef STILLOBJECTS_HW4_H
#define STILLOBJECTS_HW4_H

#include "helper_HW4.h"
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#include <vector>
#define PI 3.14159

class STILLOBJECTS_HW4 {

public:
	static void draw_background(bool ceiling_light_on);
	static void draw_structure();
	static void draw_ceiling_light(bool ceiling_light_on);
	static void draw_light_switch(bool selecting, bool ceiling_light_on);
	static void draw_table();
	static void outdoor_light(bool outdoor_light_on);	

private:

};

#endif
