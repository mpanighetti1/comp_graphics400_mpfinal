#ifndef HELPER_HW4_H
#define HELPER_HW4_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159
#define FT 12.0

class Helper_HW4 {
public:
    // Draw a scaled cube with custom normals
    static void drawScaledCube(float width, float height, float depth, 
        const bool lightSides[6]);

    // Draw a scaled cube with custom normals + No Red Light
    static void drawScaledCube_NoRed(float width, float height, float depth,
        const bool lightSides[6]);

    // Draw Cylinder
    static void drawCylinder(float baseRadius, float topRadius, float height,
        int slices, int stacks);

private:
};

#endif