/************************************************************************
*
* Animation File - Includes:
*   - Animation Calculations For Door Swing
*   - Animation Calculations For Shades Roll-up
*   - Animation Calculations For Orb Event
*   - Animation Calculations For Cauldron Glowing When Close
*	- Draw The Door
*	- Draw The Window Shades
*	- Draw The Orb
*	- Draw The Cylinder That Causes The "Liquidity" In Cauldron
*	- Draw Cauldron
*	- Draw Flash Light
*	- Reset All Settings For Orb Event To Default/Starting Settings
*
*************************************************************************/

#include "helper_HW4.h"
#include "animation_HW4.h"

#define FT 12.0

	// Door Animation Globals
	float door_swing_angle = 0;
	float door_swing_step = 1;
	bool door_open = false;

	// Window Shade Animation Globals
	float window_shade_size = 6.0;
	float window_shade_translate = 6.75;
	bool window_shade_open = false;
	float light5_atten_value = 4;
	float window_lightDiff[] = { 0.0, 0.0, 0.0, 0.0 };
	float window_lightSpec[] = { 0.0, 0.0, 0.0, 0.0 };
	float window_lightAmb[] = { 0.0, 0.0, 0.0, 0.0 };

	//Flash Light Materials
	float flash_glassDiffAmb[] = { 0.1, 0.1, 0.1, 0.3 };
	float flash_buttonDiffAmb[] = { 0.7, 0.7, 0.7, 0.0 };
	float flash_lightDiffAmb[] = { 0.0, 0.0, 0.0, 0.0 };
	float flash_lightSpec[] = { 1.0, 1.0, 1.0, 0.0 };
	float flash_lightShine[] = { 100.0 };

	//Flash Light Emission Portion
	float flash_light_emissionDiffAmb[] = { 1.0, 1.0, 1.0, 1.0 };

	// Orb Globals
	float orbPos_x = 18;
	float orbPos_y = 0.8;
	float orbPos_z = -8;
	float orb_rotation = 0;
	float orb_leg = 0;
	float orb_blueDiffAmb[] = { 0.0, 0.0, 1.0, 0.0 };
	float orb_blueEmiss[] = { 0.0, 0.0, 1.0 / 4, 0.0 };
	float orb_redDiffAmb[] = { 1.0, 0.0, 0.0, 0.0 };
	float orb_redEmiss[] = { 1.0 / 4, 0.0, 0.0, 0.0 };
	float orbSpec[] = { 1.0, 1.0, 1.0, 0.0 };
	float orbShine[] = { 100.0 };

	// Emission Globals
	float matGreenEmission_animation[] = { 0.0, 0.0, 0.0, 1.0 };
	float matGreenBlueEmission_animation[] = { 0.0, 0.1, 0.0, 1.0 };
	float cauldron_glowDiff_animation[] = { 0.0, 0.5, 0.0, 1.0 };
	float cauldron_glowSpec_animation[] = { 0.0, 0.5, 0.0, 1.0 };

	// Cauldron Globals
	float cauldron_glowDiff[] = { 0.0, 0.1, 0.0, 1.0 };
	float cauldron_glowSpec[] = { 0.0, 0.1, 0.0, 1.0 };

	// No 
	float NoSpec_animation[] = { 0.0, 0.0, 0.0, 0.0 };
	float NoEmission_animation[] = { 0.0, 0.0, 0.0, 0.0 };
	float NoShine_animation[] = { 0.0 };

	// Wood Material
	float matWood_animation[] = { 0.61 * 0.35, 0.3253 * 0.35, 0.0 * 0.35, 1.0 };

	// Dark Red
	float matShades_animation[] = { 0.2925 / 4, 0.39 / 4, 0.0, 1.0 };

	// Dark Grey Material
	float matConcret_animation[] = { 0.1, 0.1, 0.1, 1.0 };


