/******************************************
*
* Official Name:  Michael Panighetti
*
* E-mail:  mjpanigh@syr.edu
*
* Assignment:  HW2 - Food App
*
* Environment/Compiler:  Visual Studio Community 2022
*
* Date submitted:  February 27, 2023
*
* References: None this time.
*
* Interactions:   
* 
* Selection Window:   
    •	Sizes Radio Menu – you can select small, medium, or large and this 
        will change the length (radius) of the pizza slices.
    •	# of Slices Radio Menu – (Default is 6) you can select 4 slices, 6 slices, or 8 slices 
        and this will change the number of slices the pizza is cut into (it will change the start_angle 
        and end_angle variables when each slice is drawn.)
    •	Sauces Radio Menu – You can select Ranch, Alfredo, Garlic Parmesan, BBQ, or Marinara. 
        These have key bindings also, R, A, G, B, and M, respectively – indicated by what’s in () 
        beside each option.  Upon having one selected, sauce will appear on the pizza with each having 
        its own color associated with it.
    •	Toppings Checkbox Menu – Any number of toppings can be selected at once. Toppings include 
        Fresh Mozzarella, Fresh Basil, Sausage, Mushrooms, and Pepperoni. These have key bindings also, 
        1, 2, 3, 4, and 5, respectively - indicated by what’s in () beside each option. When one of these 
        toppings is selected, the topping will appear on the pizza.

* Food Plate Window:  
    •	When you left-click on the food plate window – the randomness of the topping placement is 
        regenerate and can be shuffled around until an optimal spreading is achieved. 
    •	When you right-click, a pop-up menu will appear.

* Pop-up Menu:  
    •	The pop-up menu includes the ability to exit the program with the quit option.
    •	It includes an option for slicing or unslicing the pizza. This will spread the slices of the 
        pizza outwards, and the toppings will move with the position of the slices.
    •	There is a sub-menu called “Cup.”
            o	You can remove or put on the lid (depending on what is currently active).
            o	You can change the drink type by selecting Water, Grape Soda, Orange Soda, or Pepsi. 
                This changes the color of the cylinder within the cup that represents the liquid. 
    •	There is a sub-menu called “Rotate.”
            o	Rotate -45 Degrees around the y-axis.
            o	Rotate +45 Degrees around the y-axis.
    •	There is a sub-menu called “Plate.”
            o	Change the color of the plate to Dark Grey, Green-ish-Grey, Blue-ish Grey, Red-ish Grey.
            o	Change the shape of the plate to Rectangle, Square, Circle, Diamond.

*******************************************/

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <array>
#include <vector>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159

using namespace std;

// Globals.
int winSize_X = 700;
int winSize_Y = 700;
static int selection_menu, food_plate;  // Window identifiers.
int radio_selection_sauces = 0;         // Each # Radio Sauces Menu Item (From Bottom)
int radio_selection_slices = 2;         // Each # Radio Slices Menu Item (From Bottom)
int radio_selection_size = 2;           // Each # Radio Size Menu Item (From Bottom)
array<int, 6> checkbox_selections = {}; // Each # Checkbox Menu Item (From Bottom), Starting at 1, not 0.
int sliced = 0;
int lid = 1;
int liquid = 0;
int plate_shape = 8;
int plate_color = 12;
int rotation = 0;

// Move Entire Interface Position
static float interface_anchor_X = 12.0; 
static float interface_anchor_Y = 12.0;
static float interface_anchor_Z = 0.0;

// Change Spacing
static float offset_X = 65.0;           // Space between the radio and check box menu
static float offset_X_size = 68.0;      // Space between Sizes and # of Slices
static float offset_Y = 10.0;           // Space between radio and check box menu items
static float mini_offset_X = 5.0;       // Space between selection shape and label
static float size_menu_offset_Y = 82.0; // Space from bottom, where size_menu is.


static float selectWin_anchors[3][3] =
{
    {interface_anchor_X,  // Radio menu anchor X
     interface_anchor_Y,  // Radio menu anchor Y 
     interface_anchor_Z}, // Radio menu anchor Z

    {(interface_anchor_X + offset_X), // Check box menu anchor X
     interface_anchor_Y,              // Check box menu anchor Y 
     interface_anchor_Z},             // Check box menu anchor Z 

    {(interface_anchor_X),                    // Check box menu anchor X
     interface_anchor_Y + size_menu_offset_Y, // Check box menu anchor Y 
     interface_anchor_Z},                     // Check box menu anchor Z 
};

// Stroke Text Function.
void writeStrokeString(void* font, const char* string, float lineWidth, float size)
{
    const char* c;
    glLineWidth(lineWidth);
    glScalef(size, size, size); // Font Size

    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }
}

//Reusable Square Function
void draw_square(float x, float y, float z, float length, GLenum mode)
{
    glBegin(mode);
    glVertex3f(x         , y         , z);
    glVertex3f(x + length, y         , z);
    glVertex3f(x + length, y + length, z);
    glVertex3f(x         , y + length, z);
    glEnd();
}

//Reusable Ellipse/Circle Function
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

//Reusable Cylinder Function
void drawCylinder(float height, float radius, float x, float y, float z, GLenum mode, GLenum mode2) {

    int numSlices = 32; // Number of slices to approximate the circle
    float step = 2.0 * PI / numSlices;
    float halfHeight = height / 2.0;

    // Draw the top circle
    glBegin(mode); //GL_TRIANGLE_FAN or GL_LINE_LOOP
    glVertex3f(x, y + halfHeight, z);
    for (int i = 0; i <= numSlices; i++) {
        float angle = i * step;
        glVertex3f(x + radius * cos(angle), y + halfHeight, z + radius * sin(angle));
    }
    glEnd();

    // Draw the bottom circle
    glBegin(mode);  //GL_TRIANGLE_FAN or GL_LINE_LOOP
    glVertex3f(x, y - halfHeight, z);
    for (int i = numSlices; i >= 0; i--) {
        float angle = i * step;
        glVertex3f(x + radius * cos(angle), y - halfHeight, z + radius * sin(angle));
    }
    glEnd();

    // Draw the sides
    glBegin(mode2); //GL_TRIANGLE_STRIP or GL_LINES
    for (int i = 0; i <= numSlices; i++) {
        float angle = i * step;
        float x1 = x + radius * cos(angle);
        float y1 = y + halfHeight;
        float z1 = z + radius * sin(angle);
        float x2 = x1;
        float y2 = y - halfHeight;
        float z2 = z1;
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
    }
    glEnd();
}

