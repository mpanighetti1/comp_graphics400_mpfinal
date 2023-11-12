/************************************************** ******
*
* Main file for HW3 - Includes Animation Aspects
*
* Official Name:  Michael Panighetti
*
* E-mail:  mjpanigh@syr.edu
*
* Assignment:  HW3 - Dragonfly Animation
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  March 21, 2023
*
* References: None - Other than class material.
*
* Interactions:
*   - 'd' Dragonfly Flies One Time Around.
*   - '1' - View from North.
*   - '2' - View from South.
*   - '3' - View from East.
*   - '4' - View from West.
*   - 'b' - Bird's eye view.
*   - 'c' - Dragonfly close-up view.
*   - 'h' - Dragonfly head-on close-up view.
*   - 's' - Reset.
*   - 'f' - Toggle Fire Breathing.
*   - 'Up Arrow' - Increase Cloud Speed.
*   - 'Down Arrow' - Decrease Cloud Speed.
*   - 'Right Arrow' - Increase Dragonfly Speed.
*   - 'Left Arrow' - Decrease Dragonfly Speed.
*   - Left-click on dragonfly to make it breathe fire.
*   - Left-click, hold, & drag any flag post to reposition.
*   - Dragonfly will always fly to Green, then Blue, then Red.
*
**********************************************************/

#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>

#include "helper_HW3.h"
#include "scene_HW3.h"
#include "dragonfly_HW3.h"

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

// Window Settings Globals
char Camera_position = 's';
float winSize_X = 700;
float winSize_Y = 700;

// Program Settings Globals
int obj1_state = 1;
int obj2_state = 1;
int obj3_state = 1;

// Dragonfly Settings
bool Dragonfly_circuit = false;
bool Dragonfly_fire = false;
bool Dragonfly_wings = true;
int wing_leg = 1;
float Dragonfly_speed = 110; //Lower is faster
float Dragonfly_right_wing_angle = 0;
float Dragonfly_left_wing_angle = 0;
float Dragonfly_angle = 0;
float Dragonfly_height = 70;
static float D_Vx, D_Vy, D_Vz;
static float Dx = 0, Dy = 0, Dz = 0; //partial vector in direction of V
static float D_t = 0;
static float D_startX, D_startY, D_startZ;//starting point for this D_leg of trip
static float D_endX, D_endY, D_endZ; //ending point for this D_leg of trip

// D_leg 1 Lift-Off from Lily Pad.
// D_leg 2 Lily Pad to Obj1
// D_leg 3 Obj1 to Obj2
// D_leg 4 Obj2 to Obj3
// D_leg 5 Obj3 to Above Lily Pad
// D_leg 6 Landing.
// D_leg 7 Stop Signal
static int D_leg = 1; 

// Cloud Animation
bool Cloud_movement = true;
float Cloud_speed = 0.0625; //Lower is slower
static float Cx = 0, Cy = 0, Cz = 0; //partial vector in direction of V
float Cloud_X = 0.0;
float Cloud_Y = 0.0;
float Cloud_Z = 0.0;

// Mouse Globals
bool dragging = false;
int prevMouseX, prevMouseY;
bool Obj1_Selected = false;
bool Obj2_Selected = false;
bool Obj3_Selected = false;

// Positioning Globals.
float Lily_pad_X = 40.0;
float Lily_pad_Y = 0.5;
float Lily_pad_Z = -40.0;

float Obj1_X = 60.0;
float Obj1_Y = 0.0;
float Obj1_Z = 80.0;

float Obj2_X = -70.0;
float Obj2_Y = 0.0;
float Obj2_Z = 70.0;

float Obj3_X = -80.0;
float Obj3_Y = 0.0;
float Obj3_Z = -80.0;

// Initialization routine.

//Compute the vector from start to end for circuit animation.
void assignEndpoints_circuit(
    float x1, float y1, float z1,
    float x2, float y2, float z2)
{
    D_startX = x1;
    D_startY = y1;
    D_startZ = z1;
    D_endX = x2;
    D_endY = y2;
    D_endZ = z2;
    D_Vx = D_endX - D_startX;
    D_Vy = D_endY - D_startY;
    D_Vz = D_endZ - D_startZ;
}

