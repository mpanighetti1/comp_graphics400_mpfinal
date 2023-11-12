/*********************************************************
*
* Main file for HW4
*
* Official Name:  Michael Panighetti
*
* E-mail:  mjpanigh@syr.edu
*
* Assignment:  HW4 - Haunted House
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  April 10th, 2023
*
* References: 
* http://www.rgbtool.com/ - For Colors
* Framed Image (Henryk Weyssenhoff - Przeczucie 1893):
* https://commons.wikimedia.org/wiki/File:Henryk_Weyssenhoff_-_Przeczucie_1893.jpg
*
* Interactions:
*   - 'up arrow' - Move Forwards
*   - 'down arrow' - Move Backwards
*   - 'right arrow' - Turn Right
*   - 'left arrow' - Turn left
*   - 'page up' - Look up
*   - 'page down' - Look down
*   - 'd' - Open Door
*   - 'l' - Ceiling Light On/Off
*   - 's' - Lift Window Shades
*   - 'f' - Pick up Flash Light
*   - Right Click For Menu: 
*           Launch Orb
*           Event Code Red
*           Event Code Blue
*           Reset Orb
**********************************************************/

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>

#include "helper_HW4.h"
#include "stillobjects_HW4.h"
#include "animation_HW4.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glut.h>
//#  include <GL/glext.h>
#endif

#define PI 3.14159
#define FT 12.0

// Window Settings Globals
float winSize_X = 800;
float winSize_Y = 600;
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24; // Font selection.

// Color Picking Globals
int itemID = 0;
int front_door = 1;   // Green
int light_switch = 2; // Blue
int window_shade = 3; // Red
bool selecting = false;
float click_x, click_y;

// Light Setting Globals
bool ceiling_light_on = false;
bool flash_light_on = false;
bool outdoor_light_on = false;

// Animation Globals
bool door_moving = false;
bool window_shades_moving = false;
bool orb_moving = false;
bool claudron_glowing = false;
bool entered_building = false;
bool random_num_picked = false;
int random_integer = 0;

// Texture Globals
static unsigned int texture[2];
static int id = 0;

// Camera Globals
static float camera_angle_h = 270.0; // Horizontal angle
static float camera_angle_v = -5.0; // Vertical angle
// Used in calculating eye_x & eye_z
static float camera_x = -258.176, camera_z = 0; 

// LookAt Variables
static float eye_x;
static float eye_y;
static float eye_z;
static float lookAt_x;
static float lookAt_y;
static float lookAt_z;
static float up_x;
static float up_y;
static float up_z;

// Directional Light Of Sun
float sunlightPos1[] = { 0.0, 1000.0, 0.0, 0.0 };

// Ceiling Light Point Light 
float ceiling_lightPos[] = { 16 * FT, 8.0 * FT, 0 * FT, 1.0 };

// Window Light Point Light
float window_lightPos[] = { 7.5 * FT, 5.0 * FT, 0 * FT, 1.0 };

// Cauldron Glow Point Light
float cauldron_glowPos[] = { 21 * FT, 2.5 * FT, -7 * FT, 1.0 };

// Outdoor Point Light
float outdoor_lightPos[] = { 5 * FT, 11.0 * FT, 0 * FT, 1.0 };
float outdoorlightDiff[] = { 2.0, 0.0, 0.0, 0.0 };
float outdoorlightSpec[] = { 2.0, 0.0, 0.0, 0.0 };

// Flash Light Vectors
float flash_light_spotAngle = 40.0; // Spotlight cone half-angle.
float flash_light_spotExponent = 0; // Spotlight exponent = attenuation.

// Default Material Vectors - Shine
float matSpec[] = { 0.0, 0.0, 0.0, 1.0 };
float matShine[] = { 0.0 };

// Struct of bitmap file.
struct BitMapFile
{
    int sizeX;
    int sizeY;
    unsigned char* data;
};