bool ANIMATION_HW4::calc_animation_doorSwing(bool door_moving) {
	
	glLightfv(GL_LIGHT5, GL_DIFFUSE, window_lightDiff);
	glLightfv(GL_LIGHT5, GL_SPECULAR, window_lightSpec);
	glLightfv(GL_LIGHT5, GL_AMBIENT, window_lightAmb);
	glEnable(GL_LIGHT5);

	if (door_swing_angle != 90 && door_open == false) {
		door_swing_angle += door_swing_step;
		
		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, light5_atten_value -= 0.0055);
		window_lightDiff[0] += 0.004;
		window_lightDiff[1] += 0.004;
		window_lightDiff[2] += 0.004;
		window_lightSpec[0] += 0.004;
		window_lightSpec[1] += 0.004;
		window_lightSpec[2] += 0.004;
		window_lightAmb[0] += 0.004;
		window_lightAmb[1] += 0.004;
		window_lightAmb[2] += 0.004;
		glutPostRedisplay();
		return true;
	}
	else if (door_swing_angle != 0 && door_open == true) {
		door_swing_angle -= door_swing_step;

		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, light5_atten_value += 0.0055);
		window_lightDiff[0] -= 0.004;
		window_lightDiff[1] -= 0.004;
		window_lightDiff[2] -= 0.004;
		window_lightSpec[0] -= 0.004;
		window_lightSpec[1] -= 0.004;
		window_lightSpec[2] -= 0.004;
		window_lightAmb[0] -= 0.004;
		window_lightAmb[1] -= 0.004;
		window_lightAmb[2] -= 0.004;
		glutPostRedisplay();
		return true;
	}
	else {
		door_open = !door_open;
		glutPostRedisplay();
		return false;		
	}	
}

bool ANIMATION_HW4::calc_animation_windowShades(bool window_shade_moving) {
	
	//If the value is within range of the epsilon value, they are "close enough"
	//This accounts for floating-point arithmetic inaccuracies
	const float epsilon = 0.005;
	
	glLightfv(GL_LIGHT5, GL_DIFFUSE, window_lightDiff);
	glLightfv(GL_LIGHT5, GL_SPECULAR, window_lightDiff);
	glLightfv(GL_LIGHT5, GL_AMBIENT, window_lightDiff);
	glEnable(GL_LIGHT5);

	if (std::abs(window_shade_size - 0.5) > epsilon &&
		std::abs(window_shade_translate - 10) > epsilon &&
		window_shade_open == false) {

		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, light5_atten_value -= 0.0025);
		window_lightDiff[0] += 0.003;
		window_lightDiff[1] += 0.003;
		window_lightDiff[2] += 0.003;
		window_lightSpec[0] += 0.003;
		window_lightSpec[1] += 0.003;
		window_lightSpec[2] += 0.003;
		window_lightAmb[0] += 0.003;
		window_lightAmb[1] += 0.003;
		window_lightAmb[2] += 0.003;
		window_shade_size -= 5.5 / 200.0;
		window_shade_translate += (10 - 6.75) / 200.0;
		glutPostRedisplay();
		return true;
	}
	else if (std::abs(window_shade_size - 6.0) > epsilon &&
		std::abs(window_shade_translate - 6.75) > epsilon &&
		window_shade_open == true) {

		glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, light5_atten_value += 0.0025);
		window_lightDiff[0] -= 0.003;
		window_lightDiff[1] -= 0.003;
		window_lightDiff[2] -= 0.003;
		window_lightSpec[0] -= 0.003;
		window_lightSpec[1] -= 0.003;
		window_lightSpec[2] -= 0.003;
		window_lightAmb[0] -= 0.003;
		window_lightAmb[1] -= 0.003;
		window_lightAmb[2] -= 0.003;
		window_shade_size += 5.5 / 200.0;
		window_shade_translate -= (10 - 6.75) / 200.0;
		
		glutPostRedisplay();
		return true;
	}
	else {
		window_shade_open = !window_shade_open;
		glutPostRedisplay();
		return false;
	}
}