// Function for setting which object is selected
void identifyObject(int x, int y)
{
    unsigned char pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

    Obj1_Selected = false;
    Obj2_Selected = false;    
    Obj3_Selected = false;
    
    if ((int)pixel[0] == 0 && (int)pixel[1] == 255 && (int)pixel[2] == 0)
    {
        Obj1_Selected = true;
    }
    else if ((int)pixel[0] == 0 && (int)pixel[1] == 0 && (int)pixel[2] == 255)
    {
        Obj2_Selected = true;
    }
    else if ((int)pixel[0] == 255 && (int)pixel[1] == 0 && (int)pixel[2] == 0)
    {
        Obj3_Selected = true;
    }
    else if ((int)pixel[0] == 59 && (int)pixel[1] == 59 && (int)pixel[2] == 59)
    {
        Dragonfly_fire = !Dragonfly_fire;
    }

    dragging = false;
    glutPostRedisplay();
}

void display(void)
{
    glClearColor(0.6862, 0.8766, 0.94, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);       
    glLoadIdentity();  

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float eye_x = 0, eye_y = 150, eye_z = 0;
    float lookAt_x = 0, lookAt_y = 0, lookAt_z = 0;
    float up_x = 1, up_y = 0, up_z = 0;


    // Set eye of LookAt based on camera position variable
    switch (Camera_position) {
    case 'n': //North
        eye_x = 150.0;
        eye_y = 150.0;
        eye_z = 0.0;
        lookAt_x = 0.0;
        lookAt_y = 0.0;
        lookAt_z = 0.0;
        up_x = -1.0;
        up_y = 0.0;
        up_z = 0.0;
        break;
    case 's': //South
        eye_x = -150.0;
        eye_y = 150.0;
        eye_z = 0.0;
        lookAt_x = 0.0;
        lookAt_y = 0.0;
        lookAt_z = 0.0;
        up_x = 1.0;
        up_y = 0.0;
        up_z = 0.0;
        break;
    case 'e': //East
        eye_x = 0.0;
        eye_y = 150.0;
        eye_z = 150.0;
        lookAt_x = 0.0;
        lookAt_y = 0.0;
        lookAt_z = 0.0;
        up_x = 0.0;
        up_y = 0.0;
        up_z = -1.0;
        break;
    case 'w': //West
        eye_x = 0.0;
        eye_y = 150.0;
        eye_z = -150.0;
        lookAt_x = 0.0;
        lookAt_y = 0.0;
        lookAt_z = 0.0;
        up_x = 0.0;
        up_y = 0.0;
        up_z = 1.0;
        break;
    case 'b': //Birds Eye View
        eye_x = 0.0;
        eye_y = 200.0;
        eye_z = 0.0;
        lookAt_x = 0.0;
        lookAt_y = 0.0;
        lookAt_z = 0.0;
        up_x = 1.0;
        up_y = 0.0;
        up_z = 0.0;
        break;
    case 'c': //Close Up Of Dragonfly
        eye_x = Lily_pad_X - 10;
        eye_y = Lily_pad_Y + 25;
        eye_z = Lily_pad_Z + 10;
        lookAt_x = Lily_pad_X;
        lookAt_y = Lily_pad_Y;
        lookAt_z = Lily_pad_Z;
        up_x = 0.0;
        up_y = 1.0;
        up_z = 0.0;
        break;
    case 'h': //Front Close Up Of Dragonfly
        eye_x = Lily_pad_X + 30;
        eye_y = Lily_pad_Y;
        eye_z = Lily_pad_Z + 30;
        lookAt_x = Lily_pad_X;
        lookAt_y = Lily_pad_Y;
        lookAt_z = Lily_pad_Z;
        up_x = 0.0;
        up_y = 1.0;
        up_z = 0.0;
        break;
    default:
        break;
    }

    gluLookAt(eye_x, eye_y, eye_z, 
              lookAt_x, lookAt_y, lookAt_z,
              up_x, up_y, up_z);
        
    glShadeModel(GL_FLAT);
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0); //Black
    SCENE_HW3::draw_background();
    SCENE_HW3::draw_lily_pad(Lily_pad_X, Lily_pad_Y, Lily_pad_Z);
    glShadeModel(GL_SMOOTH);

    /*Shadows Begin*/glDisable(GL_LIGHTING);
    /*Shadows Begin*/glDisable(GL_DEPTH_TEST);

    /*D*/glPushMatrix();
    glScalef(1.0, 0.0, 1.0);

    SCENE_HW3::draw_objects(Obj1_X, Obj1_Y, Obj1_Z,
        Obj2_X, Obj2_Y, Obj2_Z,
        Obj3_X, Obj3_Y, Obj3_Z, 1);

    glPushMatrix();
    glTranslated(Cx, Cy, Cz);
    SCENE_HW3::draw_cloud(1);
    glPopMatrix();

    /*A*/glPushMatrix();
    glTranslated(Dx, Dy, Dz);
    glTranslated(D_startX, D_startY, D_startZ);
    glRotatef(Dragonfly_angle, 0.0, 1.0, 0.0);
    glScalef(0.75, 0.75, 0.75);

    /*B*/glPushMatrix();
    glRotated(Dragonfly_right_wing_angle, 1.0, 0.0, 1.0);
    DRAGONFLY_HW3::draw_dragonfly_right_wings(1);
    /*B*/glPopMatrix();

    /*C*/glPushMatrix();
    glRotated(Dragonfly_left_wing_angle, 1.0, 0.0, 1.0);
    DRAGONFLY_HW3::draw_dragonfly_left_wings(1);
    /*C*/glPopMatrix();

    DRAGONFLY_HW3::draw_dragonfly(1);

    /*A*/glPopMatrix();
    
    /*D*/glPopMatrix();

    /*Shadows End*/glEnable(GL_DEPTH_TEST);
    /*Shadows End*/glEnable(GL_LIGHTING);

    SCENE_HW3::draw_objects(Obj1_X, Obj1_Y, Obj1_Z,
        Obj2_X, Obj2_Y, Obj2_Z,
        Obj3_X, Obj3_Y, Obj3_Z, 0);

    glPushMatrix();
    glTranslated(Cx, Cy, Cz);
    SCENE_HW3::draw_cloud(0);
    glPopMatrix();  
    
    /*A*/glPushMatrix();
    glTranslated(Dx, Dy, Dz);
    glTranslated(D_startX, D_startY, D_startZ);
    glRotatef(Dragonfly_angle, 0.0, 1.0, 0.0);
    glScalef(0.75, 0.75, 0.75);

    /*B*/glPushMatrix();
    glRotated(Dragonfly_right_wing_angle, 1.0, 0.0, 1.0);
    DRAGONFLY_HW3::draw_dragonfly_right_wings(0);
    /*B*/glPopMatrix();

    /*C*/glPushMatrix();
    glRotated(Dragonfly_left_wing_angle, 1.0, 0.0, 1.0);
    DRAGONFLY_HW3::draw_dragonfly_left_wings(0);
    /*C*/glPopMatrix();
 
    DRAGONFLY_HW3::draw_dragonfly(0);

    if (Dragonfly_fire) DRAGONFLY_HW3::draw_dragonfly_fire();

    /*A*/glPopMatrix();

    glutSwapBuffers();

}

