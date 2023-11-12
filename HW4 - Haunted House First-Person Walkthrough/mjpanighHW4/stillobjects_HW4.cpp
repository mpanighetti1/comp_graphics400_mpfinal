/******************************************
*
* Still Objects File - Includes:
*   - Draw Background Which Includes Grass
*	- Draw Structure - Columns, Walls, Porch
*	- Draw Ceiling Light
*	- Draw Light Switch
*   - Draw Table
* 
*******************************************/

#include "helper_HW4.h"
#include "stillobjects_HW4.h"
#include "animation_HW4.h"

#define FT 12.0

// Wood Material
float matWood[] = { 0.61 * 0.35, 0.3253 * 0.35, 0.0 * 0.35, 1.0 };

// Green Grass
float matGround[] = { 0.0696 * 0.7, 0.29 * 0.7, 0.0696 * 0.7, 1.0 }; 

// Dark Grey Material
float matDarkWood[] = { 0.39 / 3, 0.2405 / 3, 0.0, 1.0 };

// Almost Black Material
float matBlack[] = { 0.1 / 2, 0.1 / 2, 0.1 / 2, 1.0 };
float matBlack2[] = { 0.2 / 2, 0.2 / 2, 0.2 / 2, 1.0 };

// Light Grey Material
float matWoodTrim[] = { 0.39 / 5, 0.2405 / 5, 0.0, 1.0 };

// Floor
float matFloor[] = { 0.44 / 4, 0, 0, 1.0 };

// Glass Material
float matGlassAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float matGlassDiff[] = { 0.0, 0.0, 0.0, 0.5 };
float matGlassSpec[] = { 1.0, 1.0, 1.0, 1.0 };
float matGlassShine[] = { 100.0 };

// Ceiling Light
float matCeilingLightAmbDiff[] = { 0.9717 / 2, 1.0 / 2, 0.66 / 2, 1.0 };
float matCeilingLightEmission[] = { 0.9717 * 2, 1.0 * 2, 0.66 * 2, 1.0 };

// Outdoor Light
float matOutdoorLightAmbDiff[] = { 2.0, 0.0, 0.0, 1.0 };
float matOutdoorLightEmission[] = { 1.0 * 2, 0.0 * 2, 0.0 * 2, 1.0 };

// Light Switch
float matRedEmission[] = { 1.0 * 2, 0.0 * 2, 0.0 * 2, 1.0 };
float matGreenEmission[] = { 0.0 * 2, 1.0 * 2, 0.0 * 2, 1.0 };

// Material Vectors - No Shine/No Emission (Defaults)
float matNoSpec_stillobj[] = { 0.0, 0.0, 0.0, 1.0 };
float matNoShine_stillobj[] = { 0.0 };
float matNoEmission[] = { 0.0, 0.0, 0.0, 1.0 };

void STILLOBJECTS_HW4::draw_background(bool outdoor_lightState) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matGround);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matGround);

	float ground_radius = 5000.0;

	glPushMatrix();
	glTranslated(0.0, -1.0, 0.0);
	glScaled(1.0, 1.0 / ground_radius, 1.0);
	glutSolidSphere(ground_radius, 32, 32);
	glPopMatrix();
}

void draw_frontR_wall() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);

	//Right Of Window
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, 4 * FT);
	bool lit_frontR_wall_R_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 10.0 * FT, 0.5 * FT,
		lit_frontR_wall_R_window);
	glPopMatrix();

	//Left Of Window
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, 9 * FT);
	bool lit_frontR_wall_L_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 10.0 * FT, 0.5 * FT,
		lit_frontR_wall_L_window);
	glPopMatrix();

	//Top Of Window
	glPushMatrix();
	glTranslated(7 * FT, 10.5 * FT, 6.5 * FT);
	bool lit_frontR_wall_T_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 1.5 * FT, 6.0 * FT,
		lit_frontR_wall_T_window);
	glPopMatrix();

	//Bottom Of Window
	glPushMatrix();
	glTranslated(7 * FT, 2 * FT, 6.5 * FT);
	bool lit_frontR_wall_B_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 3.5 * FT, 6.0 * FT,
		lit_frontR_wall_B_window);
	glPopMatrix();

	// Glass Material
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matGlassDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matGlassAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matGlassSpec); // Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matGlassShine); // Shine

	// Set up transparency using alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Window "Glass"
	glPushMatrix();
	glTranslated(7 * FT, 6.75 * FT, 7.25 * FT);
	bool lit_frontR_wall_G_window[] = {
		false,    // West
		false,    // North
		false,    // East
		false,    // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(0.3 * FT, 6.0 * FT, 6.0 * FT,
		lit_frontR_wall_G_window);
	glPopMatrix();

	glDisable(GL_BLEND);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matNoShine_stillobj); // No Shine
}