void selection_instructions()
{
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0); // black

    // Instructions at the top of the selection window
    glPushMatrix();
    glTranslatef(selectWin_anchors[0][0] + mini_offset_X - 9, // X
        (selectWin_anchors[0][1] + (offset_Y * 12) - 2),      // Y + (offset_Y*(position)) - minor adj
        selectWin_anchors[0][2]);                             // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "Welcome to the Pizza Shop!", 2.0, 0.04); // Args: Font, Text, LineWidth, Size
    glPopMatrix();

    // Instructions at the top of the selection window
    glPushMatrix();
    glTranslatef(selectWin_anchors[0][0] + mini_offset_X - 9, // X
        (selectWin_anchors[0][1] + (offset_Y * 11) - 2),      // Y + (offset_Y*(position)) - minor adj
        selectWin_anchors[0][2]);                             // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "Keybinds are shown in () besides menu items.", 1.5, 0.04); // Args: Font, Text, LineWidth, Size
    glPopMatrix();

    // Deco Rectangle
    glBegin(GL_LINE_LOOP);
    glVertex3f(interface_anchor_X - 8, interface_anchor_Y - 8, interface_anchor_Z);
    glVertex3f(interface_anchor_X + 124, interface_anchor_Y - 8, interface_anchor_Z);
    glVertex3f(interface_anchor_X + 124, interface_anchor_Y + 126, interface_anchor_Z);
    glVertex3f(interface_anchor_X - 8, interface_anchor_Y + 126, interface_anchor_Z);
    glEnd();
}

void size_menu()
{
    // Draw circles for each menu item:
    float offset = 0;
    for (int i = 0; i < 3; i++) {
        glLineWidth(1.0);
        glColor3f(0.0, 0.0, 0.0); // black
        draw_ellipse(selectWin_anchors[2][0],  // X
            selectWin_anchors[2][1] - offset,  // Y
            selectWin_anchors[2][2],           // Z
            3.0,                               // Width
            3.0,                               // Height
            0.0,                               // Rotation
            GL_LINE_LOOP);                     // Mode
        offset += offset_Y;
    }
    offset = 0; // set offset back to zero for discs

    auto create_label = [](const char* text, int position, float offset) {        
        position = position - 1;
        glPushMatrix();
        glTranslatef(selectWin_anchors[2][0] + mini_offset_X + offset, // X
            selectWin_anchors[2][1] - (offset_Y* position) - 2,        // Y + (offset_Y*(position)) - minor adj
            selectWin_anchors[2][2]);                                  // Z
        writeStrokeString(GLUT_STROKE_ROMAN, text, 1.0, 0.035);        // Args: Font, Text, LineWidth, Size
        glPopMatrix();
    };
    offset = 0; // set offset back to zero for discs

    // create_label(text, position //from bottom up);
    create_label("Small 10\"", 1, 0);
    create_label("Medium 12\"", 2, 0);
    create_label("Large 14\"", 3, 0);

    // Title of menu - Bold - Larger
    glPushMatrix();
    glTranslatef(selectWin_anchors[0][0] + mini_offset_X - 7,  // X
        (selectWin_anchors[0][1] + (offset_Y * 9.2) - 2),      // Y + (offset_Y*(position)) - minor adj
        selectWin_anchors[0][2]);                              // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "Sizes:", 2.0, 0.04); // Args: Font, Text, LineWidth, Size
    glPopMatrix();

    // Draw circles for each menu item:
    for (int i = 0; i < 3; i++) {
        glLineWidth(1.0);
        glColor3f(0.0, 0.0, 0.0); // black
        draw_ellipse(selectWin_anchors[2][0] + offset_X_size,  // X
            selectWin_anchors[2][1] - offset,  // Y
            selectWin_anchors[2][2],           // Z
            3.0,                               // Width
            3.0,                               // Height
            0.0,                               // Rotation
            GL_LINE_LOOP);                     // Mode
        offset += offset_Y;
    }
    offset = 0; // set offset back to zero for discs

    // create_label(text, position //from bottom up);
    create_label("4 Slices", 1, offset_X_size);
    create_label("6 Slices", 2, offset_X_size);
    create_label("8 Slices", 3, offset_X_size);

    // Title of Menu - Bold - Larger
    glPushMatrix();
    glTranslatef(selectWin_anchors[1][0] + mini_offset_X - 5, // X + minor adj
        (selectWin_anchors[1][1] + (offset_Y * 9.2) - 2),     // Y + (offset_Y*(position)) - minor offset
        selectWin_anchors[1][2]);                             // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "# of Slices:", 2.0, 0.04); // Args: Font, Text, LineWidth, Scale
    glPopMatrix();

    // Selection Disc - Slices 
    if (radio_selection_slices != 0) {
        glColor3f(0.1008, 0.3654, 0.63);       // Dark Blue
        draw_ellipse(selectWin_anchors[2][0] + offset_X_size,  // X
            selectWin_anchors[2][1] - offset - (offset_Y * (radio_selection_slices - 1)),  // Y
            selectWin_anchors[2][2],           // Z
            2.4,                               // Width
            2.4,                               // Height
            0.0,                               // Rotation
            GL_POLYGON);                       // Mode
    }
    offset = 0; // set offset back to zero for discs

    // Selection Disc - Sizes
    if (radio_selection_size != 0) {
        glColor3f(0.1008, 0.3654, 0.63);       // Dark Blue
        draw_ellipse(selectWin_anchors[2][0],  // X
            selectWin_anchors[2][1] - offset - (offset_Y * (radio_selection_size - 1)),  // Y
            selectWin_anchors[2][2],           // Z
            2.4,                               // Width
            2.4,                               // Height
            0.0,                               // Rotation
            GL_POLYGON);                       // Mode
    }
}