// Mouse control function
void main_MouseControl(int button, int state, int x, int y)
{
    double xWorld, yWorld;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float aspect = (float)winSize_X / (float)winSize_Y;
        float w = 100.0 * aspect;
        float h = 100.0;

        xWorld = (x / (float)winSize_X) * w;
        yWorld = ((winSize_Y - y) / (float)winSize_Y) * h;

        // Uncomment when finding window coordinates.
        // cout << x << "  " << y << endl;
        // cout << xWorld << "  " << yWorld << endl << endl;     
                
        prevMouseX = x;
        prevMouseY = y;
        dragging = true;
        identifyObject(x, winSize_Y - y);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        dragging = false;
    }
}

// Moving cubes/circuit checkpoints
void moving_objects(int x, int y) {
    
    float deltaZ = (x - prevMouseX) * 0.5;
    float deltaX = (prevMouseY - y) * 0.5;

    if (Obj1_Selected && !dragging) {
        Obj1_X += deltaX;
        Obj1_Z += deltaZ;     
    }
    else if (Obj2_Selected && !dragging) {
        Obj2_X += deltaX;
        Obj2_Z += deltaZ;
    }
    else if (Obj3_Selected && !dragging) {
        Obj3_X += deltaX;
        Obj3_Z += deltaZ;
    }

    prevMouseX = x;
    prevMouseY = y;
    glutPostRedisplay();
}