// Routine to read a bitmap file.
BitMapFile* getBMPData(std::string filename)
{
    BitMapFile* bmp = new BitMapFile;
    unsigned int size, offset, headerSize;

    // Read input file name.
    std::ifstream infile(filename.c_str(), std::ios::binary);

    // Get the starting point of the image data.
    infile.seekg(10);
    infile.read((char*)&offset, 4);

    // Get the header size of the bitmap.
    infile.read((char*)&headerSize, 4);

    // Get width and height values in the bitmap header.
    infile.seekg(18);
    infile.read((char*)&bmp->sizeX, 4);
    infile.read((char*)&bmp->sizeY, 4);

    // Allocate buffer for the image.
    size = bmp->sizeX * bmp->sizeY * 24;
    bmp->data = new unsigned char[size];

    // Read bitmap data.
    infile.seekg(offset);
    infile.read((char*)bmp->data, size);

    /*
    // Reverse color from bgr to rgb.
    int temp;
    for (int i = 0; i < size; i += 3)
    {
        temp = bmp->data[i];
        bmp->data[i] = bmp->data[i + 2];
        bmp->data[i + 2] = temp;
    }
    */

    return bmp;
    
}

// Load external textures.
void loadExternalTextures()
{
    // Local storage for bmp image data.
    BitMapFile* image[2];

    // Load the texture.
    image[0] = getBMPData("Textures/creepy_lit.bmp");
    image[1] = getBMPData("Textures/creepy_lowlight.bmp");

    // Activate texture index texture[0]. 
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);

    // Activate texture index texture[1]. 
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Specify an image as the texture to be bound with the currently active texture index.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0,
        GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);
}

// Render Bitmap Text
void renderScaledText(float x, float y, float scale, void* font, const char* text) {

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winSize_X, 0, winSize_Y);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f); // White
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glPopMatrix();

    glDisable(GL_COLOR_MATERIAL);
}

// For Collision, Check If There Is An Intersection Of Spheres
int checkSpheresIntersection(float x1, float y1, float z1, float r1,
    float x2, float y2, float z2, float r2)
{
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2) + (z1 - z2) * (z1 - z2) <= (r1 + r2) * (r1 + r2));
}

// Near Flashlight?
bool flashlight_Collision()
{
    if (checkSpheresIntersection(eye_x, eye_y + (-2 * FT), eye_z, 2 * FT,
        18 * FT, 4.4 * FT, 7.5 * FT, 2 * FT)) return true;
    return false;
}

// Near Cauldron?
bool cauldron_Collision()
{
    if (checkSpheresIntersection(eye_x, eye_y + (-5.5 * FT), eye_z, 4 * FT,
        21 * FT, 2.5 * FT, -7 * FT, 4 * FT)) return true;
    return false;
}

// Through Door?
bool red_Light_Collision()
{
    if (checkSpheresIntersection(eye_x, eye_y + (-2 * FT), eye_z, 2 * FT,
        8 * FT, 4.5 * FT, 0 * FT, 2 * FT)) return true;
    return false;
}

// Get ID for Color Picking
void getID(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        itemID = front_door;  // 1 - Green
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255)
    {
        itemID = light_switch;  // 2 - Blue
    }
    else if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0)
    {
        itemID = window_shade;  // 3 - Red
    }
    else itemID = 0; // Default - Nothing

    selecting = false;
    glutPostRedisplay();
}