void radio_menu()
{      
    // Draw circles for each menu item:
    float offset = 0;
    for (int i = 0; i < 5; i++) {
        glLineWidth(1.0);
        glColor3f(0.0, 0.0, 0.0); // black
        draw_ellipse(selectWin_anchors[0][0],  // X
            selectWin_anchors[0][1] + offset,  // Y
            selectWin_anchors[0][2],           // Z
            3.0,                               // Width
            3.0,                               // Height
            0.0,                               // Rotation
            GL_LINE_LOOP);                     // Mode
        offset += offset_Y;
    }
    offset = 0; // set offset back to zero for discs

    auto create_label = [](const char* text, int position) {
        position = position - 1;
        glPushMatrix();
        glTranslatef(selectWin_anchors[0][0] + mini_offset_X,       // X
            (selectWin_anchors[0][1] + (offset_Y * position) - 2),  // Y + (offset_Y*(position)) - minor adj
            selectWin_anchors[0][2]);                               // Z
        writeStrokeString(GLUT_STROKE_ROMAN, text, 1.0, 0.035);     // Args: Font, Text, LineWidth, Size
        glPopMatrix();
    };

    // create_label(text, position //from bottom up);
    create_label("Marinara (M)", 1);
    create_label("BBQ (B)", 2);
    create_label("Garlic Parmesan (G)", 3);
    create_label("Alfredo (A)", 4);
    create_label("Ranch (R)", 5);

    // Title of menu - Bold - Larger
    glPushMatrix();
    glTranslatef(selectWin_anchors[0][0] + mini_offset_X - 7, // X
        (selectWin_anchors[0][1] + (offset_Y * 5) - 2),       // Y + (offset_Y*(position)) - minor adj
        selectWin_anchors[0][2]);                             // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "Sauces:", 2.0, 0.04); // Args: Font, Text, LineWidth, Size
    glPopMatrix();

    // Selection Disc - offset will depend on user selection.
    if (radio_selection_sauces != 0) {
        glColor3f(0.1008, 0.3654, 0.63);       // Dark Blue
        draw_ellipse(selectWin_anchors[0][0],  // X
            // Uses the radio_selection 'setting' to offset disc into the correct menu item.
            selectWin_anchors[0][1] + (offset + (offset_Y * (radio_selection_sauces - 1))),
            selectWin_anchors[0][2],           // Z
            2.4,                               // Width
            2.4,                               // Height
            0.0,                               // Rotation
            GL_POLYGON);                       // Mode
    }
}

void checkBox_menu()
{
    // Draw squares for each menu item:
    float offset = 0;
    for (int i = 0; i < 5; i++) {
        glLineWidth(1.0);
        glColor3f(0.0, 0.0, 0.0); // black
        draw_square(selectWin_anchors[1][0],      // X
            selectWin_anchors[1][1] + offset - 3, // Y + offset - minor adj.
            selectWin_anchors[1][2],              // Z
            5.5,                                  // Length of Sq
            GL_LINE_LOOP);                        // Mode
        offset += offset_Y;
    }
    offset = 0; // set offset back to zero for selections

    auto create_label = [](const char* text, int position) {
        position = position - 1;
        glPushMatrix();
        glTranslatef(selectWin_anchors[1][0] + mini_offset_X + 3,  // X + minor adj
            (selectWin_anchors[1][1] + (offset_Y * position) - 2), // Y + (offset_Y*(position)) - minor offset
            selectWin_anchors[1][2]);                              // Z
        writeStrokeString(GLUT_STROKE_ROMAN, text, 1.0, 0.035);    // Args: Font, Text, LineWidth, Size
        glPopMatrix();
    };

    // create_label(text, position //from bottom up);
    create_label("Pepperoni (5)", 1);
    create_label("Mushrooms (4)", 2);
    create_label("Sausage (3)", 3);
    create_label("Fresh Basil (2)", 4);
    create_label("Fresh Mozzarella (1)", 5);
   
    // Title of Menu - Bold - Larger
    glPushMatrix();
    glTranslatef(selectWin_anchors[1][0] + mini_offset_X - 5, // X + minor adj
        (selectWin_anchors[1][1] + (offset_Y * 5) - 2),       // Y + (offset_Y*(position)) - minor offset
        selectWin_anchors[1][2]);                             // Z
    writeStrokeString(GLUT_STROKE_ROMAN, "Toppings:", 2.0, 0.04); // Args: Font, Text, LineWidth, Scale
    glPopMatrix();

    // Selection Box - offset will depend on user selection.
    for (int i = 1; i < 6; i++) {          
        if (checkbox_selections[i] == i) {
            draw_square(selectWin_anchors[1][0] + 0.45, // X
                // Y + offset + (offset_Y * (position of selection item - 1))- minor adj.
                selectWin_anchors[1][1] + offset + (offset_Y * (i - 1)) - 2.5, 
                selectWin_anchors[1][2],                // Z
                4.5,                                    // Length of Sq
                GL_POLYGON);                            // Mode
        }              
    }
}

// Selection Menu Initialization -----> STARTS HERE

// Drawing routine.
void SelectionMenu_drawScene(void)
{
    glutSetWindow(selection_menu); //Choose Window

    glClear(GL_COLOR_BUFFER_BIT);

    selection_instructions();
    size_menu();
    radio_menu();
    checkBox_menu();

    glFlush();

}

