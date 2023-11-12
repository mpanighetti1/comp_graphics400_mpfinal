
#ifndef HELPER_HW3_H
#define HELPER_HW3_H

#include <cstdlib>
#include <iostream>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

class Helper_HW3 {

public:
    // Stroke Text Function.
    static void writeStrokeString(void* font, const char* string, float lineWidth, float size);

    //Reusable Square Function
    static void draw_square(float x, float y, float z, float length, GLenum mode);

    //Reusable Ellipse/Circle Function
    static void draw_ellipse(float x, float y, float z, float w, float l, float r, GLenum mode);

    //Reusable Cylinder Function
    static void draw_cylinder(float height, float radius, float x, float y, float z, GLenum mode, GLenum mode2);

    //Reusable 3-D Cone Function
    static void draw_cone(float radius, float height, int segments, float* color1, float* color2);

    //Reusable 3-D Ellipsoid Function
    static void draw_ellipsoid(float length, float width, float height, bool solid);

    //Reusable 3-D Prism Function
    static void draw_prism(float height, float length, float width);

private:

};

#endif
