/******************************************
*
* Helper file for HW3 - Includes:
*   - writeStrokeString
*   - draw_square
*   - draw_ellipse
*   - draw_cylinder
*   - draw_cone
*   - draw_ellipsoid
*   - draw_prism
*
*******************************************/

#include "helper_HW3.h"

// Stroke Text Function.
void Helper_HW3::writeStrokeString(void* font, const char* string, float lineWidth, float size)
{
    const char* c;
    glLineWidth(lineWidth);
    glScalef(size, size, size); // Font Size

    for (c = string; *c != '\0'; c++) {
        glutStrokeCharacter(font, *c);
    }
}

//Reusable Square Function
void Helper_HW3::draw_square(float x, float y, float z, float length, GLenum mode)
{
    glBegin(mode);
    glVertex3f(x - (length/2), y, z - (length / 2));
    glVertex3f(x - (length/2), y, z + length);
    glVertex3f(x + length, y, z + length);
    glVertex3f(x + length, y, z - (length / 2));
    glEnd();
}

//Reusable Ellipse/Circle Function
void Helper_HW3::draw_ellipse(float x, float y, float z, float w, float l, float r, GLenum mode)
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
void Helper_HW3::draw_cylinder(float height, float radius, float x, float y, float z, GLenum mode, GLenum mode2) {

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

//Clamp for Cone Function
float clamp(float x, float min_val, float max_val) {
    if (x < min_val) {
        return min_val;
    }
    else if (x > max_val) {
        return max_val;
    }
    else {
        return x;
    }
}

//Reusable Cone Function
void Helper_HW3::draw_cone(float radius, float height, int segments, float* color1, float* color2)
{
    // Compute the gradient for each vertex
    glBegin(GL_TRIANGLE_FAN);
    glColor4fv(color1);
    glVertex3f(0, 0, height);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * PI / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Compute the distance from the center of the base
        float d = sqrtf(x * x + y * y);

        // Compute the interpolation factor based on the distance
        float t = d / radius;
        t = clamp(t, 0.0f, 1.0f);  // clamp the value to [0,1]

        // Interpolate between the colors
        float color[4];
        for (int j = 0; j < 4; ++j) {
            color[j] = (1 - t) * color1[j] + t * color2[j];
        }

        // Set the vertex color and position
        glColor4fv(color);
        glNormal3f(x, y, height);
        glVertex3f(x, y, 0);
    }
    glEnd();

    // Draw the bottom cap
    glBegin(GL_TRIANGLE_STRIP);
    glColor4fv(color2);
    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * PI / segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        // Set the vertex color and position
        glNormal3f(0, 0, -1);
        glVertex3f(x, y, 0);

        glColor4fv(color2);
        glVertex3f(0, 0, 0);
    }
    glEnd();
}

//Reusable 3-D Ellipsoid Function
void Helper_HW3::draw_ellipsoid(float length, float width, float height, bool solid) {
    
    // Apply Transformations To Create An Ellipsoid
    glPushMatrix();
    glScalef(width, height, length);

    int slices = 50;
    int stacks = 50;

    if (solid) {
        int slices = 10;
        int stacks = 10;
        glutWireSphere(1.0, slices, stacks);
    }
    else {
        int slices = 50;
        int stacks = 50;
        glutSolidSphere(1.0, slices, stacks);
    }

    glPopMatrix();
}

//Reusable 3-D Prism Function
void Helper_HW3::draw_prism(float height, float length, float width) {
    glBegin(GL_QUADS);

    // Front face
    glVertex3f(-width / 2, -height / 2, length / 2);
    glVertex3f(width / 2, -height / 2, length / 2);
    glVertex3f(width / 2, height / 2, length / 2);
    glVertex3f(-width / 2, height / 2, length / 2);

    // Back face
    glVertex3f(-width / 2, -height / 2, -length / 2);
    glVertex3f(width / 2, -height / 2, -length / 2);
    glVertex3f(width / 2, height / 2, -length / 2);
    glVertex3f(-width / 2, height / 2, -length / 2);

    // Left face
    glVertex3f(-width / 2, -height / 2, -length / 2);
    glVertex3f(-width / 2, -height / 2, length / 2);
    glVertex3f(-width / 2, height / 2, length / 2);
    glVertex3f(-width / 2, height / 2, -length / 2);

    // Right face
    glVertex3f(width / 2, -height / 2, -length / 2);
    glVertex3f(width / 2, -height / 2, length / 2);
    glVertex3f(width / 2, height / 2, length / 2);
    glVertex3f(width / 2, height / 2, -length / 2);

    // Top face
    glVertex3f(-width / 2, height / 2, -length / 2);
    glVertex3f(width / 2, height / 2, -length / 2);
    glVertex3f(width / 2, height / 2, length / 2);
    glVertex3f(-width / 2, height / 2, length / 2);

    // Bottom face
    glVertex3f(-width / 2, -height / 2, -length / 2);
    glVertex3f(width / 2, -height / 2, -length / 2);
    glVertex3f(width / 2, -height / 2, length / 2);
    glVertex3f(-width / 2, -height / 2, length / 2);

    glEnd();
}