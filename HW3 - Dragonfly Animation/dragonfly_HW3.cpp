/******************************************
*
* Dragonfly File - Includes:
*   - draw_dragonfly - head, body, tail
*   - draw_dragonfly_right_wings
*   - draw_dragonfly_left_wings
*   - draw_dragonfly_fire
*
*******************************************/

#include "helper_HW3.h"
#include "dragonfly_HW3.h"

void DRAGONFLY_HW3::draw_dragonfly(int shadow) {

    glPushMatrix();
    glRotated(45, 0.0, 1.0, 0.0);

	glLineWidth(1.0);

    if (shadow) glColor3f(0.0, 0.0, 0.0); //Black
	else glColor3f(0.23, 0.23, 0.23); //Dark Grey

    glPushMatrix();
    glTranslated(0.0, 0.0, 10.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(2, 2, 2, false);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0.0, 0.0, 5.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(4, 3, 3, false);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslated(0.0, 2.0, -6);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(11, 1.2, 1.2, false);
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glPopMatrix();

}

void DRAGONFLY_HW3::draw_dragonfly_right_wings(int shadow) {
    
    glDisable(GL_LIGHTING);

    if (shadow) glColor3f(0.0, 0.0, 0.0); //Black
    else glColor3f(0.23, 0.23, 0.23); //Dark Grey

    glPushMatrix();
    glRotated(45, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslated(-8.0, 2.0, 7);
    glRotated(90, 0.0, 1.0, 0.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(8, 2, 0.1, true);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8.0, 2.0, 3);
    glRotated(75, 0.0, 1.0, 0.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(8, 2, 0.1, true);
    glPopMatrix();

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void DRAGONFLY_HW3::draw_dragonfly_left_wings(int shadow) {

    glDisable(GL_LIGHTING);

    if (shadow) glColor3f(0.0, 0.0, 0.0); //Black
    else glColor3f(0.23, 0.23, 0.23); //Dark Grey

    glPushMatrix();
    glRotated(45, 0.0, 1.0, 0.0);

    glPushMatrix();
    glTranslated(8.0, 2.0, 7);
    glRotated(270, 0.0, 1.0, 0.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(8, 2, 0.1, true);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.0, 2.0, 3);
    glRotated(285, 0.0, 1.0, 0.0);
    // Length, Width, Height, Wire?
    Helper_HW3::draw_ellipsoid(8, 2, 0.1, true);
    glPopMatrix();

    glPopMatrix();

    glEnable(GL_LIGHTING);
}

void DRAGONFLY_HW3::draw_dragonfly_fire() {

    glDisable(GL_LIGHTING);

    glPushMatrix();
    glRotated(45, 0.0, 1.0, 0.0);    

    float color1[] = { 1.0, 0.4167, 0.0, 1.0 }; //Orange, alpha=1
    float color2[] = { 1.0, 0.4167, 0.0, 0 }; //Orange, alpha=0

    float center_x = 0.0;
    float center_y = 0.0;
    float center_z = 13.0;
    float slices = 360.0;
    float radius = 20.0;
    float height = 50.0;
      
    glPushMatrix();
    glTranslated(center_x, center_y, center_z + height);
    glRotated(180, 1.0, 0.0, 0.0);
    //glutSolidCone(radius, height, slices, slices);
    //glutSolidSphere(radius, slices, slices);
    Helper_HW3::draw_cone(radius, height, slices, color1, color2);
    glColor3f(0.0, 0.0, 0.0); //Black
    glPopMatrix();


    glPopMatrix();

    glEnable(GL_LIGHTING);
}