// Initialization routine.
void SelectionMenu_setup(void)
{
    //white background
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void SelectionMenu_resize(int w, int h)
{
    winSize_X = w;
    winSize_Y = h;

    float aspect = (float)w / (float)h;

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (aspect >= 1.0) {
        // The window is wider than it is tall
        float aspectRatio = (float)w / (float)h;
        glOrtho(0, 140 * aspectRatio, 0, 140, -1.0, 1.0);
    }
    else {
        // The window is taller than it is wide
        float aspectRatio = (float)h / (float)w;
        glOrtho(0, 140, 0, 140 * aspectRatio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SelectionMenu_MouseControl(int button, int state, int x, int y)
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

        // Radio menu Sauces
        if (xWorld >= (interface_anchor_X - 6) && 
            xWorld <= (interface_anchor_X - 2) && 
            yWorld >= (interface_anchor_Y - 6) && 
            yWorld <= (interface_anchor_Y - 2))
            radio_selection_sauces = 1; //Marinara
        else if (xWorld >= (interface_anchor_X - 6) &&
                 xWorld <= (interface_anchor_X - 2) &&
                 yWorld >= (interface_anchor_Y + 1) &&
                 yWorld <= (interface_anchor_Y + 5))
            radio_selection_sauces = 2; //BBQ
        else if (xWorld >= (interface_anchor_X - 6) &&
                 xWorld <= (interface_anchor_X - 2) &&
                 yWorld >= (interface_anchor_Y + 8) &&
                 yWorld <= (interface_anchor_Y + 12))
            radio_selection_sauces = 3; //Garlic Parmesan
        else if (xWorld >= (interface_anchor_X - 6) &&
                 xWorld <= (interface_anchor_X - 2) &&
                 yWorld >= (interface_anchor_Y + 15) &&
                 yWorld <= (interface_anchor_Y + 19))
            radio_selection_sauces = 4; //Alfredo
        else if (xWorld >= (interface_anchor_X - 6) &&
                 xWorld <= (interface_anchor_X - 2) &&
                 yWorld >= (interface_anchor_Y + 22) &&
                 yWorld <= (interface_anchor_Y + 26))
            radio_selection_sauces = 5; //Ranch

        // Radio menu - Size
        if (xWorld >= (interface_anchor_X - 6) &&
            xWorld <= (interface_anchor_X - 2) &&
            yWorld >= (interface_anchor_Y + 53) &&
            yWorld <= (interface_anchor_Y + 57))
            radio_selection_size = 1; //Large
        else if (xWorld >= (interface_anchor_X - 6) &&
            xWorld <= (interface_anchor_X - 2) &&
            yWorld >= (interface_anchor_Y + 46) &&
            yWorld <= (interface_anchor_Y + 50))
            radio_selection_size = 2; //Medium
        else if (xWorld >= (interface_anchor_X - 6) &&
            xWorld <= (interface_anchor_X - 2) &&
            yWorld >= (interface_anchor_Y + 39) &&
            yWorld <= (interface_anchor_Y + 43))
            radio_selection_size = 3; //Large

        auto check_uncheck = [](int which) {
            if (checkbox_selections[which] == 0) // if unchecked, check
                checkbox_selections[which] = which;
            else // if checked, uncheck
                checkbox_selections[which] = 0;
        };

        // Checkbox menu selection mouse controls
        if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y - 6) &&
            yWorld <= (interface_anchor_Y - 2))
            check_uncheck(1); //Pepperoni
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 1) &&
            yWorld <= (interface_anchor_Y + 5))
            check_uncheck(2); //Mushroom
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 8) &&
            yWorld <= (interface_anchor_Y + 12))
            check_uncheck(3); //Sausage
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 15) &&
            yWorld <= (interface_anchor_Y + 19))
            check_uncheck(4); //Fresh Basil
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 22) &&
            yWorld <= (interface_anchor_Y + 26))
            check_uncheck(5); //Fresh Mozzarella

        // Radio menu - Slices
        if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 53) &&
            yWorld <= (interface_anchor_Y + 57))
            radio_selection_slices = 1;
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 46) &&
            yWorld <= (interface_anchor_Y + 50))
            radio_selection_slices = 2;
        else if (xWorld >= (interface_anchor_X + offset_X - 22) &&
            xWorld <= (interface_anchor_X + offset_X - 19) &&
            yWorld >= (interface_anchor_Y + 39) &&
            yWorld <= (interface_anchor_Y + 43))
            radio_selection_slices = 3;

        glutSetWindow(selection_menu);
        glutPostRedisplay();
        glutSetWindow(food_plate);
        glutPostRedisplay();
    }
}

// Selection Menu Initialization -----> ENDS HERE

void drawTopBot_Helper(float center_x, float center_y, float center_z, float start_angle, float end_angle, float radius, GLenum mode) {
    glBegin(mode);
    glVertex3f(center_x, center_y, center_z);
    for (GLfloat angle = start_angle; angle <= end_angle; angle += 1.0f) {
        GLfloat x = center_x + radius * cos(angle * PI / 180.0);
        GLfloat z = center_z + radius * sin(angle * PI / 180.0);
        glVertex3f(x, center_y, z);
    }
    glEnd();
}

void drawMushroom(float center_x, float center_y, float center_z, float rotation) {
    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3f(center_x - 1, center_y, center_z);
    glVertex3f(center_x - 1, center_y, center_z + 6);
    glVertex3f(center_x + 3, center_y, center_z + 6);
    glVertex3f(center_x + 1, center_y, center_z + 8);
    glVertex3f(center_x + 4, center_y, center_z + 7);
    glVertex3f(center_x + 5, center_y, center_z + 3);
    glVertex3f(center_x + 4, center_y, center_z - 1);
    glVertex3f(center_x + 1, center_y, center_z - 2);
    glVertex3f(center_x + 3, center_y, center_z + 0);
    glEnd();
    glPopMatrix();
}