bool ANIMATION_HW4::calc_animation_orb(bool orb_moving, bool collision, int random) {

	//If the value is within range of the epsilon value, they are "close enough"
	//This accounts for floating-point arithmetic inaccuracies
	const float epsilon = 0.005;

	if (std::abs(orbPos_y - 5.5) > epsilon && orb_leg == 0) {

		orbPos_y += (5.5 - 0.8) / 50.0;

		glutPostRedisplay();
		return true;
	}
	else if (std::abs(orb_rotation - (- 180)) > epsilon && orb_leg == 1) {

		orb_rotation -= 180 / 40.0;

		glutPostRedisplay();
		return true;
	}
	else if (std::abs(orbPos_y - 2.7) > epsilon && orb_leg == 2) {

		orbPos_y -= (5.5 - 2.7) / 30.0;

		glutPostRedisplay();
		return true;
	}
	else if (std::abs(orbPos_y - 2) > epsilon && orb_leg == 3) {

		orbPos_y -= (3 - 2) / 100.0;

		if (random == 1) {
			matGreenBlueEmission_animation[1] -= 2 / 100.0;
			matGreenBlueEmission_animation[2] += 2 / 100.0;
			cauldron_glowDiff[1] -= 2 / 100.0;
			cauldron_glowSpec[1] -= 2 / 100.0;
			cauldron_glowDiff[2] += 2 / 100.0;
			cauldron_glowSpec[2] += 2 / 100.0;
		}
		else
		{
			matGreenBlueEmission_animation[1] -= 2 / 100.0;
			matGreenBlueEmission_animation[0] += 2 / 100.0;
			cauldron_glowDiff[1] -= 2 / 100.0;
			cauldron_glowSpec[1] -= 2 / 100.0;
			cauldron_glowDiff[0] += 2 / 100.0;
			cauldron_glowSpec[0] += 2 / 100.0;
		}

		glutPostRedisplay();
		return true;
	}
	else {
		if (orb_leg == 0) {
			orb_leg = 1;
			return true;
		}
		else if (orb_leg == 1) {
			orb_leg = 2;
			return true;
		}
		else if (orb_leg == 2) {
			orb_leg = 3;
			return true;
		}
		else {
			orb_leg = 4;
			return false;
		}		
	}
}