void draw_frontL_wall() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);

	//Right Of Window
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, -4 * FT);
	bool lit_frontR_wall_R_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 10.0 * FT, 0.5 * FT,
		lit_frontR_wall_R_window);
	glPopMatrix();

	//Left Of Window
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, -9 * FT);
	bool lit_frontR_wall_L_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 10.0 * FT, 0.5 * FT,
		lit_frontR_wall_L_window);
	glPopMatrix();

	//Top Of Window
	glPushMatrix();
	glTranslated(7 * FT, 10.5 * FT, -6.5 * FT);
	bool lit_frontR_wall_T_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 1.5 * FT, 6.0 * FT,
		lit_frontR_wall_T_window);
	glPopMatrix();

	//Bottom Of Window
	glPushMatrix();
	glTranslated(7 * FT, 2 * FT, -6.5 * FT);
	bool lit_frontR_wall_B_window[] = {
		false,    // West
		false,    // North
		false,    // East
		true,     // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(2.0 * FT, 3.5 * FT, 6.0 * FT,
		lit_frontR_wall_B_window);
	glPopMatrix();

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

	// Glass Material
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matGlassDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matGlassAmb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matGlassSpec); // Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matGlassShine); // Shine
	
	// Set up transparency using alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Window "Glass"
	glPushMatrix();
	glTranslated(7 * FT, 6.75 * FT, -7.25 * FT);
	bool lit_frontR_wall_G_window[] = {
		false,    // West
		false,    // North
		false,    // East
		false,    // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(0.3 * FT, 6.0 * FT, 6.0 * FT,
		lit_frontR_wall_G_window);
	glPopMatrix();

	glDisable(GL_BLEND);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matNoShine_stillobj); // No Shine
}