// Main setup
void main_setup(void)
{
    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Enable color material mode.
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Define light properties
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 }; // Positional light at (1, 1, 1)
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // Ambient light intensity
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // Diffuse light intensity
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Specular light intensity

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable light source
    glEnable(GL_LIGHT0);

    // Configure material properties for the objects in the scene
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 }; // Shininess value

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y, Lily_pad_Z,
        Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z);
}

// OpenGL window reshape routine.
void main_resize(int w, int h)
{     
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    gluPerspective(90.0, aspect, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    winSize_X = w;
    winSize_Y = h;

}

// Calculate position of dragonfly wings.
void calc_dragonfly_wings(void)
{
    if (Dragonfly_circuit) {
        if (wing_leg == 1) {
            if (Dragonfly_left_wing_angle < 20) {
                Dragonfly_left_wing_angle += 10;
                Dragonfly_right_wing_angle -= 10;
            }
            else wing_leg = 2;
        }

        if (wing_leg == 2) {
            if (Dragonfly_left_wing_angle > -20) {
                Dragonfly_left_wing_angle -= 10;
                Dragonfly_right_wing_angle += 10;
            }
            else wing_leg = 1;
        }
    }
    else {
        Dragonfly_left_wing_angle = 0;
        Dragonfly_right_wing_angle = 0;
    }

    glutPostRedisplay();
}

// Timer function for dragonfly wings
void animation_wings(int someValue)
{
    if (Dragonfly_wings) calc_dragonfly_wings();
    glutTimerFunc(1, animation_wings, 1);
}

// Calculate position of dragonfly.
void calc_dragonfly_circuit(void)
{
    //Check for new D_leg.
    if ((D_t == Dragonfly_speed || D_t == 0) && D_leg == 1) // Take Off
    {
        D_t = 0;
        D_leg = 2;
        assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y, Lily_pad_Z,
            Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z);

    }
    else if (D_t == Dragonfly_speed && D_leg == 2) //To Obj1
    {
        D_t = 0;
        D_leg = 3;
        assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z,
            Obj1_X, Obj1_Y + Dragonfly_height, Obj1_Z);

    }
    else if (D_t == Dragonfly_speed && D_leg == 3) //To Obj2
    {
        D_t = 0;
        D_leg = 4;
        assignEndpoints_circuit(Obj1_X, Obj1_Y + Dragonfly_height, Obj1_Z,
            Obj2_X, Obj2_Y + Dragonfly_height, Obj2_Z);
    }
    else if (D_t == Dragonfly_speed && D_leg == 4) //To Obj3
    {
        D_t = 0;
        D_leg = 5;
        assignEndpoints_circuit(Obj2_X, Obj2_Y + Dragonfly_height, Obj2_Z,
            Obj3_X, Obj3_Y + Dragonfly_height, Obj3_Z);
    }
    else if (D_t == Dragonfly_speed && D_leg == 5) //To Lily Pad
    {
        D_t = 0;
        D_leg = 6;
        assignEndpoints_circuit(Obj3_X, Obj3_Y + Dragonfly_height, Obj3_Z,
            Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z);
    }
    else if (D_t == Dragonfly_speed && D_leg == 6) // Landing
    {
        D_t = 0;
        D_leg = 7;
        assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z,
            Lily_pad_X, Lily_pad_Y, Lily_pad_Z);
    }
    else if (D_t == Dragonfly_speed && D_leg == 7) // Landing
    {      
        Dragonfly_circuit = false; // Stop the animation
    }      
    D_t++; // Increment Timer

    // Rotation
    if (D_leg != 2 && D_leg != 1 && D_leg != 7) {
        Dragonfly_angle -= (90.0 / Dragonfly_speed);
    }

    //Update Partial Vector
    Dx = D_t / Dragonfly_speed * D_Vx;
    Dy = D_t / Dragonfly_speed * D_Vy;
    Dz = D_t / Dragonfly_speed * D_Vz;

    glutPostRedisplay();
}

