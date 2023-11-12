
#ifndef ANIMATION_HW4_H
#define ANIMATION_HW4_H

#include "helper_HW4.h"
#include <cstdlib>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

class ANIMATION_HW4 {

public:
	static bool calc_animation_doorSwing(bool door_moving);
	static bool calc_animation_windowShades(bool window_shade_moving);
	static bool calc_animation_orb(bool orb_moving, bool collision, int random);
	static void calc_cauldron_glow(bool claudron_glowing, bool collision, int random);

	static void draw_door(bool selecting);
	static void draw_window_shades(bool selecting);		
	static void draw_orb(int random);	
	static void draw_cauldron_glow();	
	static void draw_cauldron(bool cauldron_Collison);

	static void flash_light(float eye_x, float eye_y, float eye_z,
		float camera_angle_h, bool ceiling_light_on, bool flash_light_on);
	static void reset();

private:

};

#endif