void ANIMATION_HW4::calc_cauldron_glow(bool claudron_glowing, bool collision,
	int random) {

	//If the value is within range of the epsilon value, they are "close enough"
	//This accounts for floating-point arithmetic inaccuracies
	const float epsilon = 0.05;

	if (orb_leg != 4) {
		if (std::abs(matGreenBlueEmission_animation[1] - 1) > epsilon
			&& std::abs(cauldron_glowDiff[1] - 1) > epsilon
			&& collision) {

			matGreenBlueEmission_animation[1] += (1 - 0.1) / 50.0;
			cauldron_glowDiff[1] += (1 - 0.1) / 50.0;
			cauldron_glowSpec[1] += (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
		else if (std::abs(matGreenBlueEmission_animation[1] - 0.1) > epsilon
			&& std::abs(cauldron_glowDiff[1] - 0.1) > epsilon
			&& !collision) {

			matGreenBlueEmission_animation[1] -= (1.0 - 0.1) / 50.0;
			cauldron_glowDiff[1] -= (1 - 0.1) / 50.0;
			cauldron_glowSpec[1] -= (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
	}
	else if (orb_leg == 4 && random == 1)
	{
		if (std::abs(matGreenBlueEmission_animation[2] - 1) > epsilon
			&& std::abs(cauldron_glowDiff[2] - 1) > epsilon
			&& collision) {

			matGreenBlueEmission_animation[2] += (1 - 0.1) / 50.0;
			cauldron_glowDiff[2] += (1 - 0.1) / 50.0;
			cauldron_glowSpec[2] += (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
		else if (std::abs(matGreenBlueEmission_animation[1] - 0.1) > epsilon
			&& std::abs(cauldron_glowDiff[2] - 0.1) > epsilon
			&& !collision) {

			matGreenBlueEmission_animation[1] -= (1.0 - 0.1) / 50.0;
			cauldron_glowDiff[2] -= (1 - 0.1) / 50.0;
			cauldron_glowSpec[2] -= (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
	}
	else {
		if (std::abs(matGreenBlueEmission_animation[0] - 1) > epsilon
			&& std::abs(cauldron_glowDiff[0] - 1) > epsilon
			&& collision) {

			matGreenBlueEmission_animation[0] += (1 - 0.1) / 50.0;
			cauldron_glowDiff[0] += (1 - 0.1) / 50.0;
			cauldron_glowSpec[0] += (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
		else if (std::abs(matGreenBlueEmission_animation[1] - 0.1) > epsilon
			&& std::abs(cauldron_glowDiff[0] - 0.1) > epsilon
			&& !collision) {

			matGreenBlueEmission_animation[0] -= (1 - 0.1) / 50.0;
			cauldron_glowDiff[0] -= (1 - 0.1) / 50.0;
			cauldron_glowSpec[0] -= (1 - 0.1) / 50.0;
			glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
			glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
			glutPostRedisplay();
		}
	}
}

void ANIMATION_HW4::draw_door(bool selecting) {

	if (selecting) {
		//Door
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glTranslated(6.5 * FT, 4.5 * FT, 0 * FT);
		glTranslated(0 * FT, 0 * FT, -2.0 * FT);
		glRotated(door_swing_angle, 0, 1, 0);
		glTranslated(0 * FT, 0 * FT, +2.0 * FT);
		glScaled(0.3 * FT, 9 * FT, 4.0 * FT);
		glColor3f(0.0, 1.0, 0.0); // Green RGB for Selecting
		glutSolidCube(1.0);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else {

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWood_animation);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWood_animation);

		//Door
		glPushMatrix();
		glTranslated(6.5 * FT, 4.5 * FT, 0 * FT);
		glTranslated(0 * FT, 0 * FT, -2.0 * FT);
		glRotated(door_swing_angle, 0, 1, 0);
		glTranslated(0 * FT, 0 * FT, +2.0 * FT);
		bool lit_door[] = {
			true,    // West
			false,   // North
			true,    // East
			true,    // South
			true,    // Top
			true };  // Bottom
		Helper_HW4::drawScaledCube(0.3 * FT, 9 * FT, 4.0 * FT,
			lit_door);
		glPopMatrix();
	}
}

void ANIMATION_HW4::draw_window_shades(bool selecting) {


	// Right Window Shade From Outside
	if (selecting) {
		// Window Shades
		glDisable(GL_LIGHTING);
		glPushMatrix();
		// Window Shades
		glTranslated(8.3 * FT,
			window_shade_translate * FT,
			6.48 * FT);
		glScaled(0.2 * FT,
			window_shade_size * FT, 4.5 * FT);
		glColor3f(1.0, 0.0, 0.0); // Red RGB for Selecting
		glutSolidCube(1.0);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else {

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matShades_animation);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matShades_animation);

		// Window Shades
		glPushMatrix();
		glTranslated(8.3 * FT, 
			window_shade_translate * FT, 
			6.48 * FT);
		bool lit_window_shades[] = {
			true,    // West
			false,   // North
			true,    // East
			true,    // South
			true,    // Top
			true };  // Bottom
		Helper_HW4::drawScaledCube_NoRed(0.2 * FT, 
			window_shade_size * FT, 4.5 * FT,
			lit_window_shades);
		glPopMatrix();
	}

	// Left Window Shade From Outside
	if (selecting) {
		// Window Shades
		glDisable(GL_LIGHTING);
		glPushMatrix();
		// Window Shades
		glTranslated(8.3 * FT,
			window_shade_translate * FT,
			-6.48 * FT);
		glScaled(0.2 * FT,
			window_shade_size * FT, 4.5 * FT);
		glColor3f(1.0, 0.0, 0.0); // Red RGB for Selecting
		glutSolidCube(1.0);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else {

		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matShades_animation);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matShades_animation);

		// Window Shades
		glPushMatrix();
		glTranslated(8.3 * FT,
			window_shade_translate * FT,
			-6.48 * FT);
		bool lit_window_shades[] = {
			true,    // West
			false,   // North
			true,    // East
			true,    // South
			true,    // Top
			true };  // Bottom
		Helper_HW4::drawScaledCube_NoRed(0.2 * FT,
			window_shade_size * FT, 4.5 * FT,
			lit_window_shades);
		glPopMatrix();
	}
}

void ANIMATION_HW4::draw_orb(int random) {
	
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT0);

	// Get Current Material Values To Restore Them Later
	float CurrentAmb[4],
		CurrentDiff[4],
		CurrentSpec[4],
		CurrentShine[1],
		CurrentEmission[4];

	glGetMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
	glGetMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
	glGetMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, orbSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, orbShine);

	if (random == 1) {
		// Blue Glow
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orb_blueDiffAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, orb_blueDiffAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, orb_blueEmiss);
	}
	else
	{
		// Red Glow
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, orb_redDiffAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, orb_redDiffAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, orb_redEmiss);
	}
	
	glPushMatrix();
	glTranslatef(orbPos_x * FT, orbPos_y * FT, orbPos_z * FT);
	glTranslatef(1.4 * FT, 0, 0.5 * FT);
	glRotated(orb_rotation, 0, 0, 1);
	glRotated(orb_rotation, 1, 0, 0);
	glTranslatef(-1.4 * FT, 0, -0.5 * FT);
	float orb_glowPos[] = { 0, 0, 0, 1.0 };
	// Orb Glow = Light1
	glLightfv(GL_LIGHT1, GL_POSITION, orb_glowPos);
	glEnable(GL_LIGHT1);
	glutSolidSphere((0.5 * FT), 50, 50);
	glDisable(GL_LIGHT1);
	glPopMatrix();	
	
	//Restore Old Material Settings
	glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
	glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
}

void ANIMATION_HW4::draw_cauldron_glow() {

	// Green Glowing Liquid = On
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matGreenBlueEmission_animation);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matGreenBlueEmission_animation);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matGreenBlueEmission_animation);

	glDisable(GL_LIGHT6);
	glPushMatrix();
	glTranslated(16 * FT, 2.5 * FT, 0 * FT);
	glRotated(90, 1, 0, 0);
	Helper_HW4::drawCylinder(1.98 * FT, 0.1 * FT, 1.98 * FT, 360, 360);
	glPopMatrix();
	glEnable(GL_LIGHT6);

	// Glow off
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, NoEmission_animation);
}