// Main setup
void main_setup(void)
{
    glClearColor(0.6768, 0.8874, 0.94, 1.0); //Sky's Color

    // Create texture index array.
    glGenTextures(2, texture);

    // Load external texture and generate and load procedural texture.
    loadExternalTextures();

    // Specify how texture values combine with current surface color values.
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    // Seed the random number generator with the current time 
    // "2 Random Outcomes"
    srand(time(0)); 

    // Enable Depth Testing By Default.
    glEnable(GL_DEPTH_TEST);
    // Enable Lighting By Default
    glEnable(GL_LIGHTING);
    // Enable Normalizing By Default
    glEnable(GL_NORMALIZE);  
    // Enable Smooth Shading By Default
    glShadeModel(GL_SMOOTH);

    float globalAmb[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    // Sunlight = LIGHT0
    glEnable(GL_LIGHT0); // Activated By Default
    float sunlightDiff[] = { 2.0, 2.0, 2.0, 0.0 };
    float sunlightSpec[] = { 2.0, 2.0, 2.0, 0.0 };
    float sunlightAmb[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunlightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunlightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunlightAmb);

    // Orb Glow - LIGHT1
    float orb_glowDiff[] = { 0.0, 0.0, 1.0 / 2, 1.0 };
    float orb_glowSpec[] = { 0.0, 0.0, 1.0 / 2, 1.0 };
    float orb_glowAmb[] = { 0.00, 0.00, 0.00, 1.0 };
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 5);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, orb_glowDiff);
    glLightfv(GL_LIGHT1, GL_SPECULAR, orb_glowSpec);
    glLightfv(GL_LIGHT1, GL_AMBIENT, orb_glowAmb);

    // Ceiling Light Indoors - LIGHT4
    float ceiling_lightDiff[] = { 1.0 * 3, 0.835 * 3, 0.667 * 3, 0.0 };
    float ceiling_lightSpec[] = { 1.0 * 3, 0.835 * 3, 0.667 * 3, 0.0 };
    float ceiling_lightAmb[] = { 0.00, 0.00, 0.00, 1.0 };
    glLightfv(GL_LIGHT4, GL_DIFFUSE, ceiling_lightDiff);
    glLightfv(GL_LIGHT4, GL_SPECULAR, ceiling_lightSpec);
    glLightfv(GL_LIGHT4, GL_AMBIENT, ceiling_lightAmb);

    // Cauldron Glow - LIGHT6
    glEnable(GL_LIGHT6); // Activate By Default
    float cauldron_glowDiff[] = { 0.0, 0.1, 0.0, 1.0 };
    float cauldron_glowSpec[] = { 0.0, 0.1, 0.0, 1.0 };
    float cauldron_glowAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT6, GL_DIFFUSE, cauldron_glowDiff);
    glLightfv(GL_LIGHT6, GL_SPECULAR, cauldron_glowSpec);
    glLightfv(GL_LIGHT6, GL_AMBIENT, cauldron_glowAmb);

    //Flash Light - LIGHT7
    float flash_lightDiffAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
    float flash_lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };    
    glLightfv(GL_LIGHT7, GL_AMBIENT, flash_lightAmb);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, flash_lightDiffAndSpec);
    glLightfv(GL_LIGHT7, GL_SPECULAR, flash_lightDiffAndSpec); 

    // Outdoor Light = LIGHT2 
    glEnable(GL_LIGHT2);
    float outdoorlightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, -1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, outdoorlightDiff);
    glLightfv(GL_LIGHT2, GL_SPECULAR, outdoorlightSpec);
    glLightfv(GL_LIGHT2, GL_AMBIENT, outdoorlightAmb);

    // Window Light As Shades Raise
    float window_lightAmb[] = { 0.00, 0.00, 0.00, 1.0 };
    glLightfv(GL_LIGHT5, GL_AMBIENT, window_lightAmb);

    // Default Material Properties
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1); // Enable local viewpoint

    // Cull back faces.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void display(void) {      

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();       

    // Generate a random integer between 1 and 2
    // "2 Random Outcomes"
    if (random_num_picked == false) {
        random_integer = rand() % 2 + 1;
        random_num_picked = true;
    }
    
    if (flashlight_Collision()) {       
        if (flash_light_on) {
            renderScaledText(winSize_X / 2 - 100, winSize_Y / 2, 41, (void*)font,
                "Press 'f' to put the flash light back on the table.");
        }
        else {
            renderScaledText(winSize_X / 2 - 100, winSize_Y / 2, 4, (void*)font,
                "Press 'f' to pick up the flash light");
        }        
    }

    eye_x = camera_x - 10 * sin((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    eye_y = 72.0 + 10 * sin((PI / 180.0) * camera_angle_v);
    eye_z = camera_z - 10 * cos((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    lookAt_x = camera_x - 11 * sin((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    lookAt_y = 72.0 + 11 * sin((PI / 180.0) * camera_angle_v);
    lookAt_z = camera_z - 11 * cos((PI / 180.0) * camera_angle_h) * cos((PI / 180.0) * camera_angle_v);
    up_x = 0.0;
    up_y = 1.0;
    up_z = 0.0;

    gluLookAt(eye_x, eye_y, eye_z,
              lookAt_x, lookAt_y, lookAt_z,
              up_x, up_y, up_z);       

    /* Light Positioning */ glDisable(GL_LIGHTING);   

    // Sunlight = Light0 Position1  
    glLightfv(GL_LIGHT0, GL_POSITION, sunlightPos1);

    // Ceiling Light = Light4 
    glLightfv(GL_LIGHT4, GL_POSITION, ceiling_lightPos);

    // Outdoor --> Indoor Light = Light5
    glLightfv(GL_LIGHT5, GL_POSITION, window_lightPos);

    // Cauldron Glow = Light6
    glLightfv(GL_LIGHT6, GL_POSITION, cauldron_glowPos);    

    // Flash Light = Light7
    float flash_lightPos[] = { 0.0, 0.0, 0.0, 1.0 };
    float flash_light_spotDirection[] = { 0.0, 0.0, -1.0 };
    glPushMatrix();
    glTranslated(eye_x + (2 * FT), eye_y - (1.5 * FT), eye_z - (3 * FT));
    glTranslated(-1.5 * FT, 0, 3 * FT);
    glRotated(camera_angle_h, 0, 1, 0);
    glTranslated(1.5 * FT, 0, -3 * FT);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, flash_light_spotDirection);
    glLightfv(GL_LIGHT7, GL_POSITION, flash_lightPos);
    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, flash_light_spotAngle);
    glLightf(GL_LIGHT7, GL_SPOT_EXPONENT, flash_light_spotExponent);
    glPopMatrix();

    // Outdoor Light = Light2
    glLightfv(GL_LIGHT2, GL_POSITION, outdoor_lightPos);
       
    /* End Light Positioning */ glEnable(GL_LIGHTING);   
   
    if (!red_Light_Collision()) {
        glEnable(GL_LIGHT2);
    }
    else if (red_Light_Collision()) {
        if (!entered_building) {            
            entered_building = !entered_building;
        }
    }
        
    STILLOBJECTS_HW4::outdoor_light(outdoor_light_on);
      
    STILLOBJECTS_HW4::draw_background(outdoor_light_on);

    if (ceiling_light_on) glEnable(GL_LIGHT4); // Ceiling Light Activated
    else glDisable(GL_LIGHT4); // Ceiling Light Deactivated 

    if (flash_light_on) glEnable(GL_LIGHT7); // Flash Light Activated
    else  glDisable(GL_LIGHT7); // Flash Light Deactivated

    ANIMATION_HW4::flash_light(eye_x, eye_y, eye_z, camera_angle_h,
        ceiling_light_on, flash_light_on);

    STILLOBJECTS_HW4::draw_ceiling_light(ceiling_light_on);

    ANIMATION_HW4::draw_window_shades(selecting);

    ANIMATION_HW4::draw_door(selecting);    

    STILLOBJECTS_HW4::draw_light_switch(selecting, ceiling_light_on);

    ANIMATION_HW4::draw_cauldron(cauldron_Collision());

    STILLOBJECTS_HW4::draw_table();

    STILLOBJECTS_HW4::draw_structure();

    ANIMATION_HW4::draw_orb(random_integer);

    /* Textures */ glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    // Activate a texture.
    if (ceiling_light_on) {
        glBindTexture(GL_TEXTURE_2D, texture[0]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texture[1]);
    }

    glPushMatrix();
    glTranslated(23.9 * FT, 5.5 * FT, 0 * FT);
    glRotated(-90, 0, 1, 0);
    glScaled(0.8, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0, 0.0); glVertex3f(-5 * FT, -3 * FT, 0.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(5 * FT, -3 * FT, 0.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(5 * FT, 3 * FT, 0.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-5 * FT, 3 * FT, 0.0);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    /* Textures */ glEnable(GL_LIGHTING);
}

// Color Picking Step
void drawScene(void)
{
    //draw everything with special coloring for selecting
    //but don't display on computer screen.
    if (selecting)
    {
        display();
        getID(click_x, click_y);
        if (itemID == 1) door_moving = !door_moving;
        if (itemID == 2) ceiling_light_on = !ceiling_light_on;
        if (itemID == 3) window_shades_moving = !window_shades_moving;        
    }
    //draw everything 
    else
    {
        display();
        glutSwapBuffers();
    }
}

// Timer function callback for door swinging
void animation_doorSwing(int someValue)
{
    if (door_moving == true) 
        door_moving = ANIMATION_HW4::calc_animation_doorSwing(door_moving);
    glutTimerFunc(10, animation_doorSwing, 1);
}

// Timer function callback for shade
void animation_windowShades(int someValue)
{
    if (window_shades_moving == true)
        window_shades_moving = ANIMATION_HW4::calc_animation_windowShades(window_shades_moving);
    glutTimerFunc(10, animation_windowShades, 1);
}

// Timer function callback for orb
void animation_orbMovement(int someValue)
{   
    if (orb_moving == true)
        orb_moving = ANIMATION_HW4::calc_animation_orb(orb_moving, 
            cauldron_Collision(),
            random_integer);
    glutTimerFunc(10, animation_orbMovement, 1);
}

// Timer function callback for cauldron glow
void animation_cauldronGlow(int someValue)
{    
    ANIMATION_HW4::calc_cauldron_glow(claudron_glowing, cauldron_Collision(),
        random_integer);
    glutTimerFunc(1, animation_cauldronGlow, 1);
}

// Timer function callback for red Light off
void animation_redLight(int someValue)
{
    //If the value is within range of the epsilon value, they are "close enough"
    //This accounts for floating-point arithmetic inaccuracies
    const float epsilon = 0.005;

    if (entered_building && std::abs(outdoorlightDiff[0] - 0.0) > epsilon) {
        
        outdoorlightDiff[0] -= 1.0 / 50.0;
        outdoorlightSpec[0] -= 1.0 / 50.0;

        glLightfv(GL_LIGHT2, GL_DIFFUSE, outdoorlightDiff);
        glLightfv(GL_LIGHT2, GL_SPECULAR, outdoorlightSpec);
    }
    glutTimerFunc(1, animation_redLight, 1);
}

// OpenGL window reshape routine.
void main_resize(int w, int h)
{     
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    float fov = 60.0;
    gluPerspective(fov, aspect, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    winSize_Y = h;
    winSize_X = w;    
}

// Mouse control function
void main_MouseControl(int button, int state, int x, int y)
{
    double xWorld, yWorld;
    if (state == GLUT_DOWN && button == GLUT_LEFT)
    {      
        selecting = true;
        click_x = x;
        click_y = winSize_Y - y;
        glutPostRedisplay();
    }
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'd': //Opening Door
        door_moving = !door_moving;
        break;
    case 'l': //Indoor Ceiling Light
        ceiling_light_on = !ceiling_light_on;
        break;
    case 's': //Window Shades
        if (window_shades_moving == false) {
            window_shades_moving = !window_shades_moving;
        }
        break;
    case 'f': //Flash Light On
        if (flashlight_Collision()) {
            flash_light_on = !flash_light_on;
        }
        break;
    default:
        break;
    }    
    glutPostRedisplay();
}

// Special keyboard input processing routine.
void specialKeyInput(int key, int x, int y)
{
    float tempxVal = camera_x,
        tempzVal = camera_z,
        tempAngle_h = camera_angle_h,
        tempAngle_v = camera_angle_v,
        step = 4.0;

    switch (key)
    {
    case GLUT_KEY_RIGHT:
        tempAngle_h = camera_angle_h - 5.0;
        break;
    case GLUT_KEY_LEFT:
        tempAngle_h = camera_angle_h + 5.0;
        break;
    case GLUT_KEY_UP:
        tempxVal = camera_x - (step * (sin(camera_angle_h * PI / 180.0)));
        tempzVal = camera_z - (step * (cos(camera_angle_h * PI / 180.0)));
        break;
    case GLUT_KEY_DOWN:
        tempxVal = camera_x + (step * sin(camera_angle_h * PI / 180.0));
        tempzVal = camera_z + (step * cos(camera_angle_h * PI / 180.0));
        break;
    case GLUT_KEY_PAGE_UP:
        if (camera_angle_v <= 30) tempAngle_v = camera_angle_v + 5.0;
        break;
    case GLUT_KEY_PAGE_DOWN:
        if (camera_angle_v >= -50) tempAngle_v = camera_angle_v - 5.0;
        break;
    default:
        break;
    }

    // Horizontal Angle Correction.
    if (tempAngle_h > 360.0) tempAngle_h -= 360.0;
    if (tempAngle_h < 0.0) tempAngle_h += 360.0;

    camera_x = tempxVal;
    camera_z = tempzVal;
    camera_angle_h = tempAngle_h;
    camera_angle_v = tempAngle_v;

    glutPostRedisplay();
}

// The top menu callback function.
void main_menu(int id)
{
    switch (id)
    {
    case 1:
        if (orb_moving == false) {
            orb_moving = !orb_moving;
        }
        break;
    case 2:
        random_integer = 2;
        break;
    case 3:
        random_integer = 1;
        break;
    case 4:
        ANIMATION_HW4::reset();
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

// Right click menu
void right_clickMenu()
{
    glutCreateMenu(main_menu);
    glutAddMenuEntry("Launch Orb", 1);
    glutAddMenuEntry("Event Code Red", 2);
    glutAddMenuEntry("Event Code Blue", 3);
    glutAddMenuEntry("Reset Orb", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Instructions
void printInstructions()
{
    std::cout << " * Interactions: " << std::endl;
    std::cout << " * - 'up arrow' - Move forwards." << std::endl;
    std::cout << " * - 'down arrow' - Move backwards." << std::endl;
    std::cout << " * - 'right arrow' - Turn right." << std::endl;
    std::cout << " * - 'left arrow' - Turn left." << std::endl;
    std::cout << " * - 'page up' - Look up." << std::endl;
    std::cout << " * - 'page down' - Look down." << std::endl;
    std::cout << " * - 'd' - Open Door" << std::endl;
    std::cout << " * - 'l' - Ceiling Light On/Off" << std::endl;
    std::cout << " * - 's' - Lift Window Shades" << std::endl;
    std::cout << " * - 'f' - Pick up Flash Light" << std::endl;
    std::cout << " * - RIght Click For Menu:" << std::endl;
    std::cout << " *       - Launch Orb" << std::endl;
    std::cout << " *       - Event Code Red" << std::endl;
    std::cout << " *       - Event Code Blue" << std::endl;
    std::cout << " *       - Reset Orb" << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{

    printInstructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    //Window Size:
    glutInitWindowSize(winSize_X, winSize_Y);
    glutInitWindowPosition(850, 100);

    //Create Window:
    glutCreateWindow("The Haunted House");

    //Initialization for Window:
    main_setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(main_resize);
    glutMouseFunc(main_MouseControl);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    right_clickMenu();

    //Animation - Door Swing
    glutTimerFunc(1, animation_doorSwing, 1);

    //Animation - Window Shades
    glutTimerFunc(1, animation_windowShades, 1);

    //Animation - Orb Movement
    glutTimerFunc(1, animation_orbMovement, 1);

    //Animation - Cauldron Glow
    glutTimerFunc(1, animation_cauldronGlow, 1);

    //Animation - Red Light
    glutTimerFunc(1, animation_redLight, 1);
    
    glutMainLoop();

    return 0;
}