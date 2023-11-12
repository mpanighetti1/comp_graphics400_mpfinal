/******************************************
*
* Scene/Environment File - Includes:
*   - Drawing Green Surface
*	- Drawing 3 Objects
*   - Drawing the Lilly Pad
*	- Drawing the Cloud
* 
*******************************************/

#include "helper_HW3.h"
#include "scene_HW3.h"

void SCENE_HW3::draw_background() {
	
	glDisable(GL_LIGHTING);
	glColor3f(0.0, 0.34, 0.034); //Dark Green

	Helper_HW3::draw_ellipsoid(500, 500, 0.1, false);

	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);
}

void SCENE_HW3::draw_objects(float Obj1_X, float Obj1_Y, float Obj1_Z,
			    float Obj2_X, float Obj2_Y, float Obj2_Z,
				float Obj3_X, float Obj3_Y, float Obj3_Z, int shadow) {

	//Make Obj1 - Green
	glPushMatrix();	
	glTranslated(Obj1_X, Obj1_Y, Obj1_Z);

	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3ub(0, 255, 0);

	glutSolidCube(15.0);

	glPushMatrix();
	glTranslated(0.0, 40.0, 10.0);
	Helper_HW3::draw_prism(10.0, 20.0, 0.5);
	glPopMatrix();

	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3ub(255, 255, 255); // White Pole
	Helper_HW3::draw_cylinder(80.0, 1.0, 0, 5.0, 0, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
	glPopMatrix();

	//Make Obj2 - Blue
	glPushMatrix();
	
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3ub(0, 0, 255);
	glTranslated(Obj2_X, Obj2_Y, Obj2_Z);
	glutSolidCube(15.0);

	glPushMatrix();
	glTranslated(0.0, 40.0, 10.0);
	Helper_HW3::draw_prism(10.0, 20.0, 0.5);
	glPopMatrix();

	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3ub(255, 255, 255); // White Pole
	Helper_HW3::draw_cylinder(80.0, 1.0, 0, 5.0, 0, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
	glPopMatrix();

	//Make Obj3 - Red
	glPushMatrix();
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else  glColor3ub(255, 0, 0);
	glTranslated(Obj3_X, Obj3_Y, Obj3_Z);	
	glutSolidCube(15.0);

	glPushMatrix();
	glTranslated(0.0, 40.0, 10.0);
	Helper_HW3::draw_prism(10.0, 20.0, 0.5);
	glPopMatrix();

	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3ub(255, 255, 255); // White Pole
	Helper_HW3::draw_cylinder(80.0, 1.0, 0, 5.0, 0, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
	glPopMatrix();

}

void SCENE_HW3::draw_cloud(int shadow) {

	glDisable(GL_LIGHTING);
	glPushMatrix();
	glScaled(2.0, 2.0, 2.0);

	// Cloud color
	float cloud_color[] = { 1.0f, 1.0f, 1.0f };
	
	if (shadow) glColor3f(0.0, 0.0, 0.0);
	else glColor3fv(cloud_color);

	// Number of ellipsoids to create the cloud
	int num_ellipsoids = 50;

	// Random seed for positioning ellipsoids
	srand(static_cast<unsigned>(time(0)));

	// Spread factor
	float spread = 6.0f;

	for (int i = 0; i < num_ellipsoids; ++i) {
		// Generate random offsets for the ellipsoid position
		float x_offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
		float y_offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;
		float z_offset = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f;

		// Generate random sizes for the ellipsoid dimensions
		float length = 2.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f;
		float width = 2.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f;
		float height = 2.0f + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 3.0f;

		glPushMatrix();
		glTranslatef(x_offset * spread, y_offset * spread, z_offset * spread);
		Helper_HW3::draw_ellipsoid(length, width, height, false);
		glPopMatrix();
	}

	glPopMatrix();
	glEnable(GL_LIGHTING);

}

void SCENE_HW3::draw_lily_pad(float Lily_pad_X, float Lily_pad_Y, float Lily_pad_Z) {

	glDisable(GL_LIGHTING);

	//Make Lilly Pad
	glPushMatrix();
	glColor3f(0.095, 0.57, 0);
	glTranslated(Lily_pad_X, Lily_pad_Y, Lily_pad_Z);
	// Length, Width, Height, Solid = true, Wire = false.
	Helper_HW3::draw_ellipsoid(18.0, 18.0, 0.1, false);
    glPopMatrix();

	//Make Pond
	glPushMatrix();
	glColor3f(0.2054, 0.3613, 0.79);
	glRotated(45.0, 0.0, 1.0, 0.0);
	glTranslated(Lily_pad_X + 20, Lily_pad_Y, Lily_pad_Z + 20);
	// Length, Width, Height, Solid = true, Wire = false.
	Helper_HW3::draw_ellipsoid(70.0, 50.0, 0.0, false);
	glPopMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);

}