void ANIMATION_HW4::draw_cauldron(bool cauldron_Collison) {

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT2);
	glPushMatrix();
	glTranslated(5 * FT, 0 * FT, -7 * FT);

	GLdouble top_equation[] = { 0.0, -1.0, 0.0, 3 * FT };
	GLdouble bottom_equation[] = { 0.0, 1.0, 0.0, 0.5 * FT };

	draw_cauldron_glow();

	// Enable the clipping planes
	glClipPlane(GL_CLIP_PLANE0, top_equation);
	glEnable(GL_CLIP_PLANE0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matConcret_animation);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matConcret_animation);
	// Outside Normals
	glPushMatrix();
	glTranslated(16 * FT, 2.5 * FT, 0 * FT);
	glScaled(2.0 * FT, 3.0 * FT, 2.0 * FT);
	glutSolidSphere(1.0, 32, 32);
	glPopMatrix();
	// Inside Normals
	glPushMatrix();
	glTranslated(16 * FT, 2.5 * FT, 0 * FT);
	glScaled(-2.0 * FT, 3.0 * FT, 2.0 * FT);
	glutSolidSphere(1.0, 32, 32);
	glPopMatrix();

	// Disable the clipping planes
	glDisable(GL_CLIP_PLANE0);

	glPushMatrix();
	glTranslated(16 * FT, 3 * FT, 0 * FT);
	glRotated(90, 1, 0, 0);
	glutSolidTorus(0.15 * FT, 2.00 * FT, 80, 80);
	glPopMatrix();

	glPopMatrix();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
}