void drawBasil (float center_x, float center_y, float center_z, float rotation) {
    glPushMatrix();
    glRotatef(rotation, 0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex3f(center_x + 1, center_y, center_z + 4);
    glVertex3f(center_x + 1, center_y, center_z + 8);
    glVertex3f(center_x + 2, center_y, center_z + 8);
    glVertex3f(center_x + 3, center_y, center_z + 4);
    glVertex3f(center_x + 2, center_y, center_z + 0);
    glVertex3f(center_x + 3, center_y, center_z - 4);
    glVertex3f(center_x + 2, center_y, center_z - 4);
    glEnd();
    glPopMatrix();
};

void drawSlice(float center_x, float center_y, float center_z, 
    float start_angle, float end_angle, 
    float offset_x_toppings, float offset_z_toppings, float radius) {
    
    glLineWidth(2.0);

    //Draw Bot
    glColor3f(0.0, 0.0, 0.0); //Black Outline
    drawTopBot_Helper(center_x, center_y, center_z, start_angle, end_angle, radius, GL_LINE_LOOP);

    //Draw Top
    glColor3f(0.0, 0.0, 0.0); //Black Oultine
    drawTopBot_Helper(center_x, center_y + 10, center_z, start_angle, end_angle, radius, GL_LINE_LOOP);

    glColor3f(0.73, 0.499, 0.1971); //Pizza Dough Color
    drawTopBot_Helper(center_x, center_y + 10, center_z, start_angle, end_angle, radius, GL_POLYGON);

    // For Pepperoni & Mozzeralla
    auto draw_rand_cirles = [](int num, float height, float width, float radius,
        float center_x, float center_y, float center_z, 
        float start_angle, float end_angle,
        float offset_x_toppings, float offset_z_toppings) {

        for (int i = 0; i < num; i++) {
            float rand_radius = 0;

            if (radio_selection_slices == 3) { // 8 Slices - Toppings
                if (offset_x_toppings != 0) {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 16 - 7) + 7;} 
                else {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 9);}} // Sauces
            else if (radio_selection_slices == 2) { // 6 Slices                
                if (offset_x_toppings != 0) {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 22) + 7;}
                else {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 9);}} // Sauces
            else if (radio_selection_slices == 1) { // 4 Slices - Toppings                
                if (offset_x_toppings != 0) {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 14 - 7) + 7;}
                else {rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 9);}} // Sauces

            float rand_angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (end_angle - start_angle) + start_angle;
            long rand_x = (center_x + offset_x_toppings) + rand_radius * cos(rand_angle * PI / 180.0);
            long rand_z = (center_z + offset_z_toppings) + rand_radius * sin(rand_angle * PI / 180.0);
            drawCylinder(height, width, rand_x, center_y + 10.1 , rand_z, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
        }
    };

    //Pepperoni
    if (checkbox_selections[1] == 1) {
        glColor3f(0.58, 0.1353, 0.0); //Pepperoni Color
        draw_rand_cirles(15, 0.2, 5, radius, center_x, center_y + 0.1, center_z, 
            start_angle, end_angle, offset_x_toppings, offset_z_toppings);
    }

    //Fresh Mozzeralla
    if (checkbox_selections[5] == 5) {
        glColor3f(1, 1, 1); //Mozzeralla Color
        draw_rand_cirles(3, 0.2, 7, radius, center_x, center_y + 0.7, center_z, 
            start_angle, end_angle, offset_x_toppings, offset_z_toppings);
    }

    //Sauce
    if (radio_selection_sauces != 0) {
        if (radio_selection_sauces == 1)
            glColor3f(0.77, 0.1412, 0);      //Marinara Color
        else if (radio_selection_sauces == 2)
            glColor3f(0.22, 0.0615, 0.0132); //BBQ Color         
        else if (radio_selection_sauces == 3)
            glColor3f(1, 0.9213, 0.41);      //Garlic Parm Color
        else if (radio_selection_sauces == 4)
            glColor3f(1, 0.976, 0.82);       //Alfredo Color            
        else if (radio_selection_sauces == 5)
            glColor3f(1, 1, 1);              //Ranch Color 

        draw_rand_cirles(3000, 0.2, 2, radius, center_x, center_y, center_z,
            start_angle, end_angle, 0, 0);
    }

    //Mushroom
    if (checkbox_selections[2] == 2) {        
        for (int i = 0; i < 15; i++) {
            glColor3f(0.55, 0.55, 0.55); //Mushroom Color
            float rand_radius = 0;
            if (radio_selection_slices == 3) { // 8 Slices - Toppings
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 16 - 7) + 7;
            }
            else if (radio_selection_slices == 2) { // 6 Slices                
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 22) + 7;
            }
            else if (radio_selection_slices == 1) { // 4 Slices - Toppings                
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 14 - 7) + 7;
            }

            float rand_angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (end_angle - start_angle) + start_angle;
            long rand_x = (center_x + offset_x_toppings) + rand_radius * cos(rand_angle * PI / 180.0);
            long rand_z = (center_z + offset_z_toppings) + rand_radius * sin(rand_angle * PI / 180.0);
            long rand_r = rand() % 361;
            drawMushroom(rand_x, center_y + 10.4, rand_z, rand_r);
        }
    }

    //Sausage
    if (checkbox_selections[3] == 3) {        
        for (int i = 0; i < 15; i++) {
            glColor3f(0.36, 0.2639, 0.0396); //Sausage Color
            float rand_radius = 0;
            if (radio_selection_slices == 3) { // 8 Slices - Toppings
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 16 - 7) + 7;
            }
            else if (radio_selection_slices == 2) { // 6 Slices                
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 22) + 7;
            }
            else if (radio_selection_slices == 1) { // 4 Slices - Toppings                
                rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 14 - 7) + 7;
            }

            float rand_angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (end_angle - start_angle) + start_angle;
            long rand_x = (center_x + offset_x_toppings) + rand_radius * cos(rand_angle * PI / 180.0);
            long rand_z = (center_z + offset_z_toppings) + rand_radius * sin(rand_angle * PI / 180.0);
            long rand_r = rand() % 361;
            drawMushroom(rand_x, center_y + 10.5, rand_z, rand_r); //Mushroom shape works good for sausage too.
        }
    }

    
    //Fresh Basil
    if (checkbox_selections[4] == 4) {
        for (int i = 0; i < 20; i++) {
            glColor3f(0.1357, 0.36, 0.0396); //Basil Color                
            float rand_radius = 0;
                if (radio_selection_slices == 3) { // 8 Slices - Toppings
                    rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 16 - 7) + 7;
                }
                else if (radio_selection_slices == 2) { // 6 Slices                
                    rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 22) + 7;
                }
                else if (radio_selection_slices == 1) { // 4 Slices - Toppings                
                    rand_radius = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (radius - 14 - 7) + 7;
                }

                float rand_angle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (end_angle - start_angle) + start_angle;
                long rand_x = (center_x + offset_x_toppings) + rand_radius * cos(rand_angle * PI / 180.0);
                long rand_z = (center_z + offset_z_toppings) + rand_radius * sin(rand_angle * PI / 180.0);
                long rand_r = rand() % 361;
                drawBasil(rand_x, center_y + 10.6, rand_z, rand_r);
         }
    }

    //Draw Sides
    glLineWidth(1.0);
    glColor3f(0.0, 0.0, 0.0); //Black
    // Lines on the back of the crust segment
    glBegin(GL_LINES);
    for (GLfloat angle = start_angle; angle <= end_angle; angle += 5.0) {
        GLfloat x = center_x + radius * cos(angle * PI / 180.0);
        GLfloat z = center_z + radius * sin(angle * PI / 180.0);
        glVertex3f(x, 0.0, z);
        glVertex3f(x, 10.0, z);
    }
    glEnd();

    // Triangle pattern for sides
    auto create_side = [](float center_x, float center_y, float center_z, float angle, float radius) {
        int step = 10;
        glBegin(GL_LINES);
        for (float i = 0; i < radius; i += step) {
            glVertex3f(center_x + (i)*cos(angle * PI / 180.0), center_y + 10.0, center_z + (i)*sin(angle * PI / 180.0));
            glVertex3f(center_x + (i + 5) * cos(angle * PI / 180.0), center_y, center_z + (i + 5) * sin(angle * PI / 180.0));
            glVertex3f(center_x + (i + 5) * cos(angle * PI / 180.0), center_y, center_z + (i + 5) * sin(angle * PI / 180.0));
            glVertex3f(center_x + (i + 10) * cos(angle * PI / 180.0), center_y + 10, center_z + (i + 10) * sin(angle * PI / 180.0));
        }
        glEnd();
    };

    create_side(center_x, center_y, center_z, start_angle, radius); //Left
    create_side(center_x, center_y, center_z, end_angle, radius); //Right
}