void STILLOBJECTS_HW4::draw_structure() {

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matWood);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matWood);

	//Left Middle Porch Beam
	glPushMatrix();
	glTranslated(-5 * FT, 4.5 * FT, -5.5 * FT);
	glRotated(0, 0, 0, 1);
	bool lit_Lmiddle_porchBeam[] = {
		true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(0.8 * FT, 9.2 * FT, 0.5 * FT,
		lit_Lmiddle_porchBeam);
	glPopMatrix();

	//Right Middle Porch Beam
	glPushMatrix();
	glTranslated(-5 * FT, 4.5 * FT, 5.5 * FT);
	glRotated(0, 0, 0, 1);
	bool lit_Rmiddle_porchBeam[] = {
		true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(0.8 * FT, 9.2 * FT, 0.5 * FT,
		lit_Rmiddle_porchBeam);
	glPopMatrix();

	//Left Porch Beam
	glPushMatrix();
	glTranslated(-5 * FT, 4.5 * FT, -12.5 * FT);
	glRotated(0, 0, 0, 1);
	bool lit_L_porchBeam[] = {
		true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(0.8 * FT, 9.2 * FT, 0.5 * FT,
		lit_L_porchBeam);
	glPopMatrix();

	//Right Porch Beam
	glPushMatrix();
	glTranslated(-5 * FT, 4.5 * FT, 12.5 * FT);
	glRotated(0, 0, 0, 1);
	bool lit_R_porchBeam[] = {
	    true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(0.8 * FT, 9.2 * FT, 0.5 * FT,
		lit_R_porchBeam);
	glPopMatrix();

	//Porch Roof
	glPushMatrix();
	glTranslated(-1 * FT, 10.6 * FT, 0 * FT);
	glRotated(20, 0, 0, 1);
	bool lit_porch_roof[] = {
	    true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(12.95 * FT, 0.3 * FT, 25.95 * FT,
		lit_porch_roof);
	glPopMatrix();

	//Porch
	glPushMatrix();
	glTranslated(0 * FT, -0.2 * FT, 0 * FT);
	bool lit_porch[] = {
	    true,   // West
		true,    // North
		true,    // East
		true,    // South
		false,    // Top
		true
};  // Bottom
	Helper_HW4::drawScaledCube(12.95 * FT, 0.99 * FT, 25.95 * FT,
		lit_porch);
	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDarkWood);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matDarkWood);

	//Block Above Door
	glPushMatrix();
	glTranslated(7 * FT, 10.0 * FT, 0 * FT);
	glRotated(0, 0, 0, 1);
	bool lit_door[] = {
	    true,    // West
	   false,    // North
		true,    // East
		true,    // South
		true,    // Top
	   false };  // Bottom
	Helper_HW4::drawScaledCube(4.0 * FT, 2.0 * FT, 4.0 * FT,
		lit_door);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matFloor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matFloor);

	//Floor
	glPushMatrix();
	glTranslated(16 * FT, -0.2 * FT, 0 * FT);
	bool lit_floor[] = {
	    true,    // West
		true,    // North
		true,    // East
	   false,    // South
	   false,    // Top
	   false };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(19.0 * FT, 1.0 * FT, 23.95 * FT, 
		lit_floor);
	glPopMatrix();


	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDarkWood);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matDarkWood);

	//Ceiling
	glPushMatrix();
	glTranslated(16 * FT, 11.5 * FT, 0 * FT);
	bool lit_ceiling[] = {
	    true,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(22.0 * FT, 3.0 * FT, 26.0 * FT,
		lit_ceiling);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDarkWood);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matDarkWood);

	//Right Door Column
	glPushMatrix();	
	glTranslated(7 * FT, 5 * FT, 3 * FT);
	bool lit_R_doorColumn[] = {
		false,   // West
		false,   // North
		false,   // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(4.0 * FT, 10.0 * FT, 2.0 * FT,
		lit_R_doorColumn);
	glPopMatrix();

	//Left Door Column
	glPushMatrix();	
	glTranslated(7 * FT, 5 * FT, -3 * FT);
	bool lit_L_doorColumn[] = {
	   false,   // West
	   false,    // North
	   false,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(4.0 * FT, 10.0 * FT, 2.0 * FT,
		lit_L_doorColumn);
	glPopMatrix();

	//Right Corner Column
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, 11 * FT);
	bool lit_R_cornerColumn[] = {
	   false,   // West
	   false,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(4.0 * FT, 10.0 * FT, 4.0 * FT,
		lit_R_cornerColumn);
	glPopMatrix();

	//Left Corner Column
	glPushMatrix();
	glTranslated(7 * FT, 5 * FT, -11 * FT);
	bool lit_L_cornerColumn[] = {
	    true,   // West
		false,    // North
		false,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube(4.0 * FT, 10.0 * FT, 4.0 * FT,
		lit_L_cornerColumn);
	glPopMatrix();

	//Back-Right Corner Column
	glPushMatrix();
	glTranslated(25 * FT, 5 * FT, 11 * FT);
	bool lit_backR_cornerColumn[] = {
	   false,   // West
		true,    // North
		true,    // East
	   false,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(4.0 * FT, 10.0 * FT, 4.0 * FT,
		lit_backR_cornerColumn);
	glPopMatrix();

	//Back-Left Corner Column
	glPushMatrix();
	glTranslated(25 * FT, 5 * FT, -11 * FT);
	bool lit_backL_cornerColumn[] = {
	    true,    // West
		true,    // North
		false,   // East
		false,   // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(4.0 * FT, 10.0 * FT, 4.0 * FT,
		lit_backL_cornerColumn);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);
	
	//Right Wall
	glPushMatrix();
	glTranslated(16 * FT, 5 * FT, 11 * FT);
	bool lit_R_wall[] = {
		false,   // West
		true,    // North
		true,    // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(14.0 * FT, 10.0 * FT, 2.0 * FT,
		lit_R_wall);
	glPopMatrix();

	//Left Wall
	glPushMatrix();
	glTranslated(16 * FT, 5 * FT, -11 * FT);
	bool lit_L_wall[] = {
		true,    // West
		true,    // North
		false,   // East
		true,    // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(14.0 * FT, 10.0 * FT, 2.0 * FT,
		lit_L_wall);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matBlack2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matBlack2);

	//Back Wall
	glPushMatrix();
	glTranslated(25 * FT, 5 * FT, 0 * FT);
	bool lit_back_wall[] = {
		true,    // East
		true,    // North
		true,    // West
		false,   // South
		true,    // Top
		true };  // Bottom
	Helper_HW4::drawScaledCube_NoRed(2.0 * FT, 10.0 * FT, 18.0 * FT,
		lit_back_wall);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);

	//Right Front Wall
	draw_frontR_wall();

	//Right Front Wall
	draw_frontL_wall();
}

void STILLOBJECTS_HW4::draw_ceiling_light(bool ceiling_light_on) {

	glDisable(GL_LIGHT2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matCeilingLightAmbDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matCeilingLightAmbDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matGlassSpec); // Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matGlassShine); // Shine

	if (ceiling_light_on) {
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matCeilingLightEmission); // Glow
	}
	else {
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matNoEmission); // No Glow
	}

	glPushMatrix();
	glTranslated(16 * FT, 10.0 * FT, 0 * FT);	
	glScaled(1.0 * FT, 0.5 * FT, 1.0 * FT);
	glDisable(GL_LIGHT0);

	glutSolidSphere(1.0, 32, 32);

	glEnable(GL_LIGHT0);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matNoShine_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matNoEmission); // No Glow
	glEnable(GL_LIGHT2);
}

