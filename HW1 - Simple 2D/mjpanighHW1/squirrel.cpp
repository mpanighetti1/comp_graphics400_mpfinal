/******************************************
*
* Official Name:  Michael Panighetti
*
* E-mail:  mjpanigh@syr.edu
*
* Assignment:  HW1
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  February 8, 2023
*
* References:  For translate and rotation I used a post on stackoverflow on how to do it.
* No code was copied. (https://stackoverflow.com/questions/48236120/how-to-use-gltranslatef-glscalef-glrotatef-in-opengl)
* Author: Rabbid76
*              Used http://www.rgbtool.com/ for various RGB codes.
*
* Interactions:   When prompted: 'y' to "give the squirrel the acorn"
*                                'n' not to.
*
*                 After answering prompt, 'o' for orthogonal, 'p' for perspective.
*
*******************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

using namespace std;

// Globals.
static float squirrel_PositionX = 37.0;
static float squirrel_PositionY = 37.0;
static float squirrel_PositionZ = -1.0;
const char* textDisplay = "Sad Squirrel :(";

static int isOrtho = 1;
static int acorn_prompt = 0;

// Acorn's position & rotation
static float acorn_PositionX = 30.0;
static float acorn_PositionY = 30.0;
static float acorn_Rotation = 0.0;

// Stroke text function.
void writeStrokeString(void* font, const char* string)
{
    const char* c;
    glLineWidth(1.0);

    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }
}

//Reusable Ellipse Function
void draw_ellipse(float x, float y, float z, float w, float l, float r, GLenum mode)
{
    glPushMatrix();
    glTranslatef(x + 1.0, y + 0.5, z);
    glRotatef(r, 0, 0, 1);
    glTranslatef(-x - 1.0, -y - 0.5, -z);
    
    glBegin(mode);    
    int i;
    for (i = 0; i < 360; i++)
    {
        float radius = i * (PI / 180.0);
        glVertex3f(x + (cos(radius) * w),
            y + (sin(radius) * l), z);
    }
    glEnd();

    glPopMatrix();
}

// Reusable Triangle function
void draw_Triangle(GLenum mode, float(*vertices)[3])
{
    glBegin(mode);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);
    glEnd();
};

// Grass + Sky
void createBackground() {

    // create sky.
    glColor3f(0.495, 0.9405, 0.99); // set color to sku blue http://www.rgbtool.com/
    glBegin(GL_POLYGON);
    glVertex3f(0, 35, -1);
    glVertex3f(100, 35, -1);
    glVertex3f(100, 50, -1);
    glVertex3f(0, 50, -1);
    glEnd();

    // create grass.
    glColor3f(0.1149, 0.6, 0.006); // set color to dark green http://www.rgbtool.com/
    int i;
    for (i = 0; i < 50; i++)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(i, 35.0, -1.0);
        glVertex3f(i + 1, 35.0, -1.0);
        glVertex3f(i + 0.5, 37.0, -1.0);
        glEnd();
    }

    glBegin(GL_POLYGON);
    glVertex3f(0, 35, -1);
    glVertex3f(0, 0, -1);
    glVertex3f(100, 0, -1);
    glVertex3f(100, 35, -1);
    glEnd();

    // outline for grass
    for (i = 0; i < 50; i++)
    {
        glLineWidth(1.0);
        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0); // black
        glVertex3f(i + 0.5, 37.0, -1.0);
        glVertex3f(i + 1, 35.0, -1.0);
        glEnd();
    }

}

//Ellipse for body of squirrel.
void drawBody_squirrel()
{
    glLineWidth(1.0);
    glColor3f(0.39, 0.3518, 0.3081); // grey - http://www.rgbtool.com/
    draw_ellipse(squirrel_PositionX, squirrel_PositionY, squirrel_PositionZ, 2.0, 3.0, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(squirrel_PositionX, squirrel_PositionY, squirrel_PositionZ, 2.0, 3.0, 0, GL_LINE_LOOP);
}

//Ellipse for foot.
void drawFoot_squirrel()
{
    glLineWidth(1.0);
    glColor3f(0.39, 0.3518, 0.3081); // grey - http://www.rgbtool.com/
    draw_ellipse((squirrel_PositionX - 0.5), (squirrel_PositionY - 4), squirrel_PositionZ, 1.5, 0.5, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse((squirrel_PositionX - 0.5), (squirrel_PositionY - 4), squirrel_PositionZ, 1.5, 0.5, 0, GL_LINE_LOOP);
}

//Ellipse for leg.
void drawLeg_squirrel()
{
    glLineWidth(1.0);
    glColor3f(0.39, 0.3518, 0.3081); // grey - http://www.rgbtool.com/
    draw_ellipse((squirrel_PositionX + 0.35), (squirrel_PositionY - 2.5), squirrel_PositionZ, 1.5, 2.0, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse((squirrel_PositionX + 0.35), (squirrel_PositionY - 2.5), squirrel_PositionZ, 1.5, 2.0, 0, GL_LINE_LOOP);

}

// Tail vector arrays
static float tail_vertices[3][3] =
{
    {(squirrel_PositionX + 1.75), (squirrel_PositionY - 2.5), squirrel_PositionZ},
    {(squirrel_PositionX + 2.75), (squirrel_PositionY + 4), squirrel_PositionZ},
    {(squirrel_PositionX + 4.75), (squirrel_PositionY + 1.5), squirrel_PositionZ}, 
};

static float tail_vertices2[3][3] =
{
    {(squirrel_PositionX + 2.75), (squirrel_PositionY + 4), squirrel_PositionZ},
    {(squirrel_PositionX + 6.75), (squirrel_PositionY + 2.5), squirrel_PositionZ},
    {(squirrel_PositionX + 6.75), (squirrel_PositionY - 1), squirrel_PositionZ},
};

// 2 triangles for the tail.
void drawTail_squirrel()
{
    // filled grey
    glLineWidth(1.0);
    glColor3f(0.39, 0.3518, 0.3081); // grey - http://www.rgbtool.com/
    draw_Triangle(GL_POLYGON, tail_vertices);
    draw_Triangle(GL_POLYGON, tail_vertices2);

    // black outline
    glColor3f(0.0, 0.0, 0.0); // black
    draw_Triangle(GL_LINE_LOOP, tail_vertices);
    draw_Triangle(GL_LINE_LOOP, tail_vertices2);
}

// 1 triangle for the head.
void drawHead_squirrel()
{
    // filled grey
    glColor3f(0.39, 0.3518, 0.3081); // grey - http://www.rgbtool.com/
    glBegin(GL_POLYGON);
    glVertex3f((squirrel_PositionX - 3), (squirrel_PositionY + 3), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX + 1.25), (squirrel_PositionY + 3), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX + 1.25), (squirrel_PositionY + 5.5), squirrel_PositionZ);
    glEnd();

    // black outline
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0); // black
    glBegin(GL_LINE_LOOP);
    glVertex3f((squirrel_PositionX - 3), (squirrel_PositionY + 3), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX + 1.25), (squirrel_PositionY + 3), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX + 1.25), (squirrel_PositionY + 5.5), squirrel_PositionZ);
    glEnd();

}

// 2 lines for the arm and hand.
void drawArm_squirrel()
{
    glLineWidth(2.0);

    glBegin(GL_LINES);

    glVertex3f((squirrel_PositionX), (squirrel_PositionY + 1), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX - 4), (squirrel_PositionY), squirrel_PositionZ);

    glVertex3f((squirrel_PositionX - 4), (squirrel_PositionY), squirrel_PositionZ);
    glVertex3f((squirrel_PositionX - 4.5), (squirrel_PositionY + 0.5), squirrel_PositionZ);

    glEnd();

}

// draw an acorn at specified coordinate.
void drawAcorn(int x, int y, int z, float angle)
{
    glLineWidth(1.0);

    // translate and rotate - 
    //ref: stackoverflow.com/questions/48236120/how-to-use-gltranslatef-glscalef-glrotatef-in-opengl
    //author: Rabbid76
    glPushMatrix();
    glTranslatef(x + 1.0, y + 0.5, z);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-x - 1.0, -y - 0.5, -z);

    // bottom of acorn.
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.3062, 0.0275); // brown http://www.rgbtool.com/
    glVertex3f(x, y, z);
    glVertex3f(x + 0.25, y - 1.0, z);
    glVertex3f(x + 1.0, y - 1.5, z);
    glVertex3f(x + 1.75, y - 1, z);
    glVertex3f(x + 2.0, y, z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // black
    glVertex3f(x, y, z);
    glVertex3f(x + 0.25, y - 1.0, z);
    glVertex3f(x + 1.0, y - 1.5, z);
    glVertex3f(x + 1.75, y - 1, z);
    glVertex3f(x + 2.0, y, z);
    glEnd();

    // top of acorn - filled light brown.
    glColor3f(0.69, 0.5181, 0.2415); // light brown http://www.rgbtool.com/
    draw_ellipse((x + 0.96), (y + 0.35), z, 1.1, 0.5, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse((x + 0.96), (y + 0.35), z, 1.1, 0.5, 0, GL_LINE_LOOP);

    //stem of acorn - filled brown.
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.3062, 0.0275); // brown
    glVertex3f(x + 0.80, y + 0.35, z);
    glVertex3f(x + 0.35 + 0.80, y + 0.35, z);
    glVertex3f(x + 0.35 + 0.80, y + 1.0 + 0.35, z);
    glVertex3f(x + 0.80, y + 1.0 + 0.35, z);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0, 0.0, 0.0); // black
    glVertex3f(x + 0.80, y + 0.35, z);
    glVertex3f(x + 0.35 + 0.80, y + 0.35, z);
    glVertex3f(x + 0.35 + 0.80, y + 1.0 + 0.35, z);
    glVertex3f(x + 0.80, y + 1.0 + 0.35, z);
    glEnd();

    glPopMatrix();
}

// Start of drawDog with Cylinder. 
void drawBody_dog()
{
    glLineWidth(2.0);
    glColor3f(0.55, 0.3062, 0.0275); // brown

    int numVertices = 20;
    float angle;

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= numVertices; ++i)
    {
        angle = 2 * PI * i / numVertices;
        glVertex3f(15 + cos(angle) * 5.0, 15 + sin(angle) * 5.0, 0.0);
        glVertex3f(15 + cos(angle) * 5.0, 15 + sin(angle) * 5.0, -2.0);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex3f(13.0, 18.0, -2.0);
        glVertex3f(9.0, 2.0, -2.0);
        glVertex3f(2.0, 4.0, -2.0);
    glEnd();
}

void drawLegs_dog()
{
    glColor3f(0.55, 0.3062, 0.0275); // brown
    draw_ellipse(39.0, 23.0, -2.0, 2, 6, 110, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(39.0, 23.0, -2.0, 2, 6, 110, GL_LINE_LOOP);
    
    glColor3f(0.55, 0.3062, 0.0275); // brown
    draw_ellipse(22.0, 9.0, -2.0, 2, 6, 120, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(22.0, 9.0, -2.0, 2, 6, 120, GL_LINE_LOOP);

    glColor3f(0.55, 0.3062, 0.0275); // brown
    draw_ellipse(17.0, 13.0 , -2.0, 6, 9, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(17.0, 13.0, -2.0, 6, 9, 0, GL_LINE_LOOP);

    glColor3f(0.55, 0.3062, 0.0275); // brown
    draw_ellipse(36.0, 27.0, -2.0, 3, 7, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(36.0, 27.0, -2.0, 3, 7, 0, GL_LINE_LOOP);
}

void drawHead_dog()
{
    //nose of dog - filled brown.
    glBegin(GL_POLYGON);
    glColor3f(0.55, 0.3062, 0.0275); // brown
    glVertex3f(32.0, 45.0, -2.0);
    glVertex3f(36.0, 36.0, -2.0);
    glVertex3f(43.0, 42.0, -2.0);
    glVertex3f(42.0, 45.0, -2.0);
    glEnd();

    // mouth line
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0); // black
    glBegin(GL_LINES);
        glVertex3f(33.0, 35.0, -2.0);
        glVertex3f(42.5, 43.5, -2.0);
    glEnd();
    
    // head
    glColor3f(0.55, 0.3062, 0.0275); // brown
    draw_ellipse(33.0, 40.0, -2.0, 6, 6, 0, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(33.0, 40.0, -2.0, 6, 6, 0, GL_LINE_LOOP);

    // ear
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(34.0, 35.0, -2.0, 3, 5, 0, GL_POLYGON);

    // nose
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(41.5, 44.5, -2.0, 1, 1, 0, GL_POLYGON);
}

void drawBark_Dog()
{
    glColor3f(1.0, 1.0, 1.0); // white
    draw_ellipse(58, 45, -2.0, 8, 16, 90, GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); // black
    draw_ellipse(58, 45, -2.0, 8, 16, 90, GL_LINE_LOOP);

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); // black
    glTranslatef(45.5, 43, -2.0);
    glRotatef(0.0, 0.0, 0.0, -2.0);
    glScalef(0.033, 0.033, 0.033);
    writeStrokeString(GLUT_STROKE_ROMAN, "BARK! BARK!");
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (isOrtho == 2) glFrustum(0, 50, 0, 50, 1, 2);
    else glOrtho(0, 50, 0, 50, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    createBackground();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0); // brown > black
    glTranslatef(5.0, 40.0, -1.0);
    glRotatef(0.0, 0.0, 0.0, -1.0);
    glScalef(0.02, 0.02, 0.02);
    writeStrokeString(GLUT_STROKE_ROMAN, textDisplay);
    glPopMatrix();

    drawBody_squirrel();
    drawLeg_squirrel();
    drawFoot_squirrel();
    drawTail_squirrel();
    drawHead_squirrel();
    drawArm_squirrel();
    drawAcorn(acorn_PositionX, acorn_PositionY, -1.0, acorn_Rotation);

    drawBody_dog();
    drawLegs_dog();
    drawHead_dog();
    drawBark_Dog();

    glFlush();

    if (acorn_prompt == 0) {
        // ask user the following (instructions in description):
        char response;
        cout << "Do you want to give the squirrel the acorn? (y/n):  ";
        cin >> response;

        if (response == 'y')
        {
            // change acorn's position on screen
            acorn_PositionX = squirrel_PositionX - 5.5;
            acorn_PositionY = squirrel_PositionY + 1;
            acorn_Rotation = 30.0;
            textDisplay = "Happy Squirrel :)";
            acorn_prompt = 1;
        }
        else
        {
            // change acorn's position on screen
            acorn_PositionX = 30.0;
            acorn_PositionY = 30.0;
            acorn_Rotation = 0.0;
            textDisplay = "Sad Squirrel :(";
            acorn_prompt = 1;
        }
        glutPostRedisplay();
    }

}

// Initialization routine.
void setup(void)
{
    //white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{

    switch (key)
    {
    case 'o': // assign orthogonal.
        isOrtho = 1;
        glutPostRedisplay();
        cout << "Orthogonal \n";
        break;
    case 'p': // assign perspective.
        isOrtho = 2;
        textDisplay = "Scared Squirrel! D:";
        glutPostRedisplay();
        cout << "Perspective \n";
        break;
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

// Instructions
void printInstructions()
{
    cout << "Instructions:" << endl;
    cout << "After answering the prompt below, click the display window. \n Use 'o' for orthogonal, 'p' for perspective. \n" << endl;
}

// Main routine.
int main(int argc, char** argv)
{
    printInstructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Squirrel");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();

    return 0;
}