void foodScene() {

    // Tray/Mat
    if (plate_color == 12) {
        glColor3f(0.63, 0.5836, 0.5229);} // Dark Grey
    if (plate_color == 13) {
        glColor3f(0.53, 0.63, 0.5229);}   // Green-ish Grey
    if (plate_color == 14) {
        glColor3f(0.5229, 0.5461, 0.63);} // Blue-ish Grey
    if (plate_color == 15) {
        glColor3f(0.63, 0.5229, 0.5229);} // Red-ish Grey
    
    
    if (plate_shape == 8) { // Retangle
        glBegin(GL_POLYGON);
        glVertex3f(-80, -0.1, -140);
        glVertex3f(-80, -0.1, 140);
        glVertex3f(70, -0.1, 140);
        glVertex3f(70, -0.1, -140);
        glEnd();

        //Outline Effect
        glLineWidth(3.0);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-80, -0.1, -140);
        glVertex3f(-80, -0.1, 140);
        glVertex3f(70, -0.1, 140);
        glVertex3f(70, -0.1, -140);
        glEnd();
    }    
    if (plate_shape == 9) { // Square
        glBegin(GL_POLYGON);
        glVertex3f(-80, -0.1, -80);
        glVertex3f(-80, -0.1, 80);
        glVertex3f(80, -0.1, 80);
        glVertex3f(80, -0.1, -80);
        glEnd();

        //Outline Effect
        glLineWidth(3.0);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-80, -0.1, -80);
        glVertex3f(-80, -0.1, 80);
        glVertex3f(80, -0.1, 80);
        glVertex3f(80, -0.1, -80);
        glEnd();
    }
    if (plate_shape == 10) { // Circle
        drawCylinder(0.1, 100, 0, -0.1, 0, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);

        //Outline Effect
        glLineWidth(3.0);
        glColor3f(0, 0, 0);
        drawCylinder(0.1, 100, 0, -0.1, 0, GL_LINE_LOOP, GL_LINES);
    }
    if (plate_shape == 11) { // Diamond
        glBegin(GL_POLYGON);
        glVertex3f(0, -0.1, -140);
        glVertex3f(-100, -0.1, 0);
        glVertex3f(0, -0.1, 140);
        glVertex3f(100, -0.1, 0);
        glEnd();

        //Outline Effect
        glLineWidth(3.0);
        glColor3f(0, 0, 0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(0, -0.1, -140);
        glVertex3f(-100, -0.1, 0);
        glVertex3f(0, -0.1, 140);
        glVertex3f(100, -0.1, 0);
        glEnd();
    }

    // Cup
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0); //Black
    drawCylinder(40, 15, 100, 10, 100, GL_LINE_LOOP, GL_LINES);

    //Liquid
    if (liquid != 1) {
        if (liquid == 2)
            glColor3f(0.5642, 0.037, 0.74); //Grape Color (2)
        else if (liquid == 3)
            glColor3f(1, 0.4633, 0.08); //Orange Color (3)
        else
            glColor3f(0.3, 0.2, 0.0); //Pepsi Color (4)

    drawCylinder(30, 14.9, 100, 10, 100, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
    }

    //Straw
    glColor3f(1, 0.32, 0.7393); //Pink Color
    drawCylinder(30, 2, 100, 20, 100, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);

    glPushMatrix();
    glRotatef(70, 100, 50, 100);
    drawCylinder(15, 2, 88, 50, 108, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
    glPopMatrix();

    //Lid
    if (lid == 1) {
        glColor3f(1.0, 1.0, 1.0); //White
        drawCylinder(1.5, 16.5, 100, 30, 100, GL_TRIANGLE_FAN, GL_TRIANGLE_STRIP);
        glColor3f(0.0, 0.0, 0.0); //Black
        drawCylinder(1.5, 16.5, 100, 30, 100, GL_LINE_LOOP, GL_LINES);
    }
}

// Food Plate Initialization -----> STARTS HERE

// Food Plate Drawing routine.
void FoodPlate_drawScene(void)
{
    glPushMatrix();
    glRotatef(rotation, 0.0, 1.0, 0.0);

    glutSetWindow(food_plate); //Choose Window

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    foodScene();

    float size;
    if (radio_selection_size == 1)
        size = 40;  // 10" (Small)
    else if (radio_selection_size == 3)
        size = 80;  // 14" (Large)
    else
        size = 60;  // 12" (Default - Medium)

    if (radio_selection_slices == 1) {// 4 Slices
        if (sliced == 1) {
            drawSlice(5, 0, 5, 0, 90, 2.5, 2.5, size);
            drawSlice(-5, 0, 5, 90, 180, -2.5, 2.5, size);
            drawSlice(-5, 0, -5, 180, 270, -2.5, -2.5, size);
            drawSlice(5, 0, -5, 270, 360, 2.5, -2.5, size);
        }
        else {
            drawSlice(0, 0, 0, 0, 90, 5, 5, size);
            drawSlice(0, 0, 0, 90, 180, -5, 5, size);
            drawSlice(0, 0, 0, 180, 270, -5, -5, size);
            drawSlice(0, 0, 0, 270, 360, 5, -5, size);
        }
    }
    else if (radio_selection_slices == 3) { // 8 Slices
        if (sliced == 1) {
            drawSlice(10, 0, 5, 0, 45, 9, 4.5, size);
            drawSlice(5, 0, 10, 45, 90, 4.5, 9, size);
            drawSlice(-5, 0, 10, 90, 135, -4.5, 9, size);
            drawSlice(-10, 0, 5, 135, 180, -9, 4.5, size);
            drawSlice(-10, 0, -5, 180, 225, -9, -4.5, size);
            drawSlice(-5, 0, -10, 225, 270, -4.5, -9, size);
            drawSlice(5, 0, -10, 270, 315, 4.5, -9, size);
            drawSlice(10, 0, -5, 315, 360, 9, -4.5, size);
        }
        else {
            drawSlice(0, 0, 0, 0, 45, 9, 4.5, size);
            drawSlice(0, 0, 0, 45, 90, 4.5, 9, size);
            drawSlice(0, 0, 0, 90, 135, -4.5, 9, size);
            drawSlice(0, 0, 0, 135, 180, -9, 4.5, size);
            drawSlice(0, 0, 0, 180, 225, -9, -4.5, size);
            drawSlice(0, 0, 0, 225, 270, -4.5, -9, size);
            drawSlice(0, 0, 0, 270, 315, 4.5, -9, size);
            drawSlice(0, 0, 0, 315, 360, 9, -4.5, size);
        }
    }
    else { // 6 Slices (Default)
        if (sliced == 1) {
            drawSlice(10, 0, 5, 0, 60, 8, 4, size);
            drawSlice(0, 0, 10, 60, 120, 0, 8, size);
            drawSlice(-10, 0, 5, 120, 180, -8, 4, size);
            drawSlice(-10, 0, -5, 180, 240, -8, -4, size);
            drawSlice(0, 0, -10, 240, 300, 0, -8, size);
            drawSlice(10, 0, -5, 300, 360, 8, -4, size);
        }
        else {
            drawSlice(0, 0, 0, 0, 60, 8, 4, size);
            drawSlice(0, 0, 0, 60, 120, 0, 8, size);
            drawSlice(0, 0, 0, 120, 180, -8, 4, size);
            drawSlice(0, 0, 0, 180, 240, -8, -4, size);
            drawSlice(0, 0, 0, 240, 300, 0, -8, size);
            drawSlice(0, 0, 0, 300, 360, 8, -4, size);
        }
    }    
    glPopMatrix();
    glFlush();
}

// Initialization routine.
void FoodPlate_setup(void)
{
    //white background
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glEnable(GL_DEPTH_TEST); // Enable depth testing.
    glDepthFunc(GL_LESS); // Set the depth function.
}

// OpenGL window reshape routine for FoodPlate.
void FoodPlate_resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);   

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / (float)h;
    gluPerspective(90.0, aspect, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Across Cup
    // Set the camera position and orientation
    // gluLookAt(0.0, 51.0, 100.0,  // eye position
    //    100.0, 50.0, 100.0,    // look-at position
    //    1.0, 0.0, 0.0);   // up direction

    // Above Cup
    // Set the camera position and orientation
    // gluLookAt(100.0, 150.0, 100.0,  // eye position
    //    100.0, 50.0, 100.0,    // look-at position
    //   1.0, 0.0, 0.0);   // up direction

    // Normal View
    // Set the camera position and orientation
        gluLookAt(-60.0, 150.0, 0.0,  // eye position
        0.0, 0.0, 0.0,    // look-at position
        1.0, 0.0, 0.0);   // up direction

}