// Timer function for dragonfly circuit
void animation_circuit(int someValue)
{    
    if (Dragonfly_circuit) calc_dragonfly_circuit(); 
    glutTimerFunc(10, animation_circuit, 1);
}

// Idle function for cloud
void animation_cloud(void) {
    float threshold = 5.0f;

    auto random_float = [](float min, float max) {
        float random = ((float)rand()) / (float)RAND_MAX;
        return min + random * (max - min);
    };

    if (abs(Cx - Cloud_X) < threshold && abs(Cy - Cloud_Y) < threshold && abs(Cz - Cloud_Z) < threshold) {
        Cloud_X = random_float(-200, 200);
        Cloud_Y = random_float(0, 150);
        Cloud_Z = random_float(-200, 200);
    }

    if (abs(Cx - Cloud_X) >= threshold) {
        Cx += (Cloud_X > Cx ? Cloud_speed : -Cloud_speed);
    }

    if (abs(Cy - Cloud_Y) >= threshold) {
        Cy += (Cloud_Y > Cy ? Cloud_speed : -Cloud_speed);
    }

    if (abs(Cz - Cloud_Z) >= threshold) {
        Cz += (Cloud_Z > Cz ? Cloud_speed : -Cloud_speed);
    }

    glutPostRedisplay();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case '1':
        Camera_position = 'n';
        std::cout << "North View" << std::endl;
        break;
    case '2':
        Camera_position = 's';
        std::cout << "South View" << std::endl;
        break;
    case '3':
        Camera_position = 'e';
        std::cout << "East View" << std::endl;
        break;
    case '4':
        Camera_position = 'w';
        std::cout << "West View" << std::endl;
        break;
    case 'b':
        Camera_position = 'b';
        std::cout << "Bird's Eye View" << std::endl;
        break;
    case 'c':
        Camera_position = 'c';
        std::cout << "Dragonfly Close-Up View" << std::endl;
        break;
    case 'h':
        Camera_position = 'h';
        std::cout << "Dragonfly Front Close-Up View" << std::endl;
        break;
    case 'd':
        //Dragonfly Loop Once
        D_Vx = 0;
        D_Vy = 0;
        D_Vz = 0;
        Dx = 0;
        Dy = 0;
        Dz = 0;
        D_t = 0;
        D_leg = 1;
        Dragonfly_angle = 0;
        Dragonfly_circuit = !Dragonfly_circuit;
        assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y, Lily_pad_Z,
            Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z);
        break;
    case 's':
        //Reset
        Camera_position = 's';
        assignEndpoints_circuit(Lily_pad_X, Lily_pad_Y, Lily_pad_Z,
            Lily_pad_X, Lily_pad_Y + Dragonfly_height, Lily_pad_Z);
        Obj1_X = 60.0;
        Obj1_Y = 0.0;
        Obj1_Z = 80.0;
        Obj2_X = -70.0;
        Obj2_Y = 0.0;
        Obj2_Z = 70.0;
        Obj3_X = -80.0;
        Obj3_Y = 0.0;
        Obj3_Z = -80.0;
        Dragonfly_circuit = false;
        Dragonfly_fire = false;
        Dragonfly_wings = true;
        wing_leg = 1;
        Dragonfly_speed = 110;
        Dragonfly_right_wing_angle = 0;
        Dragonfly_left_wing_angle = 0;
        Dragonfly_angle = 0;
        Dragonfly_height = 80;
        Dx = 0, Dy = 0, Dz = 0;
        D_t = 0;
        D_leg = 1;
        Cloud_movement = true;
        Cloud_speed = 0.0625;
        Cx = 0, Cy = 0, Cz = 0;
        Cloud_X = 0.0;
        Cloud_Y = 0.0;
        Cloud_Z = 0.0;       
        break;
    case 'f':
        //Fire Toggle
        Dragonfly_fire = !Dragonfly_fire;
        break;
    default:
        break;
    }    

    glutPostRedisplay();
}

