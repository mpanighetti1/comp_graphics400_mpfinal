/*******************************************
* Michael Panighetti
*
* Helper Header
********************************************/

#ifndef HELPER_FINAL_H
#define HELPER_FINAL_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <array>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#  include <unistd.h>
#else
#  include <GL/glut.h>
#  include <Windows.h>
#endif

const double PI = 3.141592653589793;
const double FT = 12.0;

// Game Globals
extern int turn;
extern int countDown;

// Texture Globals
extern GLuint tableTexture;
extern GLuint carpetTexture;
extern GLuint ballTexture;
extern GLuint xNeg_spaceTexture; // 3
extern GLuint xPos_spaceTexture; // 4
extern GLuint zNeg_spaceTexture; // 5
extern GLuint zPos_spaceTexture; // 6
extern int itemID;

// Ball Movement Globals
extern double ball_throw_rotation;
extern double ball_throw_rotation_divider;
extern bool ball_missed;
extern bool throw_ball;

// Struct of bitmap file.
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char* data;
};

class Helper_Final {
public:

    ///////////// CHANGING EXTERNAL VARIABLES ///////////////

    static void change_ball_throw_rotation(double new_value);

    ///////////// CHANGING EXTERNAL VARIABLES ///////////////

    // Draw a scaled cube with custom normals - Textured Top
    static void drawScaledCube_topText(float width, float height, float depth,
        bool applyTexture);

    // Draw a scaled cube with custom normals - Textured +X Side
    static void drawScaledCube_xPosText(float width, float height, float depth,
        bool applyTexture);

    // Draw a scaled cube with custom normals - Textured -X Side
    static void drawScaledCube_xNegText(float width, float height, float depth,
        bool applyTexture);

    // Draw a scaled cube with custom normals - Textured -Z Side
    static void drawScaledCube_zNegText(float width, float height, float depth,
        bool applyTexture);

    // Draw a scaled cube with custom normals - Textured +Z Side
    static void drawScaledCube_zPosText(float width, float height, float depth,
        bool applyTexture);

    // Draw Cylinder
    static void drawCylinder(float baseRadius, float topRadius, float height,
        int slices, int stacks);

    // Draw A Sphere But With Texture Coords
    static void drawTexturedSphere(GLfloat radius, GLint slices, GLint stacks,
        GLuint textureID);
    
    // Routine to read a bitmap file.
    static BitMapFile* getBMPData(std::string filename);

    // Load external textures.
    static void loadExternalTextures();

    // Render Bitmap Text
    static void renderScaledText(float winSize_X, float winSize_Y,
        float x, float y, float scale, void* font, const char* text);

    // For Collision, Check If There Is An Intersection Of Spheres
    static int checkSpheresIntersection(double x1, double y1, double z1, double r1,
        double x2, double y2, double z2, double r2);

    // Get ID for Color Picking
    static int getID(int x, int y);

private:
};

#endif