void FoodPlate_MouseControl(int button, int state, int x, int y)
{
    int xWorld, yWorld;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        xWorld = x / 7;
        yWorld = (700 - y) / 7;
        cout << x << "  " << y << endl;
        cout << xWorld << "  " << yWorld << endl << endl;

        glutPostRedisplay();
    }
}

// The top menu callback function.
void main_menu(int id)
{
    if (id == 1) exit(0);

    if (id == 2) 
    {
        if (sliced == 0) sliced = 1;
        else sliced = 0;
    }    

    glutPostRedisplay();
}

// The cup sub-menu callback function.
void cup(int id)
{
    if (id == 3) // Remove/Put On Lid
    {
        if (lid == 1) lid = 0;            
        else lid = 1;
            
    }
    if (id == 4) liquid = 1; // Water
    if (id == 5) liquid = 2; // Grape Soda
    if (id == 6) liquid = 3; // Orange Soda
    if (id == 7) liquid = 4; // Pepsi

    glutPostRedisplay();
}

// The Plate sub-menu callback function.
void plate(int id)
{
}

// The plateShape sub-menu callback function.
void plateShape(int id)
{
    if (id == 8)  plate_shape = 8;  // Rectangle
    if (id == 9)  plate_shape = 9;  // Square
    if (id == 10) plate_shape = 10; // Circle
    if (id == 11) plate_shape = 11; // Diamond
 
    glutPostRedisplay();
}

// The plateColor sub-menu callback function.
void plateColor(int id)
{
    if (id == 12) plate_color = 12; // Dark Grey
    if (id == 13) plate_color = 13; // Green-ish Grey
    if (id == 14) plate_color = 14; // Blue-ish Grey
    if (id == 15) plate_color = 15; // Red-ish Grey

    glutPostRedisplay();
}

// The rotate sub-menu callback function.
void rotate(int id)
{
    
    if (id == 16) rotation -= 45;
    if (id == 17) rotation += 45;

    glutPostRedisplay();
}