void STILLOBJECTS_HW4::draw_light_switch(bool selecting, bool ceiling_light_on) {

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT2);

	if (selecting) {
		//Door
		glDisable(GL_LIGHTING);
		glPushMatrix();
		glTranslated(9.1 * FT, 5 * FT, 3 * FT);
		glRotated(90, 0, 1, 0);
		glColor3f(0.0, 0.0, 1.0); // Blue RGB for Selecting
		Helper_HW4::drawCylinder(1.5, 1.5, 1.0, 32, 32);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else
	{
		if (ceiling_light_on) {
			// Green Glow = On
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matGreenEmission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matGreenEmission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matGreenEmission);
			glPushMatrix();
			glTranslated(9.09 * FT, 5 * FT, 3 * FT);
			glRotated(90, 0, 1, 0);
			Helper_HW4::drawCylinder(1.5, 1.5, 0.3, 32, 32);
			glPopMatrix();
		}
		else {
			// Red Glow = Off
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matRedEmission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matRedEmission);
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matRedEmission);
			glPushMatrix();
			glTranslated(9.09 * FT, 5 * FT, 3 * FT);
			glRotated(90, 0, 1, 0);
			Helper_HW4::drawCylinder(1.5, 1.5, 1.0, 32, 32);
			glPopMatrix();
		}
	}

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matNoSpec_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matNoShine_stillobj); // No Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matNoEmission); // No Glow	
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matBlack);

	glPushMatrix();
	glTranslated(9.0 * FT, 5 * FT, 3 * FT);
	glRotated(90, 0, 1, 0);
	Helper_HW4::drawCylinder(2.5, 2.5, 1.0, 32, 32);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matWoodTrim);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matWoodTrim);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT2);
}

void STILLOBJECTS_HW4::draw_table() {
	
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT0);
	glPushMatrix();
	glTranslated(2 * FT, 0 * FT, 8.2 * FT);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matBlack);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matBlack);

	glPushMatrix();
	glTranslated(16 * FT, 4.0 * FT, 0 * FT);
	glRotated(0, 1, 0, 0);
	
	//Table Top
	bool lit_table[] = {
		false,    // East
		false,    // North
		false,    // West
		false,    // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(8.0 * FT, 0.3 * FT, 3.0 * FT,
		lit_table);
	glPopMatrix();

	//Table Legs
	glPushMatrix();
	glTranslated(20 * FT, 2.15 * FT, -1.5 * FT);
	Helper_HW4::drawScaledCube(0.3 * FT, 4.3 * FT, 0.3 * FT,
		lit_table);
	glPopMatrix();
	glPushMatrix();
	glTranslated(12 * FT, 2.15 * FT, -1.5 * FT);
	Helper_HW4::drawScaledCube(0.3 * FT, 4.3 * FT, 0.3 * FT,
		lit_table);
	glPopMatrix();
	glPushMatrix();
	glTranslated(20 * FT, 2.15 * FT, 1.5 * FT);
	Helper_HW4::drawScaledCube(0.3 * FT, 4.3 * FT, 0.3 * FT,
		lit_table);
	glPopMatrix();
	glPushMatrix();
	glTranslated(12 * FT, 2.15 * FT, 1.5 * FT);
	Helper_HW4::drawScaledCube(0.3 * FT, 4.3 * FT, 0.3 * FT,
		lit_table);
	glPopMatrix();	

	glPopMatrix();
	glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
}

void STILLOBJECTS_HW4::outdoor_light(bool outdoor_light_on) {

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

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matDarkWood);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matDarkWood);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matGlassSpec); // Shine
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matGlassShine); // Shine	

	glPushMatrix(); /*A*/
	glTranslated(5 * FT, 11.0 * FT, 0 * FT);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT6);

	glPushMatrix(); /*B*/
	glTranslated(0.0 * FT, 0.2 * FT, 0.0 * FT);
	//Top Of Outdoor Light
	bool lit_outdoor_light[] = {
		false,    // East
		false,    // North
		false,    // West
		false,    // South
		false,    // Top
		false };  // Bottom
	Helper_HW4::drawScaledCube(0.5 * FT, 0.4 * FT, 2.0 * FT,
		lit_outdoor_light);
	glPopMatrix(); /*B*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matOutdoorLightEmission); // Glow
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matOutdoorLightAmbDiff);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matOutdoorLightAmbDiff);
	glScaled(0.2 * FT, 0.4 * FT, 0.9 * FT);		
	glutSolidSphere(1.0, 32, 32);
	
	glEnable(GL_LIGHT6);
	glEnable(GL_LIGHT0);
	glPopMatrix(); /*A*/

	//Restore Old Material Settings
	glMaterialfv(GL_FRONT, GL_AMBIENT, CurrentAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, CurrentDiff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, CurrentSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, CurrentShine);
	glMaterialfv(GL_FRONT, GL_EMISSION, CurrentEmission);

}