// Special keyboard input processing routine.
void specialKeyInput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (Dragonfly_speed >= 30) {  // Max Allowed
            Dragonfly_speed = Dragonfly_speed -= 10;
            std::cout << "Dragon Speed Increased: " << Dragonfly_speed << std::endl;
        }
        break;
    case GLUT_KEY_LEFT:
        if (Dragonfly_speed <= 300) { // Min Allowed
            Dragonfly_speed = Dragonfly_speed += 10;
            std::cout << "Dragon Speed Decreased:  " << Dragonfly_speed << std::endl;
        }
        break;
    case GLUT_KEY_UP:
        if (Cloud_speed <= 0.3125) {  // Max Allowed
            Cloud_speed = Cloud_speed * 5;
            std::cout << "Cloud Speed Increased: " << Cloud_speed << std::endl;
        }
        break;
    case GLUT_KEY_DOWN:
        if (Cloud_speed >= 0.0001) {  // Min Allowed
            Cloud_speed = Cloud_speed / 5;
            std::cout << "Cloud Speed Decreased:  " << Cloud_speed << std::endl;
        }
    default:
        break;
    }
}

// Instructions
void printInstructions()
{
    std::cout << " * Interactions: " << std::endl;
    std::cout << " * 'd' Dragonfly Flies One Time Around." << std::endl;
    std::cout << " * -'1' - View from North." << std::endl;
    std::cout << " * -'2' - View from South." << std::endl;
    std::cout << " * -'3' - View from East." << std::endl;
    std::cout << " * -'4' - View from West." << std::endl;
    std::cout << " * -'b' - Bird's eye view." << std::endl;
    std::cout << " * -'c' - Dragonfly close - up view." << std::endl;
    std::cout << " * -'h' - Dragonfly head - on close - up view." << std::endl;
    std::cout << " * -'s' - Reset." << std::endl;
    std::cout << " * -'f' - Toggle Fire Breathing." << std::endl;
    std::cout << " * -'Up Arrow' - Increase Cloud Speed." << std::endl;
    std::cout << " * -'Down Arrow' - Decrease Cloud Speed." << std::endl;
    std::cout << " * -'Right Arrow' - Increase Dragonfly Speed." << std::endl;
    std::cout << " * -'Left Arrow' - Decrease Dragonfly Speed." << std::endl;
    std::cout << " * -Left - click on dragonfly to make it breathe fire." << std::endl;
    std::cout << " * -Left - click, hold, & drag any flag post to reposition." << std::endl;
    std::cout << " * -Dragonfly will always fly to Green, then Blue, then Red." << std::endl;
}

// Main routine.
int main(int argc, char** argv)
{
    // Generate random variable from time of day.
    srand(static_cast<unsigned>(time(0)));

    printInstructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Window Size:
    glutInitWindowSize(winSize_X, winSize_Y);
    glutInitWindowPosition(850, 100);

    //Create Window:
    glutCreateWindow("The Dragonfly's Journey");

    //Initialization for Window:
    main_setup();
    glutDisplayFunc(display);
    glutReshapeFunc(main_resize);
    glutMouseFunc(main_MouseControl);
    glutMotionFunc(moving_objects);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    
    //Animation Cloud
    glutIdleFunc(animation_cloud);

    //Animation Circuit
    glutTimerFunc(0, animation_circuit, 1);

    //Animation Wings
    glutTimerFunc(0, animation_wings, 1);

    glutMainLoop();

    return 0;
}