// Right click menu
void right_clickMenu()
{   
    int rotate_menu;
    rotate_menu = glutCreateMenu(rotate);
    glutAddMenuEntry("Rotate -45 Degrees", 16);
    glutAddMenuEntry("Rotate +45 Degrees", 17);

    int plateColor_menu;
    plateColor_menu = glutCreateMenu(plateColor);
    glutAddMenuEntry("Dark Grey (Default)", 12);
    glutAddMenuEntry("Green-ish Grey", 13);
    glutAddMenuEntry("Blue-ish Grey", 14);
    glutAddMenuEntry("Red-ish Grey", 15);

    int plateShape_menu;
    plateShape_menu = glutCreateMenu(plateShape);
    glutAddMenuEntry("Rectangle (Default)", 8);
    glutAddMenuEntry("Square", 9);
    glutAddMenuEntry("Circle", 10);
    glutAddMenuEntry("Diamond", 11);

    int plate_menu;
    plate_menu = glutCreateMenu(plate);
    glutAddSubMenu("Change Color", plateColor_menu);
    glutAddSubMenu("Change Shape", plateShape_menu);

    int cup_menu;
    cup_menu = glutCreateMenu(cup);
    glutAddMenuEntry("Remove/Put On Lid", 3);
    glutAddMenuEntry("Change to Water", 4);
    glutAddMenuEntry("Change to Grape Soda", 5);
    glutAddMenuEntry("Change to Orange Soda", 6);
    glutAddMenuEntry("Change to Pepsi (Default)", 7);

    glutCreateMenu(main_menu);
    glutAddSubMenu("Cup", cup_menu);
    glutAddSubMenu("Plate", plate_menu);
    glutAddSubMenu("Rotate", rotate_menu);
    glutAddMenuEntry("Slice/Unslice", 2);
    glutAddMenuEntry("Quit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Food Plate Initialization -----> ENDS HERE

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    auto check_uncheck = [](int which) {
        if (checkbox_selections[which] == 0) // if unchecked, check
            checkbox_selections[which] = which;
        else // if checked, uncheck
            checkbox_selections[which] = 0;
    };

    auto update = []() {
        glutSetWindow(selection_menu);
        glutPostRedisplay();
        glutSetWindow(food_plate);
        glutPostRedisplay();
    };

    switch (key)
    {
    case 27:
        exit(0);
        break;

    //Toppings
    case '1': //Fresh Mozzarella
        check_uncheck(5);
        update();
        break;
    case '2': //Fresh Basil
        check_uncheck(4);
        update();
        break;
    case '3': //Sausage
        check_uncheck(3);
        update();
        break;
    case '4': //Mushroom
        check_uncheck(2);
        update();
        break;
    case '5': //Pepperoni
        check_uncheck(1);
        update();
        break;

    //Sauces
    case 'r': //Ranch
        radio_selection_sauces = 5;
        update();
        break;
    case 'a': //Alfredo
        radio_selection_sauces = 4;
        update();
        break;
    case 'g': //Garlic Parmesan
        radio_selection_sauces = 3;
        update();
        break;
    case 'b': //BBQ
        radio_selection_sauces = 2;
        update();
        break;
    case 'm': //Marinara
        radio_selection_sauces = 1;
        update();
        break;
    default:
        break;
    }
}

// Instructions
void printInstructions()
{
    cout << "Instructions: " << endl;
    cout << "Selection Window: " << endl;
    cout << "      Select small, medium, or large and this will change size. " << endl;
    cout << "      You can select 4 slices, 6 slices, or 8 slices. " << endl;
    cout << "      You can select Ranch, Alfredo, Garlic Parmesan, BBQ, or Marinara. These have key bindings also, R, A, G, B, and M, respectively" << endl;
    cout << "      Any number of toppings can be selected at once. Toppings include Fresh Mozzarella, Fresh Basil, Sausage, Mushrooms, and Pepperoni." << endl;
    cout << "      These have key bindings also, 1, 2, 3, 4, and 5, respectively." << endl;
    cout << " " << endl;
    cout << "Food Plate Window: " << endl;
    cout << "      When you left-click on the food plate window, the randomness of the topping placement is regenerate and can be shuffled." << endl;
    cout << "      When you right-click, a pop-up menu will appear." << endl;
    cout << " " << endl;
    cout << "Pop-up Menu: " << endl;
    cout << " The pop-up menu includes the ability to exit the program with the quit option. " << endl;
    cout << " It includes an option for slicing or unslicing the pizza." << endl;
    cout << " There is a sub-menu called Cup." << endl;
    cout << "       You can remove or put on the lid." << endl;
    cout << "       You can change the drink type." << endl;
    cout << " There is a sub-menu called Rotate." << endl;
    cout << "       Rotate -45 Degrees around the y-axis." << endl;
    cout << "       Rotate +45 Degrees around the y-axis." << endl;
    cout << " There is a sub-menu called Plate." << endl;
    cout << "       Change the color of the plate to Dark Grey, Green-ish-Grey, Blue-ish Grey, Red-ish Grey." << endl;
    cout << "       Change the shape of the plate to Rectangle, Square, Circle, Diamond." << endl;
}

// Main routine.
int main(int argc, char** argv)
{
    printInstructions();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    //Food Selection Window:
    glutInitWindowSize(winSize_X, winSize_Y);
    glutInitWindowPosition(100, 100);

    //Create Food Selection Window:
    selection_menu = glutCreateWindow("Food Selection:");
    
    //Initialization for Food Selection Window:
    SelectionMenu_setup();
    glutDisplayFunc(SelectionMenu_drawScene);
    glutReshapeFunc(SelectionMenu_resize);
    glutMouseFunc(SelectionMenu_MouseControl);
    glutKeyboardFunc(keyInput); //Shared by both windows


    //Food Plate Window:
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(850, 100); //Start Below Food Selection

    //Create Food Plate Window:
    food_plate = glutCreateWindow("Food Plate:");

    //Initialization for Food Plate Window:
    FoodPlate_setup();
    glutDisplayFunc(FoodPlate_drawScene);
    glutReshapeFunc(FoodPlate_resize);
    glutMouseFunc(FoodPlate_MouseControl);
    glutKeyboardFunc(keyInput); //Shared by both windows
    right_clickMenu();

    glutMainLoop();

    return 0;
}