void ANIMATION_HW4::flash_light(float eye_x, float eye_y, float eye_z,
	float camera_angle_h, bool ceiling_light_on, bool flash_light_on) {

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT2);

	// Get Current Material Values To Restore Them Later
	float CurrentAmb[4],
		CurrentDiff[4],
		CurrentSpec[4],
		CurrentShine[1],
		CurrentEmission[4];

	glGetMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
	glGetMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
	glGetMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
	glGetMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, flash_lightDiffAmb);
	glMaterialfv(GL_FRONT, GL_AMBIENT, flash_lightDiffAmb);

	if (ceiling_light_on == false) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, window_lightSpec);
		glMaterialfv(GL_FRONT, GL_SHININESS, flash_lightShine);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, flash_lightSpec);
		glMaterialfv(GL_FRONT, GL_SHININESS, flash_lightShine);
	}

	glPushMatrix();	/*A*/

	if (flash_light_on) {
		glTranslated(eye_x + (1.5 * FT), eye_y - (1.5 * FT), eye_z - (3 * FT));
		glTranslated(-1.5 * FT, 0, 3 * FT);
		glRotated(camera_angle_h, 0, 1, 0);
		glTranslated(1.5 * FT, 0, -3 * FT);
	}
	else {
		glTranslated(18 * FT, 4.4 * FT, 7.5 * FT);
		glRotated(70, 0, 1, 0);
		glRotated(5, 1, 0, 0);
	}

	glScaled(0.5, 0.5, 0.5);

	// Handle
	glPushMatrix(); /*B*/
	glTranslated(0 * FT, 0 * FT, 0.3 * FT);
	Helper_HW4::drawCylinder(0.3 * FT, 0.3 * FT, 2 * FT, 32, 32);
	glPopMatrix(); /*B*/

	// Connector
	glPushMatrix(); /*B*/
	glTranslated(0 * FT, 0 * FT, 0 * FT);
	Helper_HW4::drawCylinder(0.4 * FT, 0.3 * FT, 0.3 * FT, 32, 32);
	glPopMatrix(); /*B*/

	// Flash Light Head
	glPushMatrix(); /*B*/
	glTranslated(0 * FT, 0 * FT, -0.7 * FT);
	Helper_HW4::drawCylinder(0.4 * FT, 0.4 * FT, 0.7 * FT, 32, 32);
	glPopMatrix(); /*B*/

	if (flash_light_on) {
		glMaterialfv(GL_FRONT, GL_DIFFUSE, flash_light_emissionDiffAmb);
		glMaterialfv(GL_FRONT, GL_AMBIENT, flash_light_emissionDiffAmb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, flash_light_emissionDiffAmb);
	}
	else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, NoSpec_animation);
		glMaterialfv(GL_FRONT, GL_SHININESS, NoShine_animation);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, flash_glassDiffAmb);
		glMaterialfv(GL_FRONT, GL_AMBIENT, flash_glassDiffAmb);
	}

	// Flash Light Emission Disk
	glPushMatrix(); /*B*/
	glTranslated(0 * FT, 0 * FT, -0.71 * FT);
	Helper_HW4::drawCylinder(0.35 * FT, 0.35 * FT, 0.05 * FT, 32, 32);
	glPopMatrix(); /*B*/

	glMaterialfv(GL_FRONT, GL_DIFFUSE, flash_buttonDiffAmb);
	glMaterialfv(GL_FRONT, GL_AMBIENT, flash_buttonDiffAmb);
	glMaterialfv(GL_FRONT, GL_EMISSION, NoEmission_animation);

	glPushMatrix(); /*B*/
	glTranslated(0 * FT, 0.25 * FT, 0.5 * FT);
	bool lit_flash_light[] = {
		false,    // East
		false,    // North
		false,    // West
		false,    // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(0.15 * FT, 0.15 * FT, 0.3 * FT,
		lit_flash_light);
	glPopMatrix(); /*B*/

	glPopMatrix(); /*A*/

	//Restore Old Material Settings
	glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
	glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
}

void ANIMATION_HW4::reset() {

	// Orb Globals
	orbPos_x = 18;
	orbPos_y = 0.8;
	orbPos_z = -8;
	orb_rotation = 0;
	orb_leg = 0;

	// Emission Globals
	matGreenEmission_animation[0] = 0.0;
	matGreenEmission_animation[1] = 0.0;
	matGreenEmission_animation[2] = 0.0;

	matGreenBlueEmission_animation[0] = 0.0;
	matGreenBlueEmission_animation[1] = 0.1;
	matGreenBlueEmission_animation[2] = 0.0;

	cauldron_glowDiff_animation[0] = 0.0;
	cauldron_glowDiff_animation[1] = 0.5;
	cauldron_glowDiff_animation[2] = 0.0;

	cauldron_glowSpec_animation[0] = 0.0;
	cauldron_glowSpec_animation[1] = 0.5;
	cauldron_glowSpec_animation[2] = 0.0;

	// Cauldron Globals
	cauldron_glowDiff[0] = 0.0;
	cauldron_glowDiff[1] = 0.1;
	cauldron_glowDiff[2] = 0.0;

	cauldron_glowSpec[0] = 0.0;
	cauldron_glowSpec[1] = 0.1;
	cauldron_glowSpec[2] = 0.0;

	// Reset Lighting
	glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
	